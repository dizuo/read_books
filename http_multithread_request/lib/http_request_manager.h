/*
    Copyright (C) =USTC= Fu Li

    Author   :  Fu Li
    Create   :  2009-10-1
    Home     :  http://www.phoxo.com
    Mail     :  crazybitwps@hotmail.com

    This file is part of UIStone

    The code distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

    Redistribution and use the source code, with or without modification,
    must retain the above copyright.
*/
#pragma once
#include <set>
#include "http_request.h"

//-------------------------------------------------------------------------------------
/**
    Manager HTTP request.
*/
class FCHttpRequestManager
{
    std::deque<FCHttpRequest*>   m_list ;
    std::deque<FCHttpRequest*>   m_delete ; // has been deleted, wait for thread exit

    HWND   m_wnd ;
    int    m_wait_ms_on_deconstructor ;
    int    m_current_task_id ;

public:
    FCHttpRequestManager()
    {
        CreateNotifyWnd() ;
        m_wait_ms_on_deconstructor = 3 * 1000 ;
        m_current_task_id = ID_TASK_AND_TIMER_START ;
    }

    virtual ~FCHttpRequestManager()
    {
        ::DestroyWindow (m_wnd) ;

        std::vector<HANDLE>   running_list ;
        GetAllRunningThreadAndClose (running_list) ;
        if (running_list.size())
        {
            WaitForMultipleObjects ((DWORD)running_list.size(), &running_list[0], TRUE, (DWORD)m_wait_ms_on_deconstructor) ;

            // force terminate thread
            for (size_t i=0 ; i < running_list.size() ; i++)
            {
                if (WaitForSingleObject(running_list[i],0) == WAIT_TIMEOUT)
                {
                    TerminateThread (running_list[i], 0) ;
                    assert(false) ;
                }
            }
        }

        for (size_t i=0 ; i < m_list.size() ; i++)
        {
            delete m_list[i] ;
        }
        for (size_t i=0 ; i < m_delete.size() ; i++)
        {
            delete m_delete[i] ;
        }
    }

    // In few extreme case, connecting cancel will taking a long time, set this value can reduce this time.
    void SetFinalClearToleranceTime (int nMilliseconds)
    {
        m_wait_ms_on_deconstructor = nMilliseconds ;
    }

    /// Add a new HTTP request, return nonzero task ID.
    int AddRequest (const HTTP_REQUEST_HEADER& request_header)
    {
        ::SetTimer (m_wnd, ID_CHECK_DELETE_TASK_TIMER, 100, NULL) ;

        int   nTaskID = m_current_task_id++ ;

        m_list.push_back (new FCHttpRequest (nTaskID, m_wnd, request_header)) ;
        return nTaskID ;
    }

    /// Add a new download, return nonzero task ID.
    int AddDownload (LPCTSTR sUrl)
    {
        HTTP_REQUEST_HEADER   t ;
        t.m_url = sUrl ;
        return AddRequest(t) ;
    }

    /// Find request, return NULL if not found.
    FCHttpRequest* FindRequest (int nTaskID) const
    {
        for (size_t i=0 ; i < m_list.size() ; i++)
        {
            FCHttpRequest   * rq = m_list[i] ;
            if (rq->GetTaskID() == nTaskID)
                return rq ;
        }
        return NULL ;
    }

    /// Delete request.
    void DeleteRequest (int nTaskID)
    {
        for (size_t i=0 ; i < m_list.size() ; i++)
        {
            FCHttpRequest   * rq = m_list[i] ;
            if (rq->GetTaskID() == nTaskID)
            {
                rq->CloseHttpHandleForDelete() ;

                m_list.erase (m_list.begin() + i) ;
                m_delete.push_back (rq) ;
                return ;
            }
        }
    }

    /// Get count of running request.
    int GetRequestCount() const { return (int)m_list.size(); }

protected:
    /**
        @name Event Callback.
        try to avoid pop a modal dialog in any callback\n\n
        if you have to pop a modal dialog in callback, call DeleteRequest to delete task before pop modal dialog
    */
    //@{
    /// callback after connected to server and sent HTTP request.
    virtual void OnAfterRequestSend (FCHttpRequest& rTask) {}
    /**
        callback after request finish\n
        after this callback, request will be deleted.
    */
    virtual void OnAfterRequestFinish (FCHttpRequest& rTask) {}
    /**
        callback when request over its lifetime that user set in HTTP_REQUEST_HEADER::m_lifetime_limit\n
        after this callback, request will be deleted.
    */
    virtual void OnOverRequestLifetime (FCHttpRequest& rTask) {}
    //@}

private:
    void GetAllRunningThreadAndClose (std::vector<HANDLE>& running_list)
    {
        std::set<HANDLE>   m ;
        for (size_t i=0 ; i < m_list.size() ; i++)
        {
            m.insert (m_list[i]->CloseHttpHandleForDelete()) ;
        }
        for (size_t i=0 ; i < m_delete.size() ; i++)
        {
            m.insert (m_delete[i]->CloseHttpHandleForDelete()) ;
        }
        m.insert((HANDLE)NULL) ;
        m.erase((HANDLE)NULL) ; // remove NULL thread handle

        running_list.assign (m.begin(), m.end()) ;
    }

    enum
    {
        ID_CHECK_DELETE_TASK_TIMER = 30,

        ID_TASK_AND_TIMER_START = 100,
    };

    void CreateNotifyWnd()
    {
        WNDCLASSEX   w = {0} ;
        w.cbSize = sizeof(w) ;
        w.hInstance = (HINSTANCE)&__ImageBase ;
        w.lpszClassName	= _T("uistone_http_event_wnd") ;
        w.lpfnWndProc = http_message_proc ;
        ::RegisterClassEx(&w) ;

        m_wnd = ::CreateWindowEx (0, w.lpszClassName, NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, w.hInstance, 0) ;
        ::SetWindowLongPtr (m_wnd, GWLP_USERDATA, (__int3264)(LONG_PTR)this) ; // __int3264 to remove warning in VS2005
    }

    void OnHttpEvent (int nTaskID, LPARAM event_type)
    {
        FCHttpRequest   * rq = FindRequest(nTaskID) ;
        if (rq)
        {
            switch (event_type)
            {
                case FCHttpRequest::HTTP_EVENT_CONNECT_FINISH :
                    rq->OnConnectThreadFinish() ;
                    break;

                case FCHttpRequest::HTTP_EVENT_SEND_REQUEST :
                    rq->m_response.SetResponse (rq->m_request) ;
                    OnAfterRequestSend(*rq) ;
                    break;

                case FCHttpRequest::HTTP_EVENT_REQUEST_FINISH :
                    OnAfterRequestFinish(*rq) ;
                    DeleteRequest(nTaskID) ;
                    break;
            }
        }
    }

    BOOL DeleteFirstFinishTask()
    {
        for (size_t i=0 ; i < m_delete.size() ; i++)
        {
            FCHttpRequest   * rq = m_delete[i] ;
            if (rq->IsAllThreadFinish())
            {
                delete rq ;
                m_delete.erase (m_delete.begin() + i) ;
                return TRUE ;
            }
        }
        return FALSE ;
    }

    void OnTimerMessage (UINT_PTR nTimerID)
    {
        if (nTimerID == ID_CHECK_DELETE_TASK_TIMER)
        {
            if (!m_list.size() && !m_delete.size())
            {
                ::KillTimer (m_wnd, nTimerID) ;
            }
            else
            {
                while (DeleteFirstFinishTask()) {}
            }
        }
        else
        {
            ::KillTimer (m_wnd, nTimerID) ;

            FCHttpRequest   * rq = FindRequest((int)nTimerID) ;
            if (rq)
            {
                OnOverRequestLifetime(*rq) ;
                DeleteRequest((int)nTimerID) ;
            }
        }
    }

    static LRESULT CALLBACK http_message_proc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        FCHttpRequestManager   * pThis = (FCHttpRequestManager*)(LONG_PTR)::GetWindowLongPtr(hWnd, GWLP_USERDATA) ;
        if (pThis)
        {
            switch (uMsg)
            {
                case FCHttpRequest::WM_UISTONE_HTTP_EVENT :
                    pThis->OnHttpEvent ((int)wParam, lParam) ;
                    return 0 ;

                case WM_TIMER :
                    pThis->OnTimerMessage (wParam) ;
                    return 0 ;
            }
        }
        return ::DefWindowProc (hWnd, uMsg, wParam, lParam) ;
    }
};

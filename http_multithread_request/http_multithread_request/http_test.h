#ifndef HTTP_TEST_H
#define HTTP_TEST_H

#include "../lib/http_request_manager.h"
#include <Windows.h>

class HttpTest : public FCHttpRequestManager
{
public:

	HttpTest();		// FCHttpRequestManager 构造函数依赖win32窗体系统。。。控制台程序创建失败！

	void start_download(const char* url);

	virtual void OnAfterRequestSend(FCHttpRequest& rTask);
	virtual void OnAfterRequestFinish(FCHttpRequest& rTask);

	int   m_task_id;
	std::string   m_receive;
	HTTP_REQUEST_HEADER   m_header;

};

#endif
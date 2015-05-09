#include "http_test.h"

HttpTest::HttpTest() : FCHttpRequestManager()
{
	m_header.m_url = "http://snsrtts.map.qq.com/?qt=rtt&c=±±¾©ÊÐ";
}

void HttpTest::start_download(const char* url)
{
	m_header.m_url = url;
	printf("url = %s\n", url);

	m_task_id = AddRequest(m_header);
	m_receive.clear();
}

void HttpTest::OnAfterRequestFinish(FCHttpRequest& rTask)
{
	rTask.PopReceived(m_receive);
	printf("receive size = %u\n", m_receive.size());
}

void HttpTest::OnAfterRequestSend(FCHttpRequest& rTask)
{

}
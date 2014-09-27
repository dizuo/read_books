#define _CRT_SECURE_NO_WARNINGS

// 解析html中所有jpg，然后逐个下载写到本地

#include<windows.h>
#include<Wininet.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

#pragma comment(lib,"WinInet.lib")

using namespace std;

typedef std::string str_t;

int grab_url_content(string& url_str, string& res_str);

void write_binary(string& content, string& fname);
void write_asci(string& content, string& fname);

str_t get_file_name_from_url(const str_t& url);

void parse_jpg_from_html(string& html, vector<str_t>& str_vec);
void process_html(string& html);

void test_grab_html(char* url);
void test_grab_jpg();

int main(int argn, char* argv[])
{
	if (argn == 1)
	{
		cout << "输入抓取的html 链接\n";
		cout << "any key pressed to exit...\n";
		cin.get();
		return 0;
	}

	test_grab_html(argv[1]);
	// test_grab_jpg();

	return 0;
}

void process_html(string& html)
{
	vector<str_t> jpg_url_vec;
	parse_jpg_from_html(html, jpg_url_vec);

	for (int i = 0; i < jpg_url_vec.size(); i++)
	{
		str_t& jpg_url = jpg_url_vec[i];

		str_t fname = get_file_name_from_url(jpg_url);
		cout << "<<===========================\n";
		cout << "jpg name : " << fname << endl;

		str_t jpg_content;
		if (grab_url_content(jpg_url, jpg_content) == 0)
		{
			write_binary(jpg_content, fname);
		}

		cout << ">>===========================\n";

		::Sleep(50);
	}
}

void parse_jpg_from_html(string& html, vector<str_t>& str_vec)
{
	char* pstr = &html[0];
	const char* token = "<>'";

	char* pch = strtok(pstr, token);
	const char* ptag = ".jpg";

	while (pch)
	{
		int len = strlen(pch);
		if (len > 4 && strcmp(pch + len - 4, ptag) == 0)
		{
			cout << pch << endl;
			str_vec.push_back(str_t(pch));
		}
		pch = strtok(NULL, token);
	}
}

void test_grab_html(char* purl)
{
	str_t url(purl); //"http://www.xxx.net/htm_data/16/1410/1231905.html";	// zlvc
	str_t fname = get_file_name_from_url(url);
	cout << "html name : " << fname << endl;
	str_t html_content;

	if (grab_url_content(url, html_content) == 0)
	{
		write_asci(html_content, fname);
		process_html(html_content);

		// parse_jpg_from_html(tmp_str);
	}
}

void test_grab_jpg()
{
	str_t url = "https://xx.media.tumblr.com/fb339a3c83099055be85323327d79afb/tumblr_ncgu4cM3V71tmlr77o2_1280.jpg";	// 38
	str_t fname = get_file_name_from_url(url);
	cout << "jpg name : " << fname << endl;
	
	str_t jpg_content;
	if (grab_url_content(url, jpg_content) == 0)
	{
		write_binary(jpg_content, fname);
	}

}

int grab_url_content(string& url_str, string& res_str)
{
	HINTERNET hINet, hHttpFile;
	char szSizeBuffer[32];

	DWORD dwLengthSizeBuffer = sizeof(szSizeBuffer);
	hINet = InternetOpen("IE6.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);    //InternetOpen初始化WININET.DLL
	
	if (!hINet)
	{
		cout << "InternetOpen fail" << endl;
		return 1;
	}

	hHttpFile = InternetOpenUrl(hINet, url_str.c_str(), NULL, 0, 0, 0);  //这个函数连接到一个网络服务器上并且最被从服务器上读取数据

	if (!hHttpFile)
	{
		cout << "error open url" << endl;
		return 1;
	}

	BOOL bQuery = HttpQueryInfo(hHttpFile,
		HTTP_QUERY_CONTENT_LENGTH,
		szSizeBuffer,
		&dwLengthSizeBuffer, NULL); //得到关于文件的信息

	if (bQuery == false)
	{
		InternetCloseHandle(hINet);
		cout << "error query info" << endl;
		return 3;
	}

	int FileSize = atol(szSizeBuffer);    //atol函数把字符串转换成长整型数
	res_str.resize(FileSize);

	DWORD dwBytesRead;
	BOOL bRead = InternetReadFile(hHttpFile, &res_str[0], FileSize, &dwBytesRead);     //web浏览器将在InternetReadFile上循环 ，不停地从Internet上读入数据块。
	
	if (!bRead)
	{
		cout << "error to read file" << endl;
		return 4;
	}

	InternetCloseHandle(hHttpFile);   //关闭句柄
	InternetCloseHandle(hINet);

	cout << url_str << " : 抓取成功!\n";

	return 0;
}

str_t get_file_name_from_url(const str_t& url)
{
	return url.substr(url.find_last_of('/') + 1);
}

void write_binary(string& content, string& fname)
{
	ofstream out_file(fname.c_str(), std::ios::binary);
	out_file.write(content.c_str(), content.length());
}

void write_asci(string& content, string& fname)
{
	ofstream out_file(fname.c_str());
	out_file << content << endl;
}
///////////////////////////////////////////////////////////////////////////////
//@package         web_connect_test
//@author          Dr. Lin, Chao
//@since           30th May 2018
//@version         0.0.1
///////////////////////////////////////////////////////////////////////////////

#ifndef LC_WEB_TESTER_H
#define LC_WEB_TESTER_H

#include <string>

size_t DummyWrite(char *ptr, size_t size, size_t nmemb, void *userdata);

//@class This class wrap curl library for my program. 
class WebTester
{
	protected:
		double connect_time;
		double name_lookup_time;
		double start_transfer_time;
		double total_time;

		long response_code;

		std::string server_ip;

		CURL *curl;
		struct curl_slist *headers;

	protected:
		void Reset(void);

	public:
		WebTester();
		~WebTester();

		void ResetHeader(void);
		void AddHeader(const char*);
		bool SetHost(const char*);
		bool SetHeaders(void);

		double GetConnectTime(void);
		double GetLookupTime(void);
		double GetTransferTime(void);
		double GetTotalTime(void);
		const char* GetServerIP(void);
		long GetResponseCode(void);

		bool Test(void);
};

#endif

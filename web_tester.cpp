///////////////////////////////////////////////////////////////////////////////
//@package         web_connect_test
//@author          Dr. Lin, Chao
//@since           30th May 2018
//@version         0.0.1
///////////////////////////////////////////////////////////////////////////////

#include <curl/curl.h>
#include <string.h>

#include "web_conn.h"
#include "web_tester.h"


size_t DummyWrite(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	return size * nmemb;
}


///////////////////////////////////////////////////////////////////////////////
// Constructor and destructor
///////////////////////////////////////////////////////////////////////////////
WebTester::WebTester()
{
	headers = NULL;
	Reset();
	ResetHeader();
	curl = curl_easy_init();
	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &DummyWrite);
	}
}


WebTester::~WebTester()
{
	if(curl)
	{
		curl_easy_cleanup(curl);
	}

}




///////////////////////////////////////////////////////////////////////////////
// Protected methods
///////////////////////////////////////////////////////////////////////////////

//@brief Re-set member variables. 
//
// This method should be called before perform curl test 
void WebTester::Reset(void)
{
	connect_time = 0;
	name_lookup_time = 0;
	start_transfer_time = 0;
	total_time = 0;
	server_ip = "";
	response_code = 0;
}




///////////////////////////////////////////////////////////////////////////////
// Testing related methods
///////////////////////////////////////////////////////////////////////////////




bool WebTester::Test(void)
{
	char *ip;

	Reset();
	if(curl) {
		curl_easy_perform(curl);

		if(curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total_time))
		{
			return false;
		}
		if(curl_easy_getinfo(curl, CURLINFO_NAMELOOKUP_TIME, &name_lookup_time))
		{
			return false;
		}
		if(curl_easy_getinfo(curl, CURLINFO_CONNECT_TIME, &connect_time))
		{
			return false;
		}
		if(curl_easy_getinfo(curl, CURLINFO_STARTTRANSFER_TIME, &start_transfer_time))
		{
			return false;
		}
		if( !curl_easy_getinfo(curl, CURLINFO_PRIMARY_IP, &ip) && ip)
		{
			server_ip = ip;
		}
		else
		{
			return false;
		}
		if( curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code))
		{
			return false;
		}
		return true;
	}
	return false;
}



///////////////////////////////////////////////////////////////////////////////
// Member variable access APIs
///////////////////////////////////////////////////////////////////////////////

void WebTester::ResetHeader(void)
{
	// Free curl resoruces in destructor
	if(headers != NULL)
	{
		curl_slist_free_all(headers);
	}
	headers = NULL;
}

void WebTester::AddHeader(const char* new_header)
{
	if(new_header && strnlen(new_header, MAX_STR_LENGTH) > 0)
	{
		headers = curl_slist_append(headers, new_header);
	}
}


bool WebTester::SetHost(const char* url)
{
	if(url && (strnlen(url, MAX_STR_LENGTH) > 0) && curl)
	{
		if( curl_easy_setopt(curl, CURLOPT_URL, url) == 0){
			return true;
		}
	}
	return false;
}



double WebTester::GetConnectTime(void)
{
	    return connect_time;
}

double WebTester::GetLookupTime(void)
{
	    return name_lookup_time;
}

double WebTester::GetTransferTime(void)
{
	    return start_transfer_time;
}

double WebTester::GetTotalTime(void)
{
	    return total_time;
}

const char* WebTester::GetServerIP(void)
{
	    return server_ip.c_str();
}

long WebTester::GetResponseCode(void)
{
	    return response_code;
}



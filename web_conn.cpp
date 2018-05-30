///////////////////////////////////////////////////////////////////////////////
//@author          Dr. Lin, Chao
//@since           30th May 2018
//@package         toolbox
//@version         0.0.1
//
//@mainpage        This program could be used to test web site network 
// connection quality. 
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <string>
#include <unistd.h>

// In future version, multi-threading can be used to boost the performance. 
#include <pthread.h>

// Make sure curl library has been installed on your system. 
#include <curl/curl.h>

#include "web_conn.h"
#include "web_tester.h"



// Paring the string and convert the string to integer value if all good. 
//
//@param arg A string which holds a integer
//@param var an integer pointer points to the variable which should hold the value
//@param min The minimum suitable value
//@param max The maximum suitable value
//
//@return true if everythong goes smoothly or false if something goes wrong. 
bool ParseInt(const char* arg, int* var, const int min, const int max)
{
	long lnum;
	char *end;
	bool b_result = false;

	// Do not use atoi since it is difficult to check whether the string
	// contains leagle value or not. 
	lnum = strtol(arg, &end, 10);
	*var = 0;
	if (arg == end)
	{
		std::cout << "Error: wrong value for test repeat number." << std::endl;
	}
	else if( (lnum == LONG_MAX) || (lnum == LONG_MIN) || errno == ERANGE)
	{
		std::cout << "Error: test repeat number is out of range." << std::endl;
	}
	else if( (lnum > max) || (lnum < min))
	{
		std::cout << "Error: test repeat number must be in the range of [" << min << "," << max << "]" << std::endl;
	}
	else
	{
		*var = (int)lnum;
		b_result = true;
	}


	return b_result;
}


//@brief Perform curl GET 
//
//@param site_name  web site name
//@param http_headers extra HTTP headers which provided by user through command line arguments. 
//@param repeat Test repeat number.
//@param threads Reserved for multi-threading version. 
//
//@return true if the web site can be accessed and response time has been calculated. Or false if all
//        tests failed. 
bool PerformTest(const char* site_name, std::vector<std::string>& http_headers, int repeat, int threads)
{
	double mean_connect_time;
	double mean_lookup_time;
	double mean_start_transfer_time;
	double mean_total_time;
	int i;
	int passed_tests;
	WebTester tester;
	std::vector<std::string>::iterator header;	

	tester.SetHost(site_name);

	for(header = http_headers.begin(); header != http_headers.end(); ++header)
	{
		tester.AddHeader((*header).c_str());
	}

	mean_connect_time = 0;
	mean_lookup_time = 0;
	mean_start_transfer_time = 0;
	mean_total_time = 0;
	passed_tests = 0;

	for(i=0; i<repeat; i++)
	{
		if(tester.Test())
		{
			mean_connect_time += tester.GetConnectTime();
			mean_lookup_time += tester.GetLookupTime();
			mean_start_transfer_time += tester.GetTransferTime();
			mean_total_time += tester.GetTotalTime();
			++passed_tests;
		}
	}

	if(passed_tests > 0)
	{
		mean_connect_time /= (double)passed_tests;
		mean_lookup_time /= (double)passed_tests;
		mean_start_transfer_time /= (double)passed_tests;
		mean_total_time /= (double)passed_tests;
		
		std::cout << "Passed test: " << passed_tests << " (total: " << repeat << ")" << std::endl;
		std::cout << "SKTEST;" << tester.GetServerIP() << ";" << tester.GetResponseCode() << ";" << mean_lookup_time << ";" << mean_connect_time << ";" << mean_start_transfer_time << ";" << mean_total_time << std::endl;
		return true;
	}
	else
	{
		std::cout << "Test failed." << std::endl;
		std::cout << "SKTEST;" << tester.GetServerIP() << ";" << tester.GetResponseCode() << ";" << "-" << ";" << "-"<< ";" << "-" << ";" << "-" << std::endl;
		return false;
	}

}


//@brief Main function for testing web site responding time. 
//
// Valid arguments are:
// -H "header_name:header_value"
// -n <repeat> 
// -T <threads>
//
//@note More than one HTTP header argument can be used if required. But repeat number and thread number 
//      can be set only once. The repeat number equals to one if no -n argument. Thread number
//      equals to one if no -T argument. 
//
//
//@note multi-threading mode does not included in this version. Therefore, the -T <threads> argument
//      takes no effect. 
int main(int argc, char** argv)
{
	bool test_repeat_set = false;				///< Mark whether test repeat number has been set or not. 
	bool test_threads_set = false;				///< Mark whether test thread count has been set or not. 
	int test_repeat = 1;						///< Test repeat number (must be >=1) 
	int test_threads = 1;						///< Test thread number (must be >=1)
	std::vector<std::string> http_headers;		///< Hold HTTP headers if provided by user. 
	std::vector<std::string>::iterator header;	///< iterator for HTTP headers
	int i;

	// Set repeat count to 1 if no command line argument is provided. 
	if(argc == 1)
	{
		test_repeat = 1;
		test_threads = 1;
	}
	// Parse command line arguments
	// Since the command line arguments syntax is simple and this code
	// suppose to be easy to move to other platform, this program parses
	// all command line arguments by itself. 
	else
	{
		for(i=1; i<argc; i++)
		{
			// Parse repeat number 
			if(!strncmp(argv[i], "-n", MAX_STR_LENGTH))
			{
				i++;
				if( test_repeat_set == true)
				{
					std::cout << "Error: Can not set test repeat number more than once!" << std::endl;
					return ERROR_WRONG_ARGS;
				}
				if(i < argc)
				{
					if( ParseInt(argv[i], &test_repeat, 1, MAX_REPEAT))
					{
						test_repeat_set = true;
					}
					else
					{
						std::cout << "Error: Read test repeat number failed!" << std::endl;
						return ERROR_WRONG_ARGS;
					}
				}
				else
				{
					std::cout << "Expecting test repeat number (integer)" << std::endl;
					return ERROR_WRONG_ARGS;
				}
			}
			// Parse extra HTTP header argument. 
			else if(!strncmp(argv[i], "-H", MAX_STR_LENGTH))
			{
				i++;
				if(i < argc)
				{
					if(strnlen(argv[i], MAX_STR_LENGTH) > 0)
					{
						http_headers.push_back(argv[i]);
					}
					else
					{
						std::cout << "Error: HTTP header can not be empty." << std::endl;
						return ERROR_WRONG_ARGS;
					}
				}
				else
				{
					std::cout << "Error: expecting a HTTP header." << std::endl;
					return ERROR_WRONG_ARGS;
				}
			}
			// Parse number of threads argument
			else if(!strncmp(argv[i], "-T", MAX_STR_LENGTH))
			{
				i++;
				if( test_threads_set == true)
				{
					std::cout << "Error: Can not set number of threads more than once!" << std::endl;
					return ERROR_WRONG_ARGS;
				}
				if(i < argc)
				{
					if(ParseInt(argv[i], &test_threads, 1, MAX_THREADS))
					{
						test_threads_set = true;
					}
					else
					{
						std::cout << "Error: Read number of threads failed!" << std::endl;
						return ERROR_WRONG_ARGS;
					}
				}
				else
				{
					std::cout << "Error: expecting number of threads (integer)" << std::endl;
					return ERROR_WRONG_ARGS;
				}
			}
			else
			{
				std::cout << "Unknown command line argument: " << argv[i] << std::endl;
				return ERROR_WRONG_ARGS;
			}
		}
	}


	PerformTest("http://www.google.com", http_headers, test_repeat, test_threads);

	return 0;
}


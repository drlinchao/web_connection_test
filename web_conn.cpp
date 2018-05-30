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
#include <stdio.h>
#include <string.h>
#include <string>
#include <unistd.h>

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

int main(int argc, char** argv)
{
	bool test_repeat_set = false;	///< Mark whether test repeat number has been set or not. 
	bool test_threads_set = false;	///< Mark whether test thread count has been set or not. 
	int test_repeat = 1;			///< Test repeat number (must be >=1) 
	int test_threads = 1;			///< Test thread number (must be >=1)
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

	std::cout << "Repeat: " << test_repeat << std::endl;
	std::cout << "Theads: " << test_threads << std::endl;


	return 0;
}


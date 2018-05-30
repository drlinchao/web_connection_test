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


int main(int argc, char** argv)
{
	bool test_repeat_set = false;	///< Mark whether test repeat number has been set or not. 
	bool test_threads_set = false;	///< Mark whether test thread count has been set or not. 
	int test_repeat = 0;			///< Test repeat number (must be >=1) 
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
			if(!strncmp(argv[i], "-n", MAX_STR_LENGTH))
			{
				if( test_repeat_set == true)
				{
					std::cout << "Error: Can not set test repeat number more than once!" << std::endl;
					return ERROR_WRONG_ARGS;
				}

				i++;
				if(i < argc)
				{
					long lnum;
					char *end;
					lnum = strtol(argv[i], &end, 10);

					if (argv[i] == end)
					{
						std::cout << "Error: wrong value for test repeat number." << std::endl;
						return ERROR_OUT_OF_RANGE;
					}
					else if( (lnum == LONG_MAX) || (lnum == LONG_MIN) || errno == ERANGE)
					{
						std::cout << "Error: test repeat number is out of range." << std::endl;
						return ERROR_OUT_OF_RANGE;
					}
					else if( (lnum > MAX_REPEAT) || (lnum < 1))
					{
						std::cout << "Error: test repeat number must be in the range of [" << 1 << "," << MAX_REPEAT << "]" << std::endl;
						return ERROR_OUT_OF_RANGE;
					}
					else
					{
						test_repeat = (int)lnum;
						test_repeat_set = true;
					}
				}
				else
				{
					std::cout << "Expecting test repeat number (integer)" << std::endl;
					return ERROR_WRONG_ARGS;
				}
			}
			else if(!strncmp(argv[i], "-H", MAX_STR_LENGTH))
			{
			}
			else if(!strncmp(argv[i], "-T", MAX_STR_LENGTH))
			{
			}
			else
			{
				std::cout << "Unknown command line argument: " << argv[i] << std::endl;
				return ERROR_WRONG_ARGS;
			}
		}
	}


	return 0;
}


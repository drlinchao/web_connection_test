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
	int repeat = 0;
	int nthread = 1;
	int i;

	// Set repeat count to 1 if no command line argument is provided. 
	if(argc == 1)
	{
	}
	// Parse arguments
	else
	{
		for(i=1; i<argc; i++)
		{
			if(!strncmp(argv[i], "-n", MAX_STR_LENGTH))
			{
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


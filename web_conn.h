///////////////////////////////////////////////////////////////////////////////
//@author          Dr. Lin, Chao
//@since           30th May 2018
//@package         toolbox
//@version         0.0.1
///////////////////////////////////////////////////////////////////////////////


#ifndef LC_WEB_CONN_H
#define LC_WEB_CONN_H

// Define maximum string length for string compare, copy functions.
#define MAX_STR_LENGTH		1024

// Define my error code
#define ERROR_WRONG_ARGS	1
#define ERROR_OUT_OF_RANGE	2
#define ERROR_TEST_FAILED	3
#define ERROR_CONN_FAILED	4

// Define the maximum threads this program allows
//
// By using multi-threading technology, the program performance could be imporoved in most case. 
// Consider running this program on a multi-core PC and/or with relatively slow
// network connection speed, multi-threading can reduce the total testing time dramatically. 
//
// However, consider system resoruce usage and thread conflications, number of threads must
// be considered. Here is a temporary setting which allows up to four threads running on 
// a quad-core ARM single board computer. 
#define MAX_THREADS			4

// Set a maximum repeat number to prevent user input a very large repeat number accidently.
#define MAX_REPEAT			10000

#endif 


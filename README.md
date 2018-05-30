# web_connection_test
Test web site network connection using curl library

Programming language: C/C++
Default platform: Linux
Default development environment: GNU make, GNU GCC, libcurl-7.60.0

# Target
* Check how good the network connectivity to a web site, say http://www.google.com using one or more HTTP GET request
* Get network response and extract statistic from the respones
* Using C, C++, curl library
* Can take one or more command line argument like `-H "Header-name: Header-value"` to specify extra HTTP header
* Can take command line argument like `-n <integer>` to set how many GET should be performed. 
* The program output takes this format: 
  `SKTEST;<IP address of HTTP server>;<HTTP response code>;<median of CURLINFO_NAMELOOKUP_TIME>;<median of CURLINFO_CONNECT_TIME>;<median of CURLINFO_STARTTRANSFER_TIME>;<median of CURLINFO_TOTAL_TIME>`
  
# Build the source
* Make sure curl library (can be downloaded from https://curl.haxx.se/libcurl/) has been installed before build the source code. 
* Make sure GNU make and GCC have been installed before build the source code. 
* clone souce code from GitHub
* Enter source code folder
  * `make` to build the source code
  * `make help` show help message
  * `make clean` to clean temporary files.
* This program has been tested on ARM board (OrangePi Win-Plus http://www.orangepi.org/OrangePiWinPlus/) with gcc 8.1.0 and curl library 7.60.0

# Execute the program
If the source code is built correctly, run executable file `web_conn` from a terminal window. 
`web_conn -n 100` gives a result:
`Passed test: 100 (total: 100)`
`SKTEST;172.217.23.36;200;0.00039553;0.00049263;0.0573863;0.0900923`

# Note [TO DO list]
The program can be improved if I could work with it further. Here is a brief **TO DO** list which could be considered in the future:
* Turn the program into multi-threading mode, which would boot the test performance a lot. 
* Take web site URL from command line so that it can test network performance for other web site. 
* Take more than one web site URL from command line so that more than one web site can be tested at the same time (take URL list from command line seperated by a dilimeter?)
* More results could be calculated such as min, max, divation of response time etc. 
* Unit test and functional test program can be writen to check this program quality.

# web_connection_test
Test web site network connection using curl library

Programming language: C/C++
Default platform: Linux
Default development environment: GNU make, GNU GCC, libcurl-7.60.0

# target
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

# Execute the program
If the source code is built correctly, run executable file `web_conn` from a terminal window. 



#ifndef STDAFX_H
#define STDAFX_H


#define VERSION "1.0"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include "lib/xmlParser/xmlParser/xmlParser.h"

#include <string>
#define CURL_STATICLIB
#include <stdio.h>
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>
#include <libgen.h>
#include <stdio.h>
#include "zip.h"
#include "unzip.h"
#include <direct.h>

using namespace std;


enum Color { DARKBLUE = 1, DARKGREEN, DARKTEAL, DARKRED, DARKPINK, DARKYELLOW, GRAY, DARKGRAY, BLUE, GREEN, TEAL, RED, PINK, YELLOW, WHITE };

void SetColor(Color c);

bool fileExist (const std::string& name);

size_t writeData(void* ptr, const size_t size, const size_t nmemb, FILE* stream);
bool get_http_data(string server, string file);

void extract_zip(string path,string zip);

bool dirExist(const std::string& dirName_in);

void createFile(string file,string content);


std::string GetPath();

string clean_path(string path);

std::string ReplaceString(std::string subject, const std::string& search,
                          const std::string& replace);

#endif // STDAFX_H

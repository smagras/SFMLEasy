#include "stdafx.hpp"


void SetColor(Color c){

        HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hCon, c);
}

bool fileExist (const std::string& name) {
    ifstream f(name.c_str());
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }
}


size_t writeData(void* ptr, const size_t size, const size_t nmemb, FILE* stream)
{
    return fwrite(ptr, size, nmemb, stream);
}


bool get_http_data(string server, string file)
{
    CURL* curl = curl_easy_init();

    if (curl)
    {
    const char* url = server.c_str();
    const char* filename = file.c_str();
    FILE* ofile = fopen(filename, "wb");

    if (ofile)
    {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, ofile);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);

    curl_easy_perform(curl);

    fclose(ofile);
    }

    /* always cleanup */
    curl_easy_cleanup(curl);

    }
	return true;
}

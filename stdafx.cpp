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


std::string GetPath()
{
    DWORD dwReturn;
    char szBuffer[MAX_PATH];

    dwReturn = GetCurrentDirectory(MAX_PATH,szBuffer);

    std::string f = szBuffer;
    return f;


}

bool dirExist(const std::string& dirName_in)
{
  DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
  if (ftyp == INVALID_FILE_ATTRIBUTES)
    return false;  //something is wrong with your path!

  if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return true;   // this is a directory!

  return false;    // this is not a directory!
}

void extract_zip(string path,string zip){
    HZIP hz = OpenZip(zip.c_str(),0);
    SetUnzipBaseDir(hz,_T(path.c_str()));
    ZIPENTRY ze; GetZipItem(hz,-1,&ze); int numitems=ze.index;
    for (int zi=0; zi<numitems; zi++)
    {
        ZIPENTRY ze; GetZipItem(hz,zi,&ze);
        UnzipItem(hz, zi, ze.name);
    }
    CloseZip(hz);

}


size_t writeData(void* ptr, const size_t size, const size_t nmemb, FILE* stream)
{
    return fwrite(ptr, size, nmemb, stream);
}

string clean_path(string path){
    string res = ReplaceString(path,"\\","/");
    char lastChar = res.at( res.length() - 1 );
    if(lastChar != '/') res += "/";
    return res;
}

std::string ReplaceString(std::string subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
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

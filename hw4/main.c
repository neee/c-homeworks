#include <stdio.h>
#include <curl/curl.h>
#include <json-c/json.h>
#include <string.h>

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *) userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

int main(int argc, char **argv) {
    // Validate input args
    if (argc < 2) {
        fprintf(stderr, "City wasn't defined, please use: './weather moscow' or './weather Moscow'");
        exit(EXIT_FAILURE);
    }
    char request_url[128];
    memset(request_url, 0, 128);
    sprintf(request_url, "https://wttr.in/%s?format=j1", argv[1]);

    CURL *curl_handle;
    CURLcode res;

    struct MemoryStruct chunk;

    chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */
    chunk.size = 0;    /* no data at this point */

    curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */
    curl_handle = curl_easy_init();

    /* specify URL to get */
    curl_easy_setopt(curl_handle, CURLOPT_URL, request_url);

    /* send all data to this function  */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

    /* we pass our 'chunk' struct to the callback function */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *) &chunk);

    /* some servers do not like requests that are made without a user-agent
       field, so we provide one */
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    /* get it! */
    res = curl_easy_perform(curl_handle);

    /* check for errors */
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
        /*
         * Now, our chunk.memory points to a memory block that is chunk.size
         * bytes big and contains the remote file.
         *
         * Do something nice with it!
         */

        printf("%s bytes retrieved\n", chunk.memory);
    }

    /* cleanup curl stuff */
    curl_easy_cleanup(curl_handle);

    free(chunk.memory);

    /* we are done with libcurl, so clean it up */
    curl_global_cleanup();

    return 0;
}
//
//static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp) {
//    size_t chunk_size = size * nmemb;
//    response_chunk *chunk = (response_chunk *) userp;
//    /**
//     * Не могу найти причину почему тут при первом заполнении приходит очень большое число, пробовал уже и обнулять
//     * при первом создании структуры в main и через calloc не вышло... сделал пока такой хак
//     */
//    if (chunk->size > 1000000) {
//        chunk->size = 0;
//    }
//
//    char *ptr = realloc(chunk->chars, chunk->size + chunk_size + 1);
//    if (ptr == NULL) {
//        return 0;
//    }
//
//    chunk->chars = ptr;
//    memcpy(&(chunk->chars[chunk->size]), data, chunk_size);
//    chunk->size += chunk_size;
//    chunk->chars[chunk->size] = 0;
//
//    return chunk_size;
//}
//
//int main(int argc, char **argv) {
//    // Validate input args
//    if (argc < 2) {
//        fprintf(stderr, "City wasn't defined, please use: './weather moscow' or './weather Moscow'");
//        exit(EXIT_FAILURE);
//    }
//    char request_url[128];
//    memset(request_url, 0, 128);
//    sprintf(request_url, "https://wttr.in/%s?format=j1", argv[1]);
//
//    // Request preparation
//    CURL *curl = curl_easy_init();
//    if (!curl) {
//        fprintf(stderr, "Failed to initialize curl\n");
//        exit(EXIT_FAILURE);
//    }
//
//    struct curl_slist *headers = NULL;
//    headers = curl_slist_append(headers, "Accept: application/json");
//    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//    curl_easy_setopt(curl, CURLOPT_URL, request_url);
//
//    response_chunk *chunk = {0};
//    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
//    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);
//
//    // Make request
//    CURLcode curlResponse = curl_easy_perform(curl);
//    if (curlResponse != CURLE_OK) {
//        fprintf(stderr, "Curl call error: %s\n", curl_easy_strerror(curlResponse));
//        curl_slist_free_all(headers);
//        curl_easy_cleanup(curl);
//        exit(EXIT_FAILURE);
//    }
//
//    // Check chunk code
//    long http_code = 0;
//    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
//    if (http_code != 200) {
//        fprintf(stderr, "Error response code from remote server: %ld\n", http_code);
//        curl_slist_free_all(headers);
//        curl_easy_cleanup(curl);
//        exit(EXIT_FAILURE);
//    }
//
//    /**
//     * Не могу понять почему chunk->chars = "", в дебаге в фунции write_callback значения пишутеся в переменную и она пересоздается
//     * Тут нужна помощь
//     */
//    printf("JSON: %s", chunk->chars);
//    free(chunk->chars);
//
//    curl_slist_free_all(headers);
//    curl_easy_cleanup(curl);
//    exit(EXIT_SUCCESS);
//}

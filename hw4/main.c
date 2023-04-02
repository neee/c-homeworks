#include <stdio.h>
#include <curl/curl.h>
#include <json-c/json.h>
#include <string.h>

typedef struct {
    char *chars;
    size_t size;
} response_chunk;

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp) {
    size_t chunk_size = size * nmemb;
    response_chunk *chunk = (response_chunk *) userp;
    /**
     * Не могу найти причину почему тут при первом заполнении приходит очень большое число, пробовал уже и обнулять
     * при первом создании структуры в main и через calloc не вышло... сделал пока такой хак
     */
    if (chunk->size > 1000000) {
        chunk->size = 0;
    }

    char *ptr = realloc(chunk->chars, chunk->size + chunk_size + 1);
    if (ptr == NULL) {
        return 0;
    }

    chunk->chars = ptr;
    memcpy(&(chunk->chars[chunk->size]), data, chunk_size);
    chunk->size += chunk_size;
    chunk->chars[chunk->size] = 0;

    return chunk_size;
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

    // Request preparation
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to initialize curl\n");
        exit(EXIT_FAILURE);
    }

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, request_url);

    response_chunk *chunk = {0};
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);

    // Make request
    CURLcode curlResponse = curl_easy_perform(curl);
    if (curlResponse != CURLE_OK) {
        fprintf(stderr, "Curl call error: %s\n", curl_easy_strerror(curlResponse));
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        exit(EXIT_FAILURE);
    }

    // Check chunk code
    long http_code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    if (http_code != 200) {
        fprintf(stderr, "Error response code from remote server: %ld\n", http_code);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        exit(EXIT_FAILURE);
    }

    /**
     * Не могу понять почему chunk->chars = "", в дебаге в фунции write_callback значения пишутеся в переменную и она пересоздается
     * Тут нужна помощь
     */
    printf("JSON: %s", chunk->chars);
    free(chunk->chars);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    exit(EXIT_SUCCESS);
}

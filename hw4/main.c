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
    /* Validate input args */
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

    if (!curl_handle) {
        fprintf(stderr, "Failed to initialize curl\n");
        exit(EXIT_FAILURE);
    }

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
        fprintf(stderr, "Curl perform failed: %s\n", curl_easy_strerror(res));
    } else {
        /* Parse response and set variables */
        struct json_object *root = json_tokener_parse(chunk.memory);
        if (!root) {
            fprintf(stderr, "Failed to parse JSON\n");
            curl_easy_cleanup(curl_handle);
            free(chunk.memory);
            curl_global_cleanup();

            exit(EXIT_FAILURE);
        }

        struct json_object *current_condition_array;
        struct json_object *current_condition;
        struct json_object *current_weather_desc;
        struct json_object *current_weather_definition_value;
        struct json_object *current_weather_temp;
        struct json_object *current_wind_speed_kmh;
        struct json_object *current_wind_direction_degree;
        struct json_object *current_weather_definition;

        json_object_object_get_ex(root, "current_condition", &current_condition_array);
        current_condition = json_object_array_get_idx(current_condition_array, 0);
        json_object_object_get_ex(current_condition, "weatherDesc", &current_weather_desc);
        current_weather_definition = json_object_array_get_idx(current_weather_desc, 0);
        json_object_object_get_ex(current_weather_definition, "value", &current_weather_definition_value);
        json_object_object_get_ex(current_condition, "temp_C", &current_weather_temp);
        json_object_object_get_ex(current_condition, "windspeedKmph", &current_wind_speed_kmh);
        json_object_object_get_ex(current_condition, "winddirDegree", &current_wind_direction_degree);

        /* Print current conditions */
        printf("-----------------------------------\n");
        printf("Current weather:\n");
        printf("  Definition: '%s'\n", json_object_get_string(current_weather_definition_value));
        printf("  Temperature: '%s'\n", json_object_get_string(current_weather_temp));
        printf("  Wind speed: '%s' km/h\n", json_object_get_string(current_wind_speed_kmh));
        printf("  Wind direction degree: '%s'\n", json_object_get_string(current_wind_direction_degree));
        printf("-----------------------------------\n");

        /* Forecast variables */
        struct json_object *date;
        struct json_object *minTempC;
        struct json_object *maxTempC;
        struct json_object *weather_array;

        /* Parse forecast on next days */
        printf("Forecast on next few days:\n");
        json_object_object_get_ex(root, "weather", &weather_array);
        size_t days = json_object_array_length(weather_array);
        for (size_t i = 0; i < days; i++) {
            struct json_object *day = json_object_array_get_idx(weather_array, i);
            json_object_object_get_ex(day, "date", &date);
            json_object_object_get_ex(day, "mintempC", &minTempC);
            json_object_object_get_ex(day, "maxtempC", &maxTempC);
            /* Print forecast on next days */
            printf("  Date %s\n", json_object_get_string(date));
            printf("    Temperature range: %s°C to %s°C\n", json_object_get_string(minTempC), json_object_get_string(maxTempC));
        }
        printf("-----------------------------------\n");

        json_object_put(root);
    }

    curl_easy_cleanup(curl_handle);
    free(chunk.memory);
    curl_global_cleanup();

    return EXIT_SUCCESS;
}

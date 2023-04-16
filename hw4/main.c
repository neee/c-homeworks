#include <stdio.h>
#include <curl/curl.h>
#include <json-c/json.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

static void print_weather(struct json_object *);

static bool validate_location(char *, struct json_object *);

char *to_lowercase(const char *);

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t write_memory_callback(void *contents, size_t size, size_t nmemb, void *userp) {
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

    printf("Request weather for '%s' city\n", argv[1]);
    /* Make city name in lowercase */
    char *city = to_lowercase(argv[1]);

    sprintf(request_url, "https://wttr.in/%s?format=j1", city);

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
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_memory_callback);

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
        if (!validate_location(city, root)) {
            fprintf(stderr, "Weather for the city '%s' not found, please try with another city\n", city);

            exit(EXIT_FAILURE);
        }

        print_weather(root);
    }

    curl_easy_cleanup(curl_handle);
    free(chunk.memory);
    curl_global_cleanup();
    free(city);

    return EXIT_SUCCESS;
}

char *to_lowercase(const char *input) {
    char *output = (char *) calloc(strlen(input) + 1, sizeof(char));
    for (int i = 0; input[i]; i++) {
        output[i] = (char) tolower(input[i]);
    }

    return output;
}

static bool validate_location(char *city, struct json_object *root) {
    struct json_object *nearest_area_array;
    struct json_object *nearest_area;
    struct json_object *nearest_area_name;
    struct json_object *area_name_array;
    struct json_object *area_name_value;
    char *value_in_lowercase;

    json_object_object_get_ex(root, "nearest_area", &nearest_area_array);
    size_t areas_count = json_object_array_length(nearest_area_array);
    if (areas_count == 0) {
        return false;
    }

    for (int i = 0; i < areas_count; ++i) {
        nearest_area = json_object_array_get_idx(nearest_area_array, i);
        json_object_object_get_ex(nearest_area, "areaName", &area_name_array);
        size_t area_name_array_count = json_object_array_length(area_name_array);
        for (int j = 0; j < area_name_array_count; ++j) {
            nearest_area_name = json_object_array_get_idx(area_name_array, i);
            json_object_object_get_ex(nearest_area_name, "value", &area_name_value);
            value_in_lowercase = to_lowercase(json_object_get_string(area_name_value));
            if (strcmp(value_in_lowercase, city) == 0) {
                free(value_in_lowercase);
                free(nearest_area_array);
                free(nearest_area);
                free(nearest_area_name);
                free(area_name_array);
                free(area_name_value);

                return true;
            }
        }
    }

    free(value_in_lowercase);
    free(nearest_area_array);
    free(nearest_area);
    free(nearest_area_name);
    free(area_name_array);
    free(area_name_value);

    return false;
}

static void print_weather(struct json_object *root) {
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
    struct json_object *day;

    /* Parse forecast on next days */
    printf("Forecast on next few days:\n");
    json_object_object_get_ex(root, "weather", &weather_array);
    size_t days = json_object_array_length(weather_array);
    for (size_t i = 0; i < days; i++) {
        day = json_object_array_get_idx(weather_array, i);
        json_object_object_get_ex(day, "date", &date);
        json_object_object_get_ex(day, "mintempC", &minTempC);
        json_object_object_get_ex(day, "maxtempC", &maxTempC);
        /* Print forecast on next days */
        printf("  Date %s\n", json_object_get_string(date));
        printf("    Temperature range: %s°C to %s°C\n", json_object_get_string(minTempC), json_object_get_string(maxTempC));
    }
    printf("-----------------------------------\n");

    free(current_condition_array);
    free(current_condition);
    free(current_weather_desc);
    free(current_weather_definition_value);
    free(current_weather_temp);
    free(current_wind_speed_kmh);
    free(current_wind_direction_degree);
    free(current_weather_definition);
    free(date);
    free(minTempC);
    free(maxTempC);
    free(weather_array);
    free(day);
    json_object_put(root);
}

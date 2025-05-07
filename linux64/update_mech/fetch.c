#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Callback function to write the data to a file
size_t write_callback(void *ptr, size_t size, size_t nmemb, FILE *file) {
    size_t total_size = size * nmemb;
    fwrite(ptr, size, nmemb, file);  // Write the data directly to the file
    return total_size;
}
// func to check if version.json exists
int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");  // Try to open the file in read mode
    if (file) {
        fclose(file);  // Close the file if it exists
        return 1;  // File exists
    } else {
        return 0;  // File doesn't exist
    }
}

int main() {
	const char *filename = "versionc.json";  
    if (file_exists(filename)) {
        printf("File '%s' exists.\n", filename);
	filename = "versionn.json";
    } else {
        printf("File '%s' does not exist.\n", filename);
    }

    CURL *curl;
    CURLcode res;
    FILE *file;

    // Open the file where you want to save the data (in this case, version.json)
    file = fopen(filename, "wb");
    if (file == NULL) {
        fprintf(stderr, "Could not open file for writing\n");
        return 1;
    }

    // Initialize CURL library
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set the URL to fetch
        curl_easy_setopt(curl, CURLOPT_URL, "https://raw.githubusercontent.com/GarethTacos/shitdencalc/refs/heads/main/linux64/version.json");
        
        // Set the write callback function to handle the response and write to the file
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);  // Provide the file pointer

        // Perform the HTTP request
        res = curl_easy_perform(curl);

        // Check if the request was successful
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("Successfully wrote the response to version.json\n");
        }

        // Clean up CURL
        curl_easy_cleanup(curl);
    }

    // Clean up global CURL environment
    curl_global_cleanup();

    // Close the file
    fclose(file);

    return 0;
}


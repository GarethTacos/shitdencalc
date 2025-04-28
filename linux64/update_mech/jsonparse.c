#include <stdio.h>
#include <json-c/json.h>

int main() {
    // Open the JSON file
    FILE *file = fopen("version.json", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    // Read the file into a string buffer
    fseek(file, 0, SEEK_END); // Go to the end of the file
    long file_size = ftell(file); // Get the size of the file
    fseek(file, 0, SEEK_SET); // Go back to the beginning of the file

    char *json_string = (char *)malloc(file_size + 1); // Allocate memory for the file content
    if (json_string == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return 1;
    }

    size_t bytes_read = fread(json_string, 1, file_size, file);
    if (bytes_read != file_size) {
    	perror("Error reading file");
    	free(json_string);
    	fclose(file);
    	return 1;
    }
    json_string[file_size] = '\0'; // Null-terminate the string

    fclose(file); // Close the file

    // Parse the JSON string
    struct json_object *parsed_json = json_tokener_parse(json_string);
    if (parsed_json == NULL) {
        printf("Failed to parse JSON.\n");
        free(json_string);
        return 1;
    }

    // Extract and print a value (e.g., "version") from the JSON
    struct json_object *version_obj;
    if (json_object_object_get_ex(parsed_json, "version", &version_obj)) {
        const char *version = json_object_get_string(version_obj);
        printf("version: %s\n", version);
    } else {
        printf("No 'version' key in the JSON.\n");
    }
	if (json_object_object_get_ex(parsed_json, "friendly-name", &version_obj)) {
	const char *friendly = json_object_get_string(version_obj);
	printf("friendly-name: %s\n", friendly);
	} else {
		printf("No 'friendly-name' key in the JSON.\n");
	}
	if (json_object_object_get_ex(parsed_json, "platform", &version_obj)) {
	const char *platform = json_object_get_string(version_obj);
	printf("platform: %s\n", platform);
	} else {
		printf("No 'platform' key in the JSON.\n");
	}    
	if (json_object_object_get_ex(parsed_json, "build-type", &version_obj)) {
	const char *btype = json_object_get_string(version_obj);
	printf("build-type: %s\n", btype);
	} else {
		printf("No 'build-type' key in the JSON.\n");
	}  
	if (json_object_object_get_ex(parsed_json, "pull-from", &version_obj)) {
	const char *pfrom = json_object_get_string(version_obj);
	printf("pull-from: %s\n", pfrom);
	} else {
		printf("No 'pull-from' key in the JSON.\n");
	}   	// Clean up
    free(json_string);
    json_object_put(parsed_json); // Free the parsed JSON object

    return 0;
}


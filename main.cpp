#include <stdio.h>
#include <sys/json.h>

using namespace std;

int main(){}

//sample code for QNX IDE Json encode
https://www.qnx.com/developers/docs/7.0.0/#com.qnx.doc.json/topic/manual/encoder_sample.html
bool prepare_file_info(char *str, int max_finfo_size)
{
    // In this example, we hardcode the field settings but often, they would be input
    // by a user or come from another source (e.g., a file or program)
    int id = 76;
    int type = 4;
    long long size = 99;
    const char *path = "/var/dhclient/leases";

    json_encoder_t *enc = json_encoder_create();

    // Write the 'id' value as a separate field in the top-level object, then write the
    // 'path', 'type', and 'size' fields in a nested object, 'info'.
    json_encoder_start_object(enc, NULL);
    json_encoder_add_int(enc, "id", id);
    json_encoder_start_object(enc, "info");
    json_encoder_add_string(enc, "path", path);
    json_encoder_add_int(enc, "type", type);
    json_encoder_add_int_ll(enc, "size", size);
    json_encoder_end_object(enc);
    json_encoder_end_object(enc);

    // For error checking, we don't need to check the return value of each function
    // since any error will cause the subsequent json_encoder_buffer() call to fail. 
    // Common errors are mismatched object or array start and end calls (which are 
    // programming errors) and out-of-memory errors.
    json_encoder_error_t status = json_encoder_get_status(enc);
    
    // If everything above has succeeded, json_encoder_get_status() will return 
    // JSON_ENCODER_OK
    if ( status != JSON_ENCODER_OK ) {
        printf("Data preparation failed\n");
        return false;
    }

    // Write the JSON data into the string space provided by the caller
    snprintf(str, max_finfo_size, "JSON:%s\n", json_encoder_buffer(enc));
    json_encoder_destroy(enc);
    
    return true;
}
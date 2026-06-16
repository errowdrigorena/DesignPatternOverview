#include <AdapterPattern_common/LegacyThermometerCApi.h>

#include <stdlib.h>
#include <string.h>

struct legacy_thermometer_handle {
    char* id;
    double temperature;
};

static int active_handles = 0;

static char* duplicate_id(const char* id)
{
    const char* source = id == NULL ? "" : id;
    const size_t length = strlen(source);
    char* copy = malloc(length + 1);

    if(copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length + 1);
    return copy;
}

legacy_thermometer_handle* legacy_thermometer_create(const char* id, double initial_celsius)
{
    legacy_thermometer_handle* handle = malloc(sizeof(legacy_thermometer_handle));

    if(handle == NULL) {
        return NULL;
    }

    handle->id = duplicate_id(id);
    if(handle->id == NULL) {
        free(handle);
        return NULL;
    }

    handle->temperature = initial_celsius;
    ++active_handles;
    return handle;
}

void legacy_thermometer_destroy(legacy_thermometer_handle* handle)
{
    if(handle == NULL) {
        return;
    }

    free(handle->id);
    free(handle);
    --active_handles;
}

const char* legacy_thermometer_id(const legacy_thermometer_handle* handle)
{
    return handle == NULL ? "" : handle->id;
}

double legacy_thermometer_read_celsius(const legacy_thermometer_handle* handle)
{
    return handle == NULL ? 0.0 : handle->temperature;
}

void legacy_thermometer_calibrate(legacy_thermometer_handle* handle, double offset)
{
    if(handle == NULL) {
        return;
    }

    handle->temperature += offset;
}

int legacy_thermometer_active_handles()
{
    return active_handles;
}

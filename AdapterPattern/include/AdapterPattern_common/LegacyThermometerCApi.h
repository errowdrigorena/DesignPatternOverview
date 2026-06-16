#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct legacy_thermometer_handle legacy_thermometer_handle;

legacy_thermometer_handle* legacy_thermometer_create(const char* id, double initial_celsius);
void legacy_thermometer_destroy(legacy_thermometer_handle* handle);

const char* legacy_thermometer_id(const legacy_thermometer_handle* handle);
double legacy_thermometer_read_celsius(const legacy_thermometer_handle* handle);
void legacy_thermometer_calibrate(legacy_thermometer_handle* handle, double offset);

int legacy_thermometer_active_handles();

#ifdef __cplusplus
}
#endif

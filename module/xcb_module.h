/*
    New library for xcb like glib-2.0 has gmodule-2.0

    Copyright, Germany, 2025 Author Jens-Peter Eckervogt (aka DeafMan1983)
*/

#ifndef XCB_MODULE_H
#define XCB_MODULE_H

#include <xcb/xcbext.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define XCB_MODULE_MAJOR_VERSION 0
#define XCB_MODULE_MINOR_VERSION 01
#define XCB_MODULE_PATCH_VERSION 0

extern xcb_extension_t xcb_module_id;

typedef struct _xcb_module_t xcb_module_t;

typedef enum
{
    XCB_MODULE_LAZY  = 1 << 0,
    XCB_MODULE_LOCAL = 1 << 1,
} xcb_module_flags_t;

/**
 * Open a shared module with given flags
 */
xcb_module_t* xcb_module_open(const char* file_name, xcb_module_flags_t flags);

/**
 * Look up a symbol in a module
 * @return 1 on success, 0 on failure
 */
uint8_t xcb_module_symbol(xcb_module_t* module, const char* symbol_name, void** func_pointer);

/**
 * Get the last error string (from dlerror)
 */
const char* xcb_module_get_error(void);

/**
 * Close and free a module
 * @return 0 on success, -1 on error
 */
int xcb_module_destroy(xcb_module_t* module);

#ifdef __cplusplus
}
#endif

#endif // XCB_MODULE_H
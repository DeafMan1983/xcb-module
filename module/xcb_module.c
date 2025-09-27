#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "xcb_module.h"
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

xcb_extension_t xcb_module_id = { "MIT-MODULE", 0 };

struct _xcb_module_t
{
    char* file_name;
    void* handle;
};

xcb_module_t* xcb_module_open(const char* file_name, xcb_module_flags_t flags)
{
    if (!file_name) return NULL;

    xcb_module_t* module = calloc(1, sizeof(xcb_module_t));
    if (!module) return NULL;

    int dl_flags = 0;

    if (flags & XCB_MODULE_LAZY)
        dl_flags |= RTLD_LAZY;
    else
        dl_flags |= RTLD_NOW;

    if (flags & XCB_MODULE_LOCAL)
        dl_flags |= RTLD_LOCAL;
    else
        dl_flags |= RTLD_GLOBAL;

    #ifdef RTLD_DEEPBIND
    dl_flags |= RTLD_DEEPBIND;
    #endif

    module->handle = dlopen(file_name, dl_flags);
    if (!module->handle)
    {
        free(module);
        return NULL;
    }

    module->file_name = strdup(file_name);
    return module;
}

uint8_t xcb_module_symbol(xcb_module_t* module, const char* symbol_name, void** func_pointer)
{
    if (!module || !module->handle || !symbol_name || !func_pointer)
        return 0;

    dlerror(); // clear previous error
    void* sym = dlsym(module->handle, symbol_name);

    const char* err = dlerror();
    if (err != NULL)
    {
        *func_pointer = NULL;
        return 0;
    }

    *func_pointer = sym;
    return 1;
}

const char* xcb_module_get_error(void)
{
    return dlerror();
}

int xcb_module_destroy(xcb_module_t* module)
{
    if (!module) return -1;

    int res = 0;
    if (module->handle)
        res = dlclose(module->handle);

    free(module->file_name);
    free(module);
    return res;
}
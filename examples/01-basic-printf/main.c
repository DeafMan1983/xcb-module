#include <xcb/xcb_module.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    xcb_module_t* mod = xcb_module_open("libc.so.6", XCB_MODULE_LAZY);
    if (!mod)
    {
        perror("Error: libc doesn't load.\n");
        return 1;
    }

    typedef int (*pfn_printf)(const char* fmt, ...);
    pfn_printf func_ptr_printf;
    if (!xcb_module_symbol(mod, "printf", (void**)&func_ptr_printf))
    {
        fprintf(stderr, "Error: libc doesn't have public method (printf).\n");
        return 1;
    }

    func_ptr_printf("Hello, basic printf - Version: %i.%i.%i.\n", XCB_MODULE_MAJOR_VERSION, XCB_MODULE_MINOR_VERSION, XCB_MODULE_PATCH_VERSION);

    xcb_module_destroy(mod);

    return 0;
}
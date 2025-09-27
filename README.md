# Welcome to xcb-module ( successor of glib-20's gmodule-2.0 )

That is new extension for xcb and xcb-extensions

Clone this

```shell
git clone https://gitlab.com/deafman1983/xcb-module.git
cd xcb-module
mdkir build-gnu && cd build-gnu
cmake .. -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_INSTALL_LIBDIR=/usr/lib/x86_64-linux-gnu
cmake compile -b .
sudo cmake install -b .
```

Little example:

```c
xcb_module_t* mod = xcb_module_open("libc.so.6", XCB_MODULE_LAZY);
if (!mod)
{
    perror("Error: libc doesn't load.\n");
    return 1;
}
```
And you would like to create simple printf for example:
```c
typedef int (*pfn_printf)(const char* fmt, ...);
pfn_printf func_ptr_printf;
if (!xcb_module_symbol(mod, "printf", (void**)&func_ptr_printf))
{
    fprintf(stderr, "Error: libc doesn't have public method (printf).\n");
    return 1;
}

func_ptr_printf("Hello, basic printf - Version: %i.%i.%i.\n", XCB_MODULE_MAJOR_VERSION, XCB_MODULE_MINOR_VERSION, XCB_MODULE_PATCH_VERSION);
```

And destroy module:
```c
xcb_module_destroy(mod);
```

That is all. Enjoy your xcb development
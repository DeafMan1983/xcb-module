cmake_minimum_required(VERSION 3.15)
project(xcb-module VERSION 0.1.0 LANGUAGES C)

include(GNUInstallDirs)

# Options wie bei Autotools
option(ENABLE_STATIC "Build static library" ON)
option(ENABLE_SHARED "Build shared library" ON)

# Quellen
set(XCB_MODULE_SOURCES
    module/xcb_module.c
)

set(XCB_MODULE_HEADERS
    module/xcb_module.h
)

# Targets
if(ENABLE_SHARED)
    add_library(xcb-module SHARED ${XCB_MODULE_SOURCES})
    target_include_directories(xcb-module PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/module>
                                               $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/xcb>)
    target_link_libraries(xcb-module PUBLIC xcb dl)
    set_target_properties(xcb-module PROPERTIES
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION}
        OUTPUT_NAME "xcb-module"
    )
    install(TARGETS xcb-module
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endif()

if(ENABLE_STATIC)
    add_library(xcb-module-static STATIC ${XCB_MODULE_SOURCES})
    target_include_directories(xcb-module-static PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/module>
                                                        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/xcb>)
    target_link_libraries(xcb-module-static PUBLIC xcb dl)
    set_target_properties(xcb-module-static PROPERTIES
        OUTPUT_NAME "xcb-module"
    )
    install(TARGETS xcb-module-static
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endif()

# Installiere Header
install(FILES ${XCB_MODULE_HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xcb)

# --- pkg-config Support ---
include(CMakePackageConfigHelpers)

set(prefix      ${CMAKE_INSTALL_PREFIX})
set(exec_prefix ${CMAKE_INSTALL_PREFIX})
set(libdir      ${CMAKE_INSTALL_LIBDIR})
set(includedir  ${CMAKE_INSTALL_INCLUDEDIR}/xcb)
set(PACKAGE_VERSION ${PROJECT_VERSION})

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/xcb-module.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/xcb-module.pc
    @ONLY
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/xcb-module.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
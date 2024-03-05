cmake_minimum_required(VERSION 3.20)
project(LIBDXF)

set(LIBDXF_VERSION_MAJOR 1)
set(LIBDXF_VERSION_MINOR 0)
set(LIBDXF_VERSION_REV 1)
set(LIBDXF_VERSION_BUILD 0)

set(LIBDXF_VERSION 1.0.1.0)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dxf_config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/dxf_config.h)

add_library(dxf SHARED dxf_reader.c dxf_writer.c dxf_document.c)

if(MSVC)
    target_compile_definitions(dxf PRIVATE DXF_DYN_LINK)
    target_compile_definitions(dxf PRIVATE DXF_SOURCE)
    target_compile_definitions(dxf PRIVATE _USE_MATH_DEFINES)
elseif()
endif()

target_include_directories(dxf PUBLIC 
    ${CMAKE_CURRENT_BINARY_DIR}    
)
cmake_minimum_required(VERSION 3.20)
project(LIBDXF)

add_library(dxf SHARED dxf.c dxf_reader.c dxf_writer.c)

if(MSVC)
    target_compile_definitions(dxf PRIVATE DXF_DYN_LINK)
    target_compile_definitions(dxf PRIVATE DXF_SOURCE)
elseif()
endif()
cmake_minimum_required(VERSION 3.20)
project(DXF)


add_library(dxf SHARED dxf.c dxf_reader.c dxf_writer.c)
cmake_minimum_required(VERSION 3.10)
project(NURBS LANGUAGES C)
set(CMAKE_C_STANDARD 99)

option(SUPPORT_NURBS_IMAGE "save nurbs curve to png" OFF)

if(SUPPORT_NURBS_IMAGE)
    find_package(PNG REQUIRED)
endif()

add_library(nurbs 
    nurbs.c
    nurbs_analyze.c
    nurbs_curveboundingbox.c
    nurbs_divide.c
    nurbs_eval.c
    nurbs_intersect.c
    nurbs_make.c
    nurbs_mat.c
    nurbs_modify.c
    nurbs_tess.c
    nurbs_vec.c
)


target_compile_definitions(nurbs PUBLIC _USE_MATH_DEFINES)
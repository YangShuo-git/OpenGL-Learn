cmake_minimum_required(VERSION 3.22.1)

project("GLRender")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions -Wall")

set(OPENGL_LIB GLESv3)
set(GLM_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libglm)
set(STBIMG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libstbImage)

include_directories(${GLM_DIR}/include)
include_directories(${STBIMG_DIR}/include)

aux_source_directory(. DIR_SRCS)

add_library(${CMAKE_PROJECT_NAME} SHARED
        ${DIR_SRCS}
    )

target_link_libraries(${CMAKE_PROJECT_NAME}
        ${OPENGL_LIB}

        android
        log)


cmake_minimum_required(VERSION 3.22.1)


project("GLRender")

SET(GLM_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libglm)
SET(STBIMG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/libstbImage)

INCLUDE_DIRECTORIES(${GLM_DIR}/include)
INCLUDE_DIRECTORIES(${STBIMG_DIR}/include)

aux_source_directory(. DIR_SRCS)

add_library(${CMAKE_PROJECT_NAME} SHARED
        ${DIR_SRCS}
    )

target_link_libraries(${CMAKE_PROJECT_NAME}
        -lGLESv1_CM
        -lGLESv2

        android
        log)

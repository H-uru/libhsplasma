cmake_minimum_required(VERSION 3.1)
project(libhsplasma)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

option(ENABLE_SSE2 "Build with SSE2 CPU instructions" ON)

set(CMAKE_C_FLAGS_DEBUG "-DDEBUG ${CMAKE_C_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG ${CMAKE_CXX_FLAGS_DEBUG}")
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR
        CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set(WARNING_FLAGS "-Wall -Wextra -Wno-unused-parameter")
    set(CMAKE_CXX_FLAGS "${WARNING_FLAGS} ${CMAKE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "${WARNING_FLAGS} ${CMAKE_C_FLAGS}")
    if(ENABLE_SSE2)
        set(CMAKE_CXX_FLAGS "-msse2 ${CMAKE_CXX_FLAGS}")
        set(CMAKE_C_FLAGS "-msse2 ${CMAKE_C_FLAGS}")
    endif()
endif()

if(APPLE)
    add_definitions("-DMACOSX")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
endif()

if(MSVC)
    add_definitions("-D_CRT_SECURE_NO_WARNINGS")
    set(CMAKE_CXX_FLAGS "/bigobj /wd4996 /wd4244 /wd4251 /wd4351 ${CMAKE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "/wd4996 /wd4244 /wd4251 /wd4351 ${CMAKE_C_FLAGS}")
endif()

# Turn everything on by default
option(ENABLE_PYTHON "Build HSPlasma Python integration" ON)
option(ENABLE_TOOLS "Build the HSPlasma tools" ON)
option(ENABLE_NET "Build HSPlasmaNet" ON)
option(ENABLE_PHYSX "Build with PhysX Support" ON)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

try_compile(NEED_SIZE_T_OVERLOAD ${PROJECT_BINARY_DIR}
            ${PROJECT_SOURCE_DIR}/cmake/check_size_t_overload.cpp)

configure_file(${PROJECT_SOURCE_DIR}/cmake/PlasmaConfig.h.in
               ${PROJECT_BINARY_DIR}/PlasmaConfig.h)
include_directories(${PROJECT_BINARY_DIR})

find_package(string_theory 2.0 REQUIRED)

add_subdirectory(core)

if(ENABLE_PYTHON)
    add_subdirectory(Python)
endif()

if(ENABLE_TOOLS)
    add_subdirectory(Tools)
endif()

if(ENABLE_NET)
    add_subdirectory(net)
endif()

install(EXPORT HSPlasma-targets DESTINATION share/cmake/HSPlasma)

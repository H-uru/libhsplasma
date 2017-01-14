project(libhsplasma)
cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_C_FLAGS_DEBUG "-DDEBUG ${CMAKE_C_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG ${CMAKE_CXX_FLAGS_DEBUG}")
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR
        CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set(WARNING_FLAGS "-Wall -Wextra -Wno-unused-parameter")
    set(CMAKE_CXX_FLAGS "-std=c++0x ${WARNING_FLAGS} ${CMAKE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "${WARNING_FLAGS} ${CMAKE_C_FLAGS}")
endif()

if(APPLE)
    add_definitions("-DMACOSX")
    set(CMAKE_CXX_FLAGS "-stdlib=libc++ ${CMAKE_CXX_FLAGS}")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
endif()

if(MSVC)
    add_definitions("-D_CRT_SECURE_NO_WARNINGS")
    set(CMAKE_CXX_FLAGS "/wd4996 /wd4244 /wd4251 ${CMAKE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "/wd4996 /wd4244 /wd4251 ${CMAKE_C_FLAGS}")
endif()

# Python is disabled by default because most projects don't need it
# Tools are still enabled because they're fast and occasionally useful
option(ENABLE_PYTHON "Build HSPlasma Python integration" OFF)
option(ENABLE_TOOLS "Build the HSPlasma tools" ON)
option(ENABLE_NET "Build HSPlasmaNet" ON)
option(ENABLE_PHYSX "Build with PhysX Support" ON)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

try_compile(HAVE_OVERRIDE ${PROJECT_BINARY_DIR}
            ${PROJECT_SOURCE_DIR}/cmake/check_override.cpp)
try_compile(HAVE_NOEXCEPT ${PROJECT_BINARY_DIR}
            ${PROJECT_SOURCE_DIR}/cmake/check_noexcept.cpp)

configure_file(${PROJECT_SOURCE_DIR}/cmake/PlasmaConfig.h.in
               ${PROJECT_BINARY_DIR}/PlasmaConfig.h)
include_directories(${PROJECT_BINARY_DIR})

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

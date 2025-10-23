cmake_minimum_required(VERSION 3.12)
project(libhsplasma)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(CheckCXXCompilerFlag)
include(CMakePushCheckState)

# Note that recent versions of MSVC default to producing SSE2 instructions for x86
# targets, so it's ok to simply fail this check for MSVC. It will always produce SSE2
# code for x86 targets in that case.
set(SSE2_COMPILER_FLAGS "-msse2")
CMAKE_PUSH_CHECK_STATE()
set(CMAKE_REQUIRED_FLAGS "-Werror")
check_cxx_compiler_flag("${SSE2_COMPILER_FLAGS}" SSE2_SUPPORTED)
CMAKE_POP_CHECK_STATE()

include(CMakeDependentOption)
cmake_dependent_option(
    ENABLE_SSE2
    "Build with SSE2 CPU instructions"
    ON
    SSE2_SUPPORTED
    OFF
)

include(TestBigEndian)
test_big_endian(BIG_ENDIAN)
if(BIG_ENDIAN)
    add_definitions("-DHS_BIG_ENDIAN")
endif()

set(CMAKE_C_FLAGS_DEBUG "-DDEBUG ${CMAKE_C_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG ${CMAKE_CXX_FLAGS_DEBUG}")
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR
        CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set(WARNING_FLAGS "-Wall -Wextra -Wno-unused-parameter")
    set(CMAKE_CXX_FLAGS "${WARNING_FLAGS} ${CMAKE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "${WARNING_FLAGS} ${CMAKE_C_FLAGS}")
endif()
if(ENABLE_SSE2)
    set(CMAKE_CXX_FLAGS "${SSE2_COMPILER_FLAGS} ${CMAKE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "${SSE2_COMPILER_FLAGS} ${CMAKE_C_FLAGS}")
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

add_subdirectory(Tests)

include(FeatureSummary)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

cmake_minimum_required(VERSION 3.12)
project(libhsplasma)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

option(ENABLE_SSE2 "Build with SSE2 CPU instructions" ON)

# There are lots of variants of Clang, so just match it instead
# of trying to hardwire them all in a generator expression.
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR
        CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    set(COMPILER_USES_GCC_FLAGS TRUE)
endif()

add_library(HSPlasmaCompilerInterface INTERFACE)
target_compile_definitions(HSPlasmaCompilerInterface
    INTERFACE
        $<$<CONFIG:Debug>:DEBUG>
        $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
        $<$<BOOL:${APPLE}>:MACOSX>
)
target_compile_options(HSPlasmaCompilerInterface
    INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:/bigobj /wd4996 /wd4244 /wd4251 /wd4351>
        $<$<BOOL:${COMPILER_USES_GCC_FLAGS}>:-Wall -Wextra -Wno-unused-parameter>
        $<$<AND:$<BOOL:${ENABLE_SSE2}>,$<BOOL:${COMPILER_USES_GCC_FLAGS}>>:-msse2>
)

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

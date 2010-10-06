project(PLASMA)
cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PLASMA_SOURCE_DIR}/cmake")

set(CMAKE_C_FLAGS_DEBUG "-DDEBUG ${CMAKE_C_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG ${CMAKE_CXX_FLAGS_DEBUG}")
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-Wall ${CMAKE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "-Wall ${CMAKE_C_FLAGS}")
endif()

if(APPLE)
    add_definitions("-DMACOSX")
endif()

if(MSVC)
    add_definitions("-D_CRT_SECURE_NO_WARNINGS")
    set(CMAKE_CXX_FLAGS "/wd4996 /wd4244 ${CMAKE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "/wd4996 /wd4244 ${CMAKE_C_FLAGS}")
endif()

# Python is disabled by default because most projects don't need it
# Tools are still enabled because they're fast and occasionally useful
option(DISABLE_PYTHON "Don't build HSPlasma Python integration" ON)
option(DISABLE_TOOLS "Don't build the HSPlasma tools" OFF)
option(DISABLE_NET "Don't build HSPlasmaNet" OFF)

add_subdirectory(core)

if(NOT DISABLE_PYTHON)
    add_subdirectory(Python)
endif()

if(NOT DISABLE_TOOLS)
    add_subdirectory(Tools)
endif()

if(NOT DISABLE_NET)
    add_subdirectory(net)
endif()

install(EXPORT HSPlasma-targets DESTINATION share/cmake/HSPlasma)

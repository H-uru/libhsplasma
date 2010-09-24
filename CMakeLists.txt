project(PLASMA)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_C_FLAGS_DEBUG "-DDEBUG ${CMAKE_C_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG ${CMAKE_CXX_FLAGS_DEBUG}")
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-Wall ${CMAKE_CXX_FLAGS}")
  set(CMAKE_C_FLAGS "-Wall ${CMAKE_C_FLAGS}")
endif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

# Python is disabled by default because most projects don't need it
# Tools are still enabled because they're fast and occasionally useful
option(DISABLE_PYTHON "Don't build HSPlasma Python integration" ON)
option(DISABLE_TOOLS "Don't build the HSPlasma tools" OFF)
option(DISABLE_NET "Don't build HSPlasmaNet" OFF)

add_subdirectory(core)

if(NOT DISABLE_PYTHON)
  add_subdirectory(Python)
endif(NOT DISABLE_PYTHON)

if(NOT DISABLE_TOOLS)
  add_subdirectory(Tools)
endif(NOT DISABLE_TOOLS)

if(NOT DISABLE_NET)
  add_subdirectory(net)
endif(NOT DISABLE_NET)

install(EXPORT HSPlasma-targets DESTINATION share/cmake/HSPlasma)

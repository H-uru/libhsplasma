project(PLASMA)
cmake_minimum_required(VERSION 2.6)

option(DISABLE_PYTHON "Don't build HSPlasma Python integration")
option(DISABLE_TOOLS "Don't build the HSPlasma tools")
option(DISABLE_NET "Don't build HSPlasmaNet")

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

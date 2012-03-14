include_directories(${PLASMA_SOURCE_DIR}/core)

try_compile(HAVE_NON_CONST_DIRENT ${PLASMA_BINARY_DIR}
            ${PLASMA_SOURCE_DIR}/Misc/cmake_CheckDirent.cpp
            OUTPUT_VARIABLE OUTPUT)
if(NOT HAVE_NON_CONST_DIRENT)
    add_definitions("-DNEED_CONST_DIRENT")
endif()

macro(plasma_tool NAME)
    add_executable(${NAME} src/${NAME}.cpp)
    target_link_libraries(${NAME} HSPlasma)
    install(TARGETS ${NAME} RUNTIME DESTINATION bin)
endmacro(plasma_tool)

plasma_tool(PageConvert)
plasma_tool(PlasmaCrypt)
plasma_tool(PrpPack)
plasma_tool(PrcExtract)
plasma_tool(PageList)
plasma_tool(prcc)
plasma_tool(prcdc)
plasma_tool(Prp2Obj)
plasma_tool(PyPack)
plasma_tool(prpmod)
plasma_tool(prpgrep)
plasma_tool(PlasmaSum)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    option(ENABLE_PRP_FUSE "Enable the prp-fuse tool. EXPERIMENTAL!" OFF)
    if(ENABLE_PRP_FUSE)
        plasma_tool(prp-fuse)
        target_link_libraries(prp-fuse fuse)
    endif(ENABLE_PRP_FUSE)
endif(CMAKE_SYSTEM_NAME STREQUAL "Linux")

install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/eoaedit
                 ${CMAKE_CURRENT_SOURCE_DIR}/uruedit
        DESTINATION bin
)

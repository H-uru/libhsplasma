try_compile(DIRENT_IS_CONST ${PROJECT_BINARY_DIR}
            ${PROJECT_SOURCE_DIR}/cmake/check_dirent.cpp
            OUTPUT_VARIABLE OUTPUT)
if(DIRENT_IS_CONST)
    add_definitions("-DDIRENT_IS_CONST")
endif()

macro(plasma_tool NAME)
    add_executable(${NAME} src/${NAME}.cpp)
    target_link_libraries(${NAME} HSPlasma ${STRING_THEORY_LIBRARIES})
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

install(PROGRAMS ${CMAKE_CURRENT_SOURCE_DIR}/eoaedit
                 ${CMAKE_CURRENT_SOURCE_DIR}/uruedit
        DESTINATION bin
)

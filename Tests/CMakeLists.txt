find_package(Catch2 3.4 QUIET)
if(NOT Catch2_FOUND)
    # Force Catch2 to be built as a static lib
    set(BUILD_SHARED_LIBS__save ${BUILD_SHARED_LIBS})
    set(BUILD_SHARED_LIBS OFF)

    include(FetchContent)
    FetchContent_Declare(Catch2
        GIT_REPOSITORY  https://github.com/catchorg/Catch2.git
        GIT_TAG         v3.11.0
    )
    FetchContent_MakeAvailable(Catch2)
    list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/contrib")

    set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS__save})
endif()

set(test_SOURCES
    Test_Location.cpp
)
add_executable(test_HSPlasma ${test_SOURCES})
target_link_libraries(test_HSPlasma PRIVATE Catch2::Catch2WithMain HSPlasma)

if(WIN32 AND BUILD_SHARED_LIBS)
    # Catch2 needs the HSPlasma DLL available to run <test_executable> --list-tests
    add_custom_command(
        TARGET test_HSPlasma PRE_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:HSPlasma> $<TARGET_FILE_DIR:test_HSPlasma>
    )
endif()

# Integrate with CTest so we can use the built-in test targets
include(CTest)
include(Catch)
catch_discover_tests(test_HSPlasma)

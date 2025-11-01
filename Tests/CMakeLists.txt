include(FetchContent)
FetchContent_Declare(Catch2
    GIT_REPOSITORY  https://github.com/catchorg/Catch2.git
    GIT_TAG         v2.13.10
)
FetchContent_MakeAvailable(Catch2)

set(test_SOURCES
    catch2_main.cpp
    Test_Location.cpp
)
add_executable(test_HSPlasma ${test_SOURCES})
target_link_libraries(test_HSPlasma PRIVATE Catch2::Catch2 HSPlasma)

# Integrate with CTest so we can use the built-in test targets
list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/contrib")
include(CTest)
include(Catch)
catch_discover_tests(test_HSPlasma)

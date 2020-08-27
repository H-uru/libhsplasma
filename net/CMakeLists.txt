find_package(OpenSSL REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../core)
include_directories(${OPENSSL_INCLUDE_DIR})

if(NOT OPENSSL_FOUND)
    message(FATAL_ERROR "OpenSSL has not been found. You will need it to continue build with hsPlasmaNet enabled. Please either install OpenSSL or disable hsPlasmaNet.")
endif(NOT OPENSSL_FOUND)

if(WIN32)
    # Windows XP. Seems a reasonable enough target.
    add_definitions("-DWINVER=0x0501")
endif(WIN32)

if(${CMAKE_SYSTEM_NAME} MATCHES "SunOS")
    add_definitions("-DNEED_FILIO")
endif()

if(PLASMANET_COMMDEBUG)
    add_definitions("-DCOMMDEBUG")
endif()

add_definitions(-DBUILD_PLASMANET_DLL)

set(PN_AUTH_SOURCES
    auth/AuthMessages.cpp
    auth/pnAuthClient.cpp
    auth/pnVaultNode.cpp
)
set(PN_AUTH_HEADERS
    auth/AuthMessages.h
    auth/pnAuthClient.h
    auth/pnVaultNode.h
    auth/pnVaultNodeTypes.hpp
)

set(PN_CRYPT_SOURCES
    crypt/pnBigInteger.cpp
    crypt/pnRC4.cpp
    crypt/pnSha1.cpp
)
set(PN_CRYPT_HEADERS
    crypt/pnBigInteger.h
    crypt/pnRC4.h
    crypt/pnSha1.h
)

set(PN_FILE_SOURCES
    file/pnFileClient.cpp
)
set(PN_FILE_HEADERS
    file/FileMessages.h
    file/pnFileClient.h
)

set(PN_GAME_SOURCES
    game/GameMessages.cpp
    game/pnGameClient.cpp
)
set(PN_GAME_HEADERS
    game/GameMessages.h
    game/pnGameClient.h
)

set(PN_GATE_SOURCES
    gate/GateKeeperMessages.cpp
    gate/pnGateKeeperClient.cpp
)
set(PN_GATE_HEADERS
    gate/GateKeeperMessages.h
    gate/pnGateKeeperClient.h
)

set(PN_SOURCES
    pnClient.cpp
    pnNetMsg.cpp
    pnSocket.cpp
    pnSocketInterface.cpp
)
set(PN_HEADERS
    Protocol.h
    pnClient.h
    pnNetMsg.h
    pnSocket.h
    pnSocketInterface.h
)

add_library(HSPlasmaNet
            ${PN_AUTH_SOURCES}  ${PN_AUTH_HEADERS}
            ${PN_CRYPT_SOURCES} ${PN_CRYPT_HEADERS}
            ${PN_FILE_SOURCES}  ${PN_FILE_HEADERS}
            ${PN_GAME_SOURCES}  ${PN_GAME_HEADERS}
            ${PN_GATE_SOURCES}  ${PN_GATE_HEADERS}
            ${PN_SOURCES}       ${PN_HEADERS}
)
target_link_libraries(HSPlasmaNet HSPlasma ${STRING_THEORY_LIBRARIES})
if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "SunOS")
    target_link_libraries(HSPlasmaNet ${OPENSSL_LIBRARIES})
endif()

if(WIN32)
    target_link_libraries(HSPlasmaNet crypt32)
    target_link_libraries(HSPlasmaNet ws2_32)
endif(WIN32)

target_include_directories(HSPlasmaNet PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
                           $<INSTALL_INTERFACE:include/HSPlasmaNet>)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libhsplasmanet.pc.in.cmake ${CMAKE_CURRENT_BINARY_DIR}/libhsplasmanet.pc @ONLY)

# Package installation
install(TARGETS HSPlasmaNet
        EXPORT HSPlasma-targets
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

include(CMakePackageConfigHelpers)
configure_package_config_file(HSPlasmaNetConfig.cmake.in
                              ${CMAKE_CURRENT_BINARY_DIR}/HSPlasmaNetConfig.cmake
                              INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/share/cmake/HSPlasmaNet)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/HSPlasmaNetConfig.cmake
        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/cmake/HSPlasmaNet)

install(FILES ${PN_AUTH_HEADERS} DESTINATION include/HSPlasmaNet/auth)
install(FILES ${PN_CRYPT_HEADERS} DESTINATION include/HSPlasmaNet/crypt)
install(FILES ${PN_FILE_HEADERS} DESTINATION include/HSPlasmaNet/file)
install(FILES ${PN_GAME_HEADERS} DESTINATION include/HSPlasmaNet/game)
install(FILES ${PN_GATE_HEADERS} DESTINATION include/HSPlasmaNet/gate)
install(FILES ${PN_HEADERS} DESTINATION include/HSPlasmaNet)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libhsplasmanet.pc DESTINATION lib/pkgconfig)

# Visual studio source grouping
source_group("auth" FILES ${PN_AUTH_SOURCES} ${PN_AUTH_HEADERS})
source_group("crypt" FILES ${PN_CRYPT_SOURCES} ${PN_CRYPT_HEADERS})
source_group("file" FILES ${PN_FILE_SOURCES} ${PN_FILE_HEADERS})
source_group("game" FILES ${PN_GAME_SOURCES} ${PN_GAME_HEADERS})
source_group("gate" FILES ${PN_GATE_SOURCES} ${PN_GATE_HEADERS})
source_group("gate" FILES ${PN_GATE_SOURCES} ${PN_GATE_HEADERS})

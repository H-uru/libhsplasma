find_package(OpenSSL)

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

set(PN_AUTH_SRCS
    auth/AuthMessages.cpp
    auth/pnAuthClient.cpp
    auth/pnVaultNode.cpp
)
set(PN_AUTH_HDRS
    auth/AuthMessages.h
    auth/pnAuthClient.h
    auth/pnVaultNode.h
    auth/pnVaultNodeTypes.hpp
)

set(PN_CRYPT_SRCS
    crypt/pnBigInteger.cpp
    crypt/pnRC4.cpp
    crypt/pnSha1.cpp
)
set(PN_CRYPT_HDRS
    crypt/pnBigInteger.h
    crypt/pnRC4.h
    crypt/pnSha1.h
)

set(PN_FILE_SRCS
    file/pnFileClient.cpp
)
set(PN_FILE_HDRS
    file/FileMessages.h
    file/pnFileClient.h
)

set(PN_GAME_SRCS
    game/GameMessages.cpp
    game/pnGameClient.cpp
)
set(PN_GAME_HDRS
    game/GameMessages.h
    game/pnGameClient.h
)

set(PN_GATE_SRCS
    gate/GateKeeperMessages.cpp
    gate/pnGateKeeperClient.cpp
)
set(PN_GATE_HDRS
    gate/GateKeeperMessages.h
    gate/pnGateKeeperClient.h
)

set(PN_SRCS
    pnClient.cpp
    pnNetMsg.cpp
    pnSocket.cpp
    pnSocketInterface.cpp
)
set(PN_HDRS
    Protocol.h
    pnClient.h
    pnNetMsg.h
    pnSocket.h
    pnSocketInterface.h
)

add_library(HSPlasmaNet
            ${PN_AUTH_SRCS}  ${PN_AUTH_HDRS}
            ${PN_CRYPT_SRCS} ${PN_CRYPT_HDRS}
            ${PN_FILE_SRCS}  ${PN_FILE_HDRS}
            ${PN_GAME_SRCS}  ${PN_GAME_HDRS}
            ${PN_GATE_SRCS}  ${PN_GATE_HDRS}
            ${PN_SRCS}       ${PN_HDRS}
)
target_link_libraries(HSPlasmaNet HSPlasma ${STRING_THEORY_LIBRARIES})
if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "SunOS")
    target_link_libraries(HSPlasmaNet ${OPENSSL_LIBRARIES})
endif()

if(WIN32)
    target_link_libraries(HSPlasmaNet ws2_32)
endif(WIN32)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libhsplasmanet.pc.in.cmake ${CMAKE_CURRENT_BINARY_DIR}/libhsplasmanet.pc @ONLY)

# Package installation
install(TARGETS HSPlasmaNet
        EXPORT HSPlasma-targets
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
install(FILES HSPlasmaNetConfig.cmake DESTINATION share/cmake/HSPlasmaNet)
install(FILES ${PN_AUTH_HDRS} DESTINATION include/HSPlasmaNet/auth)
install(FILES ${PN_CRYPT_HDRS} DESTINATION include/HSPlasmaNet/crypt)
install(FILES ${PN_FILE_HDRS} DESTINATION include/HSPlasmaNet/file)
install(FILES ${PN_GAME_HDRS} DESTINATION include/HSPlasmaNet/game)
install(FILES ${PN_GATE_HDRS} DESTINATION include/HSPlasmaNet/gate)
install(FILES ${PN_HDRS} DESTINATION include/HSPlasmaNet)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libhsplasmanet.pc DESTINATION lib/pkgconfig)

# Visual studio source grouping
source_group("auth" FILES ${PN_AUTH_SRCS} ${PN_AUTH_HDRS})
source_group("crypt" FILES ${PN_CRYPT_SRCS} ${PN_CRYPT_HDRS})
source_group("file" FILES ${PN_FILE_SRCS} ${PN_FILE_HDRS})
source_group("game" FILES ${PN_GAME_SRCS} ${PN_GAME_HDRS})
source_group("gate" FILES ${PN_GATE_SRCS} ${PN_GATE_HDRS})
source_group("gate" FILES ${PN_GATE_SRCS} ${PN_GATE_HDRS})

if(NOT PHYSX_SDK_PATH)
    find_path(PHYSX_SDK_PATH Foundation/include/Nx.h)
elseif(PHYSX_SDK_PATH AND PHYSX_LOADER_LIBRARY)
    set(PHYSX_FIND_QUIETLY TRUE)
endif()

if(PHYSX_SDK_PATH)
    set(PHYSX_FOUNDATION_INCLUDE_DIR "${PHYSX_SDK_PATH}/Foundation/include")
    set(PHYSX_COOKING_INCLUDE_DIR "${PHYSX_SDK_PATH}/Cooking/include")
    set(PHYSX_FRAMEWORK_INCLUDE_DIR "${PHYSX_SDK_PATH}/Framework/include")
    set(PHYSX_CHARACTER_INCLUDE_DIR "${PHYSX_SDK_PATH}/NxCharacter/include")
    set(PHYSX_EXTENSIONS_INCLUDE_DIR "${PHYSX_SDK_PATH}/NxExtensions/include")
    set(PHYSX_PHYSICS_INCLUDE_DIR "${PHYSX_SDK_PATH}/Physics/include")
    set(PHYSX_LOADER_INCLUDE_DIR "${PHYSX_SDK_PATH}/PhysXLoader/include")

    set(PHYSX_INCLUDE_DIRS
        ${PHYSX_COOKING_INCLUDE_DIR}
        ${PHYSX_FOUNDATION_INCLUDE_DIR}
        ${PHYSX_FRAMEWORK_INCLUDE_DIR}
        ${PHYSX_CHARACTER_INCLUDE_DIR}
        ${PHYSX_EXTENSIONS_INCLUDE_DIR}
        ${PHYSX_PHYSICS_INCLUDE_DIR}
        ${PHYSX_LOADER_INCLUDE_DIR}
    )
endif()

#TODO: Make find paths work for Linux builds too
find_library(PHYSX_COOKING_LIBRARY NAMES NxCooking
             PATHS "${PHYSX_SDK_PATH}/lib/win32")
find_library(PHYSX_CHARACTER_LIBRARY NAMES NxCharacter
             PATHS "${PHYSX_SDK_PATH}/lib/win32")
find_library(PHYSX_EXTENSIONS_LIBRARY NAMES NxExtensions
             PATHS "${PHYSX_SDK_PATH}/lib/win32")
find_library(PHYSX_LOADER_LIBRARY NAMES PhysXLoader
             PATHS "${PHYSX_SDK_PATH}/lib/win32")

set(PHYSX_LIBRARIES
    ${PHYSX_COOKING_LIBRARY}
    ${PHYSX_CHARACTER_LIBRARY}
    ${PHYSX_EXTENSIONS_LIBRARY}
    ${PHYSX_LOADER_LIBRARY}
)

mark_as_advanced(PHYSX_COOKING_LIBRARY
                 PHYSX_CHARACTER_LIBRARY
                 PHYSX_EXTENSIONS_LIBRARY
                 PHYSX_LOADER_LIBRARY)

if(PHYSX_SDK_PATH AND PHYSX_LOADER_LIBRARY)
    set(PHYSX_FOUND TRUE)
endif()

if (PHYSX_FOUND)
    if(NOT PHYSX_FIND_QUIETLY)
        message(STATUS "Found PhysX: ${PHYSX_SDK_PATH}")
    endif()
else()
    if(PHYSX_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find PhysX.  Please set your PHYSX_SDK_PATH appropriately and try again")
    endif()
endif()

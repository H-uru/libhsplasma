get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(${SELF_DIR}/HSPlasma-targets.cmake)
get_filename_component(HSPlasma_INCLUDE_DIRS "${SELF_DIR}/../../../include/HSPlasma" ABSOLUTE)

get_filename_component(SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(${SELF_DIR}/HSPlasma-targets.cmake)
# uncomment when header install is supported
get_filename_component(Plasma_INCLUDE_DIRS "${SELF_DIR}/../../../include/HSPlasma" ABSOLUTE)

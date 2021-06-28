#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "mogen_p2p_joint::mogen_p2p_joint" for configuration "Release"
set_property(TARGET mogen_p2p_joint::mogen_p2p_joint APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(mogen_p2p_joint::mogen_p2p_joint PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/mogen_p2p_joint/libmogen_p2p_joint.so"
  IMPORTED_SONAME_RELEASE "libmogen_p2p_joint.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS mogen_p2p_joint::mogen_p2p_joint )
list(APPEND _IMPORT_CHECK_FILES_FOR_mogen_p2p_joint::mogen_p2p_joint "${_IMPORT_PREFIX}/mogen_p2p_joint/libmogen_p2p_joint.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

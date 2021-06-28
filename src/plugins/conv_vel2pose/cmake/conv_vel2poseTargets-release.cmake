#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "conv_vel2pose::conv_vel2pose" for configuration "Release"
set_property(TARGET conv_vel2pose::conv_vel2pose APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(conv_vel2pose::conv_vel2pose PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/conv_vel2pose/libconv_vel2pose.so"
  IMPORTED_SONAME_RELEASE "libconv_vel2pose.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS conv_vel2pose::conv_vel2pose )
list(APPEND _IMPORT_CHECK_FILES_FOR_conv_vel2pose::conv_vel2pose "${_IMPORT_PREFIX}/conv_vel2pose/libconv_vel2pose.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

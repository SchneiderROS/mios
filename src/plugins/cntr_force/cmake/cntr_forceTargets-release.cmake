#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cntr_force::cntr_force" for configuration "Release"
set_property(TARGET cntr_force::cntr_force APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(cntr_force::cntr_force PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/cntr_force/libcntr_force.so"
  IMPORTED_SONAME_RELEASE "libcntr_force.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS cntr_force::cntr_force )
list(APPEND _IMPORT_CHECK_FILES_FOR_cntr_force::cntr_force "${_IMPORT_PREFIX}/cntr_force/libcntr_force.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

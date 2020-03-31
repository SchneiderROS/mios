#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "wave_variables::wave_variables" for configuration "Release"
set_property(TARGET wave_variables::wave_variables APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(wave_variables::wave_variables PROPERTIES
  IMPORTED_LOCATION_RELEASE "/home/lars/repos/simulink_pipeline/install/wave_variables/libwave_variables.so"
  IMPORTED_SONAME_RELEASE "libwave_variables.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS wave_variables::wave_variables )
list(APPEND _IMPORT_CHECK_FILES_FOR_wave_variables::wave_variables "/home/lars/repos/simulink_pipeline/install/wave_variables/libwave_variables.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

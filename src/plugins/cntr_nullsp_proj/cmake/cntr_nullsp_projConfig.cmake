# Copyright (c) 2021 - present, Lars Johannsmeier
# All rights reserved.
# contact: lars.johannsmeier@tum.de


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was simulink_pipelineConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../home/lars/repos/simulink_pipeline/install" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

set(config_targets_file cntr_nullsp_projTargets.cmake)

include(CMakeFindDependencyMacro)

find_dependency(Eigen3 REQUIRED)

include("${CMAKE_CURRENT_LIST_DIR}/${config_targets_file}")

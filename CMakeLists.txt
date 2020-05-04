cmake_minimum_required(VERSION 3.10.2)
project(mios
    LANGUAGES CXX
    )


set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_LINK_DEPENDS_NO_SHARED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wreturn-type -Wno-error=deprecated-declarations")
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

include(cotire)

find_package(Eigen3 REQUIRED)
find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIRS})
include_directories(${LIBBSONCXX_INCLUDE_DIRS})

include_directories(
    ${CMAKE_SOURCE_DIR}/core/include
    ${CMAKE_SOURCE_DIR}/skill/include
    ${CMAKE_SOURCE_DIR}/task/include
    ${CMAKE_SOURCE_DIR}/interface/include
    ${CMAKE_SOURCE_DIR}/led_pattern/include
    ${CMAKE_SOURCE_DIR}/led_pattern/patterns
    ${CMAKE_SOURCE_DIR}/manipulation_primitive/include
    ${CMAKE_SOURCE_DIR}/knowledge_base/include
    ${CMAKE_SOURCE_DIR}/telemetry/include
    ${CMAKE_SOURCE_DIR}/utils/include
    ${CMAKE_SOURCE_DIR}/event_publisher/include)

add_subdirectory(plugins/mogen_p2p)
include_directories(${mogen_p2p_INCLUDE_DIRS})
find_library(mogen_p2p NAMES mogen_p2p HINTS ${mogen_p2p_LIBRARIES})

add_subdirectory(plugins/mogen_p2p_joint)
include_directories(${mogen_p2p_joint_INCLUDE_DIRS})
find_library(mogen_p2p_joint NAMES mogen_p2p_joint HINTS ${mogen_p2p_joint_LIBRARIES})

add_subdirectory(plugins/cntr_joint_var_imp)
include_directories(${cntr_joint_var_imp_INCLUDE_DIRS})
find_library(cntr_joint_var_imp NAMES cntr_joint_var_imp HINTS ${cntr_joint_var_imp_LIBRARIES})

add_subdirectory(plugins/cntr_aic)
include_directories(${cntr_aic_INCLUDE_DIRS})
find_library(cntr_aic NAMES cntr_aic HINTS ${cntr_aic_LIBRARIES})

add_subdirectory(plugins/cntr_force)
include_directories(${cntr_force_INCLUDE_DIRS})
find_library(cntr_force NAMES cntr_force HINTS ${cntr_force_LIBRARIES})

add_subdirectory(plugins/cntr_mux)
include_directories(${cntr_mux_INCLUDE_DIRS})
find_library(cntr_mux NAMES cntr_mux HINTS ${cntr_mux_LIBRARIES})

add_subdirectory(plugins/conv_vel2pose)
include_directories(${conv_vel2pose_INCLUDE_DIRS})
find_library(conv_vel2pose NAMES conv_vel2pose HINTS ${conv_vel2pose_LIBRARIES})

add_subdirectory(plugins/motion_error_cart)
include_directories(${motion_error_cart_INCLUDE_DIRS})
find_library(motion_error_cart NAMES motion_error_cart HINTS ${motion_error_cart_LIBRARIES})

add_subdirectory(plugins/virtual_cube)
include_directories(${virtual_cube_INCLUDE_DIRS})
find_library(virtual_cube NAMES virtual_cube HINTS ${virtual_cube_LIBRARIES})

add_subdirectory(plugins/virtual_walls_joint)
include_directories(${virtual_walls_joint_INCLUDE_DIRS})
find_library(virtual_walls_joint NAMES virtual_walls_joint HINTS ${virtual_walls_joint_LIBRARIES})

add_subdirectory(plugins/cntr_nullsp_proj)
include_directories(${cntr_nullsp_proj_INCLUDE_DIRS})
find_library(cntr_nullsp_proj NAMES cntr_nullsp_proj HINTS ${cntr_nullsp_proj_LIBRARIES})

set(SOURCES core/src/core.cpp event_publisher/src/event_publisher.cpp interface/src/interface.cpp interface/src/parameter_server.cpp knowledge_base/src/concepts.cpp knowledge_base/src/knowledge_base.cpp
    knowledge_base/src/local_memory.cpp led_pattern/src/led_pattern.cpp manipulation_primitive/src/manipulation_primitive.cpp skill/src/skill.cpp task/src/task.cpp task/src/task_handler.cpp task/src/task_list.cpp
    telemetry/src/telemetry_udp.cpp)

set(SOURCES_PRIMITIVES manipulation_primitive/src/primitives/mp_basic.cpp manipulation_primitive/src/primitives/mp_basic_joint.cpp manipulation_primitive/src/primitives/mp_telepresence.cpp
    manipulation_primitive/src/primitives/mp_external.cpp)

file(GLOB SOURCES_SKILLS "skill/src/skills/*.cpp")
file(GLOB SOURCES_TASKS "task/src/tasks/*.cpp")
file(GLOB SOURCES_PATTERN "led_pattern/src/patterns/*.cpp")

add_executable(mios main/src/mios.cpp ${SOURCES} ${SOURCES_PRIMITIVES} ${SOURCES_SKILLS} ${SOURCES_TASKS} ${SOURCES_PATTERN})
cotire(mios)

target_link_libraries(mios ${mogen_p2p} ${conv_vel2pose} ${cntr_force}
    ${cntr_aic} ${cntr_joint_var_imp} ${cntr_mux} ${virtual_cube} ${virtual_walls_joint} ${cntr_nullsp_proj} ${mogen_p2p} ${motion_error_cart} ${mogen_p2p_joint}
    msrm_cpp_utils franka mongocxx bsoncxx boost_system SDL2 SDL2_mixer ssl crypto pthread)

install(TARGETS mios DESTINATION ${CMAKE_SOURCE_DIR}/bin)

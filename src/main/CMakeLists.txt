add_executable(mios src/mios.cpp)

find_package(PythonLibsNew REQUIRED)

target_include_directories(mios
    PRIVATE
    src
    ${PYTHON_INCLUDE_DIRS}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    )

find_package(pybind11 REQUIRED)
find_package(cxxopts REQUIRED)
find_package(Boost REQUIRED)

target_link_libraries(mios
    PRIVATE
    ${PROJECT_NAME}::${PROJECT_NAME}_project_options
    ${PROJECT_NAME}::${PROJECT_NAME}_project_warnings
    ${PROJECT_NAME}::${PROJECT_NAME}_project_deps
    PUBLIC
    ${PROJECT_NAME}::core
    pybind11::pybind11
    cxxopts::cxxopts
    stdc++fs
    )

install(TARGETS mios DESTINATION ${CMAKE_INSTALL_BINDIR})

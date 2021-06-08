add_executable(mios src/mios.cpp)

target_link_libraries(mios
    PRIVATE
    ${PROJECT_NAME}::${PROJECT_NAME}_project_options
    ${PROJECT_NAME}::${PROJECT_NAME}_project_warnings
    ${PROJECT_NAME}::${PROJECT_NAME}_project_deps
    )

install(TARGETS mios DESTINATION ${CMAKE_SOURCE_DIR}/bin)

project(proj_tests)

function(create_unit_test  test_name test_location LIBS)
    add_executable(${test_name} ${test_location})
    target_compile_options(${test_name} PRIVATE ${CXX_FLAGS_REQUIRED_TESTS})
    target_link_libraries(${test_name} ${LIBS}  )
    add_test(NAME ${test_name} COMMAND ${test_name})
    set_target_properties(${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test)
endfunction(create_unit_test)




set(LIBS_TEST proj_lib catch armadillo)


# The test program
create_unit_test(testBasic src/testBasic.cpp "${LIBS_TEST}")
create_unit_test(testWeighted src/testWeighted.cpp "${LIBS_TEST}")

###BUILD TEST Examples
set(LIBS_EXAMPLES  ${LIBS_TEST})


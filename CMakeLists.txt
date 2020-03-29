project (proj_prz)

# Header only library, therefore INTERFACE
add_library(proj_prz INTERFACE)

# INTERFACE targets only have INTERFACE properties
target_include_directories(proj_prz INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)



set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_subdirectory(projection)


add_subdirectory(3rdparty/chronoP)
add_subdirectory(bench)

include(CTest)
add_subdirectory(3rdparty/catch)
add_subdirectory(test)



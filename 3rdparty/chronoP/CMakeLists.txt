project (chronoP)

# Header only library, therefore INTERFACE
add_library(chronoP INTERFACE)

# INTERFACE targets only have INTERFACE properties
target_include_directories(chronoP INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

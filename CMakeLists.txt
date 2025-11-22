cmake_minimum_required (VERSION 3.26)

project (oop1_ex02)
set (MY_AUTHORS "Tomer_Shovav-Gal_Amar")

include (cmake/CompilerSettings.cmake)

add_executable (${CMAKE_PROJECT_NAME})

# Enable AddressSanitizer in debug builds
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
if (NOT MSVC)
    target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
endif()

add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (resources)

include (cmake/Zip.cmake)

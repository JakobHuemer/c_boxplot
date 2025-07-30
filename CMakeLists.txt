
cmake_minimum_required(VERSION 3.12)
project(boxplot C)

# Set include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create static library
add_library(boxplot STATIC
    src/boxplot.c
)

# Public headers for installation
target_include_directories(boxplot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


# testing
enable_testing()

add_executable(test_boxplot test/test_boxplot.c)
target_link_libraries(test_boxplot boxplot)
target_include_directories(test_boxplot PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_test(NAME OutlierTest COMMAND test_boxplot)

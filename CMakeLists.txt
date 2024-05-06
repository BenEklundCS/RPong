cmake_minimum_required(VERSION 3.11)  # Version can be adjusted based on your needs
project(MyRaylibGame)

# Set the C standard to C99
set(CMAKE_C_STANDARD 99)

# If raylib isn't in a standard location, you might need to set this
# set(CMAKE_PREFIX_PATH "/usr/local/lib/cmake/raylib")  # Adjust the path as necessary

# Find raylib
find_package(raylib 3.0 QUIET) # If you have a specific version requirement, adjust it here

if (NOT raylib_FOUND)
    # If not found, fetch from GitHub
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/3.7.0.tar.gz # Adjust version as needed
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

# Define your executable
add_executable(MyRaylibGame main.c)

# Link against raylib
target_link_libraries(MyRaylibGame raylib)

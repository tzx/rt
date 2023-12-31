cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
       -Wall -Werror -Wno-error=maybe-uninitialized
       $<$<CONFIG:RELEASE>:-Ofast>
       $<$<CONFIG:DEBUG>:-O0>
       $<$<CONFIG:DEBUG>:-ggdb3>
)

project(Rt)

# This is bad, but I don't care right now
file(GLOB_RECURSE SRCFILES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE TESTFILES CONFIGURE_DEPENDS "tests/*.cpp")


message(${SRCFILES})
list(REMOVE_ITEM SRCFILES ${CMAKE_SOURCE_DIR}/src/rt.cpp)

add_executable(${PROJECT_NAME} ${SRCFILES} "src/rt.cpp")
add_executable(tester ${SRCFILES} ${TESTFILES})

find_package(Catch2 REQUIRED)
target_link_libraries(tester Catch2::Catch2)

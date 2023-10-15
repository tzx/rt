cmake_minimum_required(VERSION 3.26)

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

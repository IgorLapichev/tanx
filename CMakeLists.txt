message (STATUS "Started...")
cmake_minimum_required(VERSION 2.8)

set (APP_NAME "tanx")

set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/../../boost_1_67_0)
set(BOOST_INCLUDEDIR ${BOOST_ROOT})
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib64-msvc-14.1)

find_package(Boost REQUIRED)

include_directories(
	${CMAKE_SOURCE_DIR}/../Json
	${BOOST_INCLUDEDIR}
   )

link_directories(${BOOST_LIBRARYDIR})

add_subdirectory(${CMAKE_SOURCE_DIR}/src)
get_property(SRC GLOBAL PROPERTY SRC_LIST)

add_executable(${APP_NAME} ${SRC})

message(STATUS "Finished...")


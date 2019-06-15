cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(concertistamidi)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(Freetype REQUIRED)

find_library(ICUUC_LIBRARY icuuc)


include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${FREETYPE_INCLUDE_DIRS})
include_directories(${ICUUC_INCLUDE_DIR})

add_subdirectory(codigo)

set(todo
		${codigo}
)
add_executable(${PROJECT_NAME} ${todo})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${FREETYPE_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${ICUUC_LIBRARY})

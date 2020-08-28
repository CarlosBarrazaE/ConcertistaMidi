cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(concertistamidi)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
#find_package(SDL2 REQUIRED)
find_package(Freetype REQUIRED)

find_library(ICUUC_LIBRARY icuuc)
find_library(SQLITE3_LIBRERIA NAMES sqlite3)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(ALSA REQUIRED alsa)

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${FREETYPE_INCLUDE_DIRS})
include_directories(${ICUUC_INCLUDE_DIR})
include_directories(${ALSA_INCLUDE_DIRS})

add_subdirectory(codigo)

set(todo
		${codigo}
)
#-Wsign-compare=
set(advertencias "-Wdelete-non-virtual-dtor -Wdeprecated-copy -Wswitch-default -Wshadow -Wsign-promo -Wreorder -Wparentheses -Wmaybe-uninitialized -Wtype-limits -Wcatch-value")
#-Wall -Wextra -Wctor-dtor-privacy -Wdisabled-optimization -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wstrict-null-sentinel -Wswitch-default -Wundef -Wformat=2
#-Werror
set(depuracion "-g3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -march=native -std=c++17 -lstdc++fs ${advertencias} ${depuracion}")
add_executable(${PROJECT_NAME} ${todo})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${SDL2_CFLAGS_OTHER})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${FREETYPE_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${ICUUC_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${ALSA_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SQLITE3_LIBRERIA})

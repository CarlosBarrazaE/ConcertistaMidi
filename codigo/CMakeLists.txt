add_subdirectory(archivos)
add_subdirectory(recursos)

set(codigo
	${archivos}
	${recursos}
	${CMAKE_CURRENT_SOURCE_DIR}/principal.c++
	${CMAKE_CURRENT_SOURCE_DIR}/controlador_juego.c++
	${CMAKE_CURRENT_SOURCE_DIR}/raton.c++
	${CMAKE_CURRENT_SOURCE_DIR}/fps.c++
	${CMAKE_CURRENT_SOURCE_DIR}/registro.c++
	PARENT_SCOPE
)

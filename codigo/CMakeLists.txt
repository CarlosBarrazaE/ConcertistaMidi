add_subdirectory(archivos)
add_subdirectory(control)
add_subdirectory(dispositivos)
add_subdirectory(elementos_graficos)
add_subdirectory(libmidi)
add_subdirectory(recursos)
add_subdirectory(util)
add_subdirectory(ventanas)

set(codigo
	${archivos}
	${control}
	${dispositivos}
	${elementos_graficos}
	${libmidi}
	${recursos}
	${util}
	${ventanas}
	${CMAKE_CURRENT_SOURCE_DIR}/principal.c++
	${CMAKE_CURRENT_SOURCE_DIR}/controlador_juego.c++
	${CMAKE_CURRENT_SOURCE_DIR}/fps.c++
	${CMAKE_CURRENT_SOURCE_DIR}/registro.c++
	PARENT_SCOPE
)

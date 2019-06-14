#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "recursos/administrador_recursos.h++"
#include "controlador_juego.h++"

#include "registro.h++"

#define ANCHO 800
#define ALTO 600

Administrador_Recursos *recursos;
Controlador_Juego *controlador;

void configurar_gl();
void ajustar_ventana(GLFWwindow *ventana, int ancho_nuevo, int alto_nuevo);
void eventos_raton_botones(GLFWwindow *ventana, int boton, int accion, int modo);
void eventos_raton_posicion(GLFWwindow *ventana, double x, double y);
void evento_raton_rueda(GLFWwindow *ventana, double desplazamiento_x, double desplazamiento_y);
void eventos_taclado(GLFWwindow *ventana, int tecla, int codigo, int accion, int modo);

int main (int n, char **argumentos)
{
	Registro::nota("Iniciando GLFW " + std::string(glfwGetVersionString()));
	glfwSetErrorCallback(Registro::error_glfw);

	if(!glfwInit())
	{
		Registro::error("Error al inicial GLFW");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	//GLFWmonitor *pantalla = glfwGetPrimaryMonitor();
	//const GLFWvidmode *modo = glfwGetVideoMode(pantalla);
	//GLFWwindow *ventana = glfwCreateWindow(modo->width, modo->height, "Prueba OpenGl", pantalla, NULL);
	GLFWwindow *ventana = glfwCreateWindow(ANCHO, ALTO, "Conceritsta MIDI", NULL, NULL);
	if(!ventana)
	{
		Registro::error("Error al inicial la ventana");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(ventana);
	glewExperimental = GL_TRUE;
	glewInit();

	Registro::mostrar_detalles();

	configurar_gl();
	recursos = new Administrador_Recursos();
	controlador = new Controlador_Juego(recursos);

	glfwSetWindowSizeCallback(ventana, ajustar_ventana);
	glfwSetKeyCallback(ventana, eventos_taclado);
	glfwSetMouseButtonCallback(ventana, eventos_raton_botones);
	glfwSetCursorPosCallback(ventana, eventos_raton_posicion);
	glfwSetScrollCallback(ventana, evento_raton_rueda);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Modo estructura alambre
	while (!glfwWindowShouldClose(ventana))
	{
		if(controlador->terminar())
			glfwSetWindowShouldClose(ventana, GLFW_TRUE);

		glClear(GL_COLOR_BUFFER_BIT);

		controlador->actualizar();

		glfwSwapBuffers(ventana);
		glfwPollEvents();
	}

	delete controlador;
	delete recursos;
	glfwDestroyWindow(ventana);
	glfwTerminate();
	return 0;
}

void configurar_gl()
{
	glfwSwapInterval(1);//60 FPS sincronizacion vertical
	glEnable (GL_CULL_FACE);
	glClearColor(0.725, 1.0, 0.892, 1.0);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ajustar_ventana(GLFWwindow *ventana, int ancho_nuevo, int alto_nuevo)
{
	if(recursos != NULL)
	{
		glViewport(0, 0, ancho_nuevo, alto_nuevo);
		recursos->actualizar_pantalla(ancho_nuevo, alto_nuevo);
	}
}

void eventos_raton_botones(GLFWwindow *ventana, int boton, int accion, int modo)
{
	if(controlador != NULL)
	{
		Raton *raton = controlador->eventos_raton();

		bool estado = false;
		if(accion == GLFW_PRESS)
			estado = true;
		else if(accion == GLFW_RELEASE)
			estado = false;

		if(boton == GLFW_MOUSE_BUTTON_LEFT)
			raton->actualizar_boton(BotonIzquierdo, estado);
		else if(boton == GLFW_MOUSE_BUTTON_MIDDLE)
			raton->actualizar_boton(BotonCentral, estado);
		else if(boton == GLFW_MOUSE_BUTTON_RIGHT)
			raton->actualizar_boton(BotonDerecho, estado);
	}
}
void eventos_raton_posicion(GLFWwindow *ventana, double x, double y)
{
	if(controlador != NULL)
	{
		Raton *raton = controlador->eventos_raton();
		raton->actualizar_posicion(x, y);
	}
}

void evento_raton_rueda(GLFWwindow *ventana, double desplazamiento_x, double desplazamiento_y)
{
	if(controlador != NULL)
	{
		Raton *raton = controlador->eventos_raton();
		raton->actualizar_desplazamiento(desplazamiento_y);
	}
}

void eventos_taclado(GLFWwindow *ventana, int tecla, int codigo, int accion, int modo)
{
	if(controlador != NULL && accion != GLFW_REPEAT)
	{
		bool estado = false;
		if(accion == GLFW_PRESS)
			estado = true;
		else if(accion == GLFW_RELEASE)
			estado = false;

		switch(tecla)
		{
			case GLFW_KEY_0: controlador->eventos_teclado(TECLA_0, estado); break;
			case GLFW_KEY_1: controlador->eventos_teclado(TECLA_1, estado); break;
			case GLFW_KEY_2: controlador->eventos_teclado(TECLA_2, estado); break;
			case GLFW_KEY_3: controlador->eventos_teclado(TECLA_3, estado); break;
			case GLFW_KEY_4: controlador->eventos_teclado(TECLA_4, estado); break;
			case GLFW_KEY_5: controlador->eventos_teclado(TECLA_5, estado); break;
			case GLFW_KEY_6: controlador->eventos_teclado(TECLA_6, estado); break;
			case GLFW_KEY_7: controlador->eventos_teclado(TECLA_7, estado); break;
			case GLFW_KEY_8: controlador->eventos_teclado(TECLA_8, estado); break;
			case GLFW_KEY_9: controlador->eventos_teclado(TECLA_9, estado); break;
			case GLFW_KEY_A: controlador->eventos_teclado(TECLA_A, estado); break;
			case GLFW_KEY_B: controlador->eventos_teclado(TECLA_B, estado); break;
			case GLFW_KEY_C: controlador->eventos_teclado(TECLA_C, estado); break;
			case GLFW_KEY_D: controlador->eventos_teclado(TECLA_D, estado); break;
			case GLFW_KEY_E: controlador->eventos_teclado(TECLA_E, estado); break;
			case GLFW_KEY_F: controlador->eventos_teclado(TECLA_F, estado); break;
			case GLFW_KEY_G: controlador->eventos_teclado(TECLA_G, estado); break;
			case GLFW_KEY_H: controlador->eventos_teclado(TECLA_H, estado); break;
			case GLFW_KEY_I: controlador->eventos_teclado(TECLA_I, estado); break;
			case GLFW_KEY_J: controlador->eventos_teclado(TECLA_J, estado); break;
			case GLFW_KEY_K: controlador->eventos_teclado(TECLA_K, estado); break;
			case GLFW_KEY_L: controlador->eventos_teclado(TECLA_L, estado); break;
			case GLFW_KEY_M: controlador->eventos_teclado(TECLA_M, estado); break;
			case GLFW_KEY_N: controlador->eventos_teclado(TECLA_N, estado); break;
			case GLFW_KEY_SEMICOLON: controlador->eventos_teclado(TECLA_NN, estado); break;
			case GLFW_KEY_O: controlador->eventos_teclado(TECLA_O, estado); break;
			case GLFW_KEY_P: controlador->eventos_teclado(TECLA_P, estado); break;
			case GLFW_KEY_Q: controlador->eventos_teclado(TECLA_Q, estado); break;
			case GLFW_KEY_R: controlador->eventos_teclado(TECLA_R, estado); break;
			case GLFW_KEY_S: controlador->eventos_teclado(TECLA_S, estado); break;
			case GLFW_KEY_T: controlador->eventos_teclado(TECLA_T, estado); break;
			case GLFW_KEY_U: controlador->eventos_teclado(TECLA_U, estado); break;
			case GLFW_KEY_V: controlador->eventos_teclado(TECLA_V, estado); break;
			case GLFW_KEY_W: controlador->eventos_teclado(TECLA_W, estado); break;
			case GLFW_KEY_X: controlador->eventos_teclado(TECLA_X, estado); break;
			case GLFW_KEY_Y: controlador->eventos_teclado(TECLA_Y, estado); break;
			case GLFW_KEY_Z: controlador->eventos_teclado(TECLA_Z, estado); break;
			case GLFW_KEY_LEFT: controlador->eventos_teclado(TECLA_FLECHA_IZQUIERDA, estado); break;
			case GLFW_KEY_RIGHT: controlador->eventos_teclado(TECLA_FLECHA_DERECHA, estado); break;
			case GLFW_KEY_UP: controlador->eventos_teclado(TECLA_FLECHA_ARRIBA, estado); break;
			case GLFW_KEY_DOWN: controlador->eventos_teclado(TECLA_FLECHA_ABAJO, estado); break;
			case GLFW_KEY_SPACE: controlador->eventos_teclado(TECLA_ESPACIO, estado); break;
			case GLFW_KEY_BACKSPACE: controlador->eventos_teclado(TECLA_BORRAR, estado); break;
			case GLFW_KEY_PAUSE: controlador->eventos_teclado(TECLA_PAUSA, estado); break;
			case GLFW_KEY_ESCAPE: controlador->eventos_teclado(TECLA_ESCAPE, estado); break;
			case GLFW_KEY_F10: controlador->eventos_teclado(TECLA_F10, estado); break;
			case GLFW_KEY_F11: controlador->eventos_teclado(TECLA_F11, estado); break;
		}
	}
	Registro::nota("Tecla: " + std::to_string(tecla) + " Codigo: " + std::to_string(codigo) + " Accion: " + std::to_string(accion) + " Modo: " + std::to_string(modo));
}

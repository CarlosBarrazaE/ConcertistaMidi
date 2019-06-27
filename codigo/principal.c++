#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "recursos/administrador_recursos.h++"
#include "controlador_juego.h++"
#include "pantalla.h++"

#include "registro.h++"

#define ANCHO 800
#define ALTO 600

void configurar_gl();
void ajustar_ventana(Controlador_Juego *controlador, int ancho_nuevo, int alto_nuevo);
void evento_raton_rueda(Controlador_Juego *controlador, int desplazamiento_x, int desplazamiento_y);
void eventos_raton_botones(Controlador_Juego *controlador, int boton, int accion);
void eventos_raton_posicion(Controlador_Juego *controlador, int x, int y);
void eventos_taclado(SDL_Window *ventana, Controlador_Juego *controlador, int tecla, bool estado);
void controlar_eventos(SDL_Window *ventana, Controlador_Juego *controlador, SDL_Event *evento);

int main (int n, char **argumentos)
{
	Pantalla::ancho = ANCHO;
	Pantalla::alto = ALTO;

	SDL_Window *ventana = SDL_CreateWindow("Concertista Midi", 0, 0, ANCHO, ALTO, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_GLContext contexto = SDL_GL_CreateContext(ventana);
	SDL_GL_SetSwapInterval(1);//Limita a 60 fps

	glewExperimental = GL_TRUE;
	glewInit();

	Registro::mostrar_detalles();

	configurar_gl();
	Administrador_Recursos recursos;
	Controlador_Juego controlador(&recursos);

	while (!controlador.terminar())
	{
		SDL_Event evento;
		while (SDL_PollEvent(&evento))
			controlar_eventos(ventana, &controlador, &evento);

		glClear(GL_COLOR_BUFFER_BIT);

		controlador.actualizar();

		SDL_GL_SwapWindow(ventana);
	}

	return 0;
}

void configurar_gl()
{
	glEnable (GL_CULL_FACE);
	glClearColor(0.95, 0.95, 0.95, 1.0);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void controlar_eventos(SDL_Window *ventana, Controlador_Juego *controlador, SDL_Event *evento)
{
	if (evento->type == SDL_KEYDOWN)
		eventos_taclado(ventana, controlador, evento->key.keysym.sym, true);
	else if (evento->type == SDL_KEYUP)
		eventos_taclado(ventana, controlador, evento->key.keysym.sym, false);
	else if(evento->type == SDL_MOUSEBUTTONDOWN)
		eventos_raton_botones(controlador, evento->button.button, evento->button.state);
	else if(evento->type == SDL_MOUSEBUTTONUP)
		eventos_raton_botones(controlador, evento->button.button, evento->button.state);
	else if(evento->type == SDL_MOUSEMOTION)
		eventos_raton_posicion(controlador, evento->button.x, evento->button.y);
	else if(evento->type == SDL_MOUSEWHEEL)
		evento_raton_rueda(controlador, evento->wheel.x, evento->wheel.y);
	else if (evento->type == SDL_WINDOWEVENT)
	{
		if(evento->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			ajustar_ventana(controlador, evento->window.data1, evento->window.data2);
		else if (evento->window.event == SDL_WINDOWEVENT_CLOSE)
			controlador->evento_salir();
	}
}

void ajustar_ventana(Controlador_Juego *controlador, int ancho_nuevo, int alto_nuevo)
{
	glViewport(0, 0, ancho_nuevo, alto_nuevo);
	controlador->evento_ventana(ancho_nuevo, alto_nuevo);
}

void eventos_raton_botones(Controlador_Juego *controlador, int boton, int accion)
{
	Raton *raton = controlador->eventos_raton();

	bool estado = false;
	if(accion == SDL_PRESSED)
		estado = true;
	else if(accion == SDL_RELEASED)
		estado = false;

	if(boton == SDL_BUTTON_LEFT)
		raton->actualizar_boton(BotonIzquierdo, estado);
	else if(boton == SDL_BUTTON_MIDDLE)
		raton->actualizar_boton(BotonCentral, estado);
	else if(boton == SDL_BUTTON_RIGHT)
		raton->actualizar_boton(BotonDerecho, estado);
}
void eventos_raton_posicion(Controlador_Juego *controlador, int x, int y)
{
	Raton *raton = controlador->eventos_raton();
	raton->actualizar_posicion(x, y);
}

void evento_raton_rueda(Controlador_Juego *controlador, int desplazamiento_x, int desplazamiento_y)
{
	Raton *raton = controlador->eventos_raton();
	raton->actualizar_desplazamiento(desplazamiento_x, desplazamiento_y);
}

void eventos_taclado(SDL_Window *ventana, Controlador_Juego *controlador, int tecla, bool estado)
{
	switch(tecla)
	{
		case SDLK_0: controlador->eventos_teclado(TECLA_0, estado); break;
		case SDLK_1: controlador->eventos_teclado(TECLA_1, estado); break;
		case SDLK_2: controlador->eventos_teclado(TECLA_2, estado); break;
		case SDLK_3: controlador->eventos_teclado(TECLA_3, estado); break;
		case SDLK_4: controlador->eventos_teclado(TECLA_4, estado); break;
		case SDLK_5: controlador->eventos_teclado(TECLA_5, estado); break;
		case SDLK_6: controlador->eventos_teclado(TECLA_6, estado); break;
		case SDLK_7: controlador->eventos_teclado(TECLA_7, estado); break;
		case SDLK_8: controlador->eventos_teclado(TECLA_8, estado); break;
		case SDLK_9: controlador->eventos_teclado(TECLA_9, estado); break;
		case SDLK_a: controlador->eventos_teclado(TECLA_A, estado); break;
		case SDLK_b: controlador->eventos_teclado(TECLA_B, estado); break;
		case SDLK_c: controlador->eventos_teclado(TECLA_C, estado); break;
		case SDLK_d: controlador->eventos_teclado(TECLA_D, estado); break;
		case SDLK_e: controlador->eventos_teclado(TECLA_E, estado); break;
		case SDLK_f: controlador->eventos_teclado(TECLA_F, estado); break;
		case SDLK_g: controlador->eventos_teclado(TECLA_G, estado); break;
		case SDLK_h: controlador->eventos_teclado(TECLA_H, estado); break;
		case SDLK_i: controlador->eventos_teclado(TECLA_I, estado); break;
		case SDLK_j: controlador->eventos_teclado(TECLA_J, estado); break;
		case SDLK_k: controlador->eventos_teclado(TECLA_K, estado); break;
		case SDLK_l: controlador->eventos_teclado(TECLA_L, estado); break;
		case SDLK_m: controlador->eventos_teclado(TECLA_M, estado); break;
		case SDLK_n: controlador->eventos_teclado(TECLA_N, estado); break;
		case 241: controlador->eventos_teclado(TECLA_NN, estado); break;
		case SDLK_o: controlador->eventos_teclado(TECLA_O, estado); break;
		case SDLK_p: controlador->eventos_teclado(TECLA_P, estado); break;
		case SDLK_q: controlador->eventos_teclado(TECLA_Q, estado); break;
		case SDLK_r: controlador->eventos_teclado(TECLA_R, estado); break;
		case SDLK_s: controlador->eventos_teclado(TECLA_S, estado); break;
		case SDLK_t: controlador->eventos_teclado(TECLA_T, estado); break;
		case SDLK_u: controlador->eventos_teclado(TECLA_U, estado); break;
		case SDLK_v: controlador->eventos_teclado(TECLA_V, estado); break;
		case SDLK_w: controlador->eventos_teclado(TECLA_W, estado); break;
		case SDLK_x: controlador->eventos_teclado(TECLA_X, estado); break;
		case SDLK_y: controlador->eventos_teclado(TECLA_Y, estado); break;
		case SDLK_z: controlador->eventos_teclado(TECLA_Z, estado); break;
		case SDLK_LEFT: controlador->eventos_teclado(TECLA_FLECHA_IZQUIERDA, estado); break;
		case SDLK_RIGHT: controlador->eventos_teclado(TECLA_FLECHA_DERECHA, estado); break;
		case SDLK_UP: controlador->eventos_teclado(TECLA_FLECHA_ARRIBA, estado); break;
		case SDLK_DOWN: controlador->eventos_teclado(TECLA_FLECHA_ABAJO, estado); break;
		case SDLK_SPACE: controlador->eventos_teclado(TECLA_ESPACIO, estado); break;
		case SDLK_BACKSPACE: controlador->eventos_teclado(TECLA_BORRAR, estado); break;
		case SDLK_PAUSE: controlador->eventos_teclado(TECLA_PAUSA, estado); break;
		case SDLK_ESCAPE: controlador->eventos_teclado(TECLA_ESCAPE, estado); break;
		case SDLK_F10: controlador->eventos_teclado(TECLA_F10, estado); break;
		case SDLK_F11:
			controlador->eventos_teclado(TECLA_F11, estado);
			if(controlador->es_pantalla_completa())
				SDL_SetWindowFullscreen(ventana, SDL_WINDOW_FULLSCREEN_DESKTOP);
			else
				SDL_SetWindowFullscreen(ventana, 0);
			break;
		case SDLK_F12:
			controlador->eventos_teclado(TECLA_F12, estado);
			if(controlador->modo_alambre_activado())
				glPolygonMode(GL_FRONT, GL_LINE);
			else
				glPolygonMode(GL_FRONT, GL_FILL);
			break;
	}
}

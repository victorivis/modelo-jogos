#include "input.h"

void Input::receberInput(SDL_Event& evento){
    if(evento.type == SDL_KEYDOWN){
		teclaPressionada = evento.key.keysym.scancode;
        teclasSeguradas[teclaPressionada] = true;
	}
    else if(evento.type == SDL_KEYUP){
        teclaLiberada = evento.key.keysym.scancode;
        teclasSeguradas[teclaLiberada] = false;
    }
}

bool Input::foiPressionada(Uint8 tecla){
    return teclaPressionada == tecla;
}

bool Input::foiLiberada(Uint8 tecla){
    return teclaLiberada == tecla;
}

bool Input::estaPressionada(Uint8 tecla){
    return teclasSeguradas[tecla];
}

void Input::resetar(){
    teclaPressionada = 0;
    teclaLiberada = 0;
}
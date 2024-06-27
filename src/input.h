#pragma once
#include <SDL2/SDL.h>
#include <map>

class Input{
    public:
        void receberInput(SDL_Event& evento);
        bool foiPressionada(Uint8 tecla);
        bool foiLiberada(Uint8 tecla);
        bool estaPressionada(Uint8 tecla);        
        void resetar();

    private:
        Uint8 teclaPressionada;
        Uint8 teclaLiberada;
        std::map<Uint8, bool> teclasSeguradas;
};
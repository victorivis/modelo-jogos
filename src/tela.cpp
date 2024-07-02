#include "tela.h"
#include "global.h"
#include <iostream>

namespace definicoesJanela{
    const int comprimento= 1080;
    const int altura = 720;
    const int posX = SDL_WINDOWPOS_CENTERED;
    const int posY = SDL_WINDOWPOS_CENTERED;
    const Uint32 flags = SDL_WINDOW_RESIZABLE;
};

namespace definicoesRenderer{
    const Uint32 flags = SDL_RENDERER_ACCELERATED;
};

Vector2 tamanhoCamera(definicoesJanela::comprimento * 2, definicoesJanela::altura * 2);

Tela::Tela(){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG || IMG_INIT_JPG);
    _janela = SDL_CreateWindow("Uma game engine simples", definicoesJanela::posX, definicoesJanela::posY, 
        definicoesJanela::comprimento, definicoesJanela::altura, definicoesJanela::flags);
    _render = SDL_CreateRenderer(_janela, -1, definicoesRenderer::flags);

    SDL_SetRenderDrawColor(getRenderer(), 150, 150, 150, 255);

    _cursor = SDL_CreateColorCursor(carregarSuperficie("assets/sprites/cursor.png"), 0, 0);
    SDL_SetCursor(_cursor);

    origem = {0, 0, definicoesJanela::comprimento, definicoesJanela::altura};
    destino = {0, 0, definicoesJanela::comprimento, definicoesJanela::altura};

    SDL_SetRenderTarget(getRenderer(), criarTextura());
}

Tela::~Tela(){
    int numSur=0, numTex=0;
    for(auto textura: _todasAsTexturas){
        numTex++;
        SDL_DestroyTexture(textura.second);
    }
    for(auto superficie: _todasAsSuperficies){
        numSur++;
        SDL_FreeSurface(superficie.second);
    }

    SDL_DestroyWindow(_janela);
    SDL_DestroyRenderer(_render);
    SDL_FreeCursor(_cursor);

    IMG_Quit();
    SDL_Quit();

    if(mostrarDebug){
        std::cout << numSur << " superficies liberadas com sucesso!\n";
        std::cout << numTex << " texturas liberadas com sucesso!\n";
        std::cout << "Adeus vazamentos de memoria\n";
    }
}

SDL_Surface* Tela::carregarSuperficie(std::string caminhoParaImagem){
    if(_todasAsSuperficies.count(caminhoParaImagem) == 0){
        _todasAsSuperficies[caminhoParaImagem] = IMG_Load(caminhoParaImagem.c_str());
    }
    return _todasAsSuperficies[caminhoParaImagem];
}

SDL_Texture* Tela::carregarTextura(std::string caminhoParaImagem){
    if(_todasAsTexturas.count(caminhoParaImagem) == 0){
        _todasAsTexturas[caminhoParaImagem] = SDL_CreateTextureFromSurface(getRenderer(), carregarSuperficie(caminhoParaImagem));
    }
    return _todasAsTexturas[caminhoParaImagem];
}

SDL_Texture* Tela::criarTextura(){
    if(_todasAsTexturas.count("criada") == 0){
        _todasAsTexturas["criada"] = SDL_CreateTexture(getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, tamanhoCamera.x, tamanhoCamera.y);
    }
    return _todasAsTexturas["criada"];
}

void Tela::apresentar(){
    SDL_SetRenderDrawColor(getRenderer(), 150, 150, 150, 255);

    SDL_SetRenderTarget(getRenderer(), NULL);
    SDL_RenderCopy(getRenderer(), criarTextura(), &origem, &destino);

    SDL_RenderPresent(getRenderer());
    SDL_SetRenderTarget(getRenderer(), criarTextura());
    SDL_RenderClear(_render);
}

SDL_Renderer* Tela::getRenderer(){
    return _render;
}

SDL_Window* Tela::getWindow(){
    return _janela;
}

void Tela::moverCameraX(int X){
    if(X < 0 && origem.x+X >= 0){
        origem.x += X;
    }
    else if(origem.x+X < tamanhoCamera.x){
        origem.x += X;
    }
}
void Tela::moverCameraY(int Y){
    if(Y < 0 && origem.y+Y >= 0){
        origem.y += Y;
    }
    else if(origem.y+Y < tamanhoCamera.y){
        origem.y += Y;
    }
}
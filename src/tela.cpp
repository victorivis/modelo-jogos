#include "tela.h"
#include "global.h"
#include <iostream>

//Para que carregarTexturas seja acessivel globalmente
SDL_Renderer* rendererGlobal=nullptr;
std::map<std::string, SDL_Surface*> Tela::_todasAsSuperficies;
std::map<std::string, SDL_Texture*> Tela::_todasAsTexturas;

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

Vector2 tamanhoCenario(definicoesJanela::comprimento * 2, definicoesJanela::altura * 2);

void mostrarDrivers(){
    int numDrivers = SDL_GetNumRenderDrivers();
    for (int i = 0; i < numDrivers; i++) {
        SDL_RendererInfo info;
        if (SDL_GetRenderDriverInfo(i, &info) == 0) {
            printf("Driver %d: %s\n", i, info.name);
        } else {
            printf("Erro ao obter informações do driver %d\n", i);
        }
    }
}

Tela::Tela(): _seguirX(nullptr), _seguirY(nullptr), _cameraX(200), _cameraY(0){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG || IMG_INIT_JPG);
    _janela = SDL_CreateWindow("Uma game engine simples", definicoesJanela::posX, definicoesJanela::posY, 
        definicoesJanela::comprimento, definicoesJanela::altura, definicoesJanela::flags);
    _render = SDL_CreateRenderer(_janela, -1, definicoesRenderer::flags);

    rendererGlobal = _render;

    SDL_SetRenderDrawColor(getRenderer(), 150, 150, 150, 255);

    SDL_Surface* imagemMouse = carregarSuperficie("assets/sprites/cursor.png");
    _cursor = SDL_CreateColorCursor(imagemMouse, imagemMouse->w/2, imagemMouse->h/2);

    SDL_SetCursor(_cursor);

    origem = {0, 0, definicoesJanela::comprimento, definicoesJanela::altura};
    destino = {0, 0, definicoesJanela::comprimento, definicoesJanela::altura};

    //SDL_SetRenderTarget(getRenderer(), criarTextura());
    mostrarDrivers();
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
    if(rendererGlobal == nullptr){
        std::cout << "Impossivel carregar textura. Tela nao foi criada ainda.\n";
        return nullptr;
    }

    if(_todasAsTexturas.count(caminhoParaImagem) == 0){
        _todasAsTexturas[caminhoParaImagem] = SDL_CreateTextureFromSurface(rendererGlobal, carregarSuperficie(caminhoParaImagem));
    }
    return _todasAsTexturas[caminhoParaImagem];
}

SDL_Texture* Tela::criarTextura(){
    if(_todasAsTexturas.count("criada") == 0){
        _todasAsTexturas["criada"] = SDL_CreateTexture(getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, tamanhoCenario.x, tamanhoCenario.y);
    }
    return _todasAsTexturas["criada"];
}

void Tela::apresentar(){
    SDL_SetRenderDrawColor(getRenderer(), 150, 150, 150, 255);

    //SDL_SetRenderTarget(getRenderer(), NULL);

    seguirCamera();
    //SDL_RenderCopy(getRenderer(), criarTextura(), &origem, &destino);

    SDL_RenderPresent(getRenderer());
    //SDL_SetRenderTarget(getRenderer(), criarTextura());
    SDL_RenderClear(_render);
}

SDL_Renderer* Tela::getRenderer(){
    return _render;
}

SDL_Window* Tela::getWindow(){
    return _janela;
}

void Tela::selecionarSeguirCamera(float* seguirX, float* seguirY){
    if(seguirX != nullptr && seguirY != nullptr){
        _seguirX = seguirX;
        _seguirY = seguirY;
    }
}

void Tela::seguirCamera(){
    if(_seguirX != nullptr){
        int velocidade = 3;

        int novoX = (*_seguirX - origem.w/2) * -1;
        int novoY = (*_seguirY - origem.h/2) * -1;

        /*
        if(novoX < 0){
            novoX = 0;
        }
        else if(novoX > tamanhoCenario.x - origem.w){
            novoX = tamanhoCenario.x - origem.w;
        }

        if(novoY < 0){
            novoY = 0;
        }
        else if(novoY > tamanhoCenario.y - origem.h){
            novoY = tamanhoCenario.y - origem.h;
        }
        */

        origem.x = novoX;
        origem.y = novoY;

        _cameraX = novoX;
        _cameraY = novoY;
    }
}

void Tela::moverCameraX(int X){
    if(X < 0 && origem.x+X >= 0){
        origem.x += X;
    }
    else if(origem.x+X < tamanhoCenario.x){
        origem.x += X;
    }
}
void Tela::moverCameraY(int Y){
    if(Y < 0 && origem.y+Y >= 0){
        origem.y += Y;
    }
    else if(origem.y+Y < tamanhoCenario.y){
        origem.y += Y;
    }
}

int Tela::getCameraX(){
    return _cameraX;
}
int Tela::getCameraY(){
    return _cameraY;
}
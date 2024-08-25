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

Tela::Tela(): _seguirX(nullptr), _seguirY(nullptr){
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

    _camera = {0, 0, definicoesJanela::comprimento, definicoesJanela::altura};
    
    if(mostrarDebug){
        mostrarDrivers();
    }
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
    seguirCamera();
    SDL_RenderPresent(getRenderer());
    SDL_RenderClear(_render);
}

SDL_Renderer* Tela::getRenderer(){
    return _render;
}

SDL_Window* Tela::getWindow(){
    return _janela;
}

void Tela::atualizarTamanhoCamera(){
    SDL_GetWindowSize(getWindow(), &_camera.w, &_camera.h);
}

void Tela::selecionarSeguirCamera(float* seguirX, float* seguirY){
    _seguirX = seguirX;
    _seguirY = seguirY;
}

bool Tela::seguirCamera(){
    if(_seguirX != nullptr && _seguirY != nullptr){
        _camera.x = _camera.w / (2.0 * aumentarSprite) - (*_seguirX);
        _camera.y = _camera.h / (2.0 * aumentarSprite) - (*_seguirY);

        return true;
    }
    return false;
}

void Tela::moverCameraX(int X){
    _camera.x += X;
}
void Tela::moverCameraY(int Y){
    _camera.y += Y;
}

int Tela::getCameraX(){
    return _camera.x;
}
int Tela::getCameraY(){
    return _camera.y;
}
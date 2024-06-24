#include <SDL2/SDL.h>

#include "imagem.h"

Imagem::Imagem(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem):
    _tex(tex),
    _tamanho(tamanho),
    _x(posTela.x),
    _y(posTela.y),
    _posImagem(posImagem)
    {}


void Imagem::mostrar(Tela &tela){
    SDL_Rect origem = {_posImagem.x, _posImagem.y, _tamanho.x, _tamanho.y};
    SDL_Rect destino = {_x, _y, _tamanho.x * aumentarSprite, _tamanho.y * aumentarSprite};
    SDL_RenderCopy(tela.getRenderer(), _tex, &origem, &destino);
}
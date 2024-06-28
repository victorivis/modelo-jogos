#include "animacao.h"
#include <iostream>

Animacao::Animacao(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem, int numeroFrames, int duracao):
    Imagem(tex, tamanho, posTela, posImagem),
    _indice(0),
    _duracao(duracao),
    _totalTempo(0){
        for(int i=0; i<numeroFrames; i++){
            _frames.push_back(Vector2(posImagem.x + tamanho.x * i, posImagem.y));
        }
    }

Animacao::Animacao(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem, std::vector<Vector2>& frames, int duracao):
    Imagem(tex, tamanho, posTela, posImagem),
    _indice(0),
    _duracao(duracao),
    _totalTempo(0),
    _frames(frames){}

void Animacao::atualizar(int tempo){
    _totalTempo += tempo;
    
    if(_totalTempo / _duracao > 0){
        _indice = (_indice+1)% _frames.size();
        _totalTempo -= _duracao;
    }
}

void Animacao::mostrar(Tela& tela){
    _posImagem.x = _frames[_indice].x;
    _posImagem.y = _frames[_indice].y;
    Imagem::mostrar(tela);
}
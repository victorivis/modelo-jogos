#include "animacao.h"
#include <iostream>

Animacao::Animacao(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem, int numeroFrames, int duracao):
    Imagem(tex, tamanho, posTela, posImagem),
    _numeroFrames(numeroFrames),
    _indice(0),
    _frameInicial(posImagem),
    _duracao(duracao),
    _totalTempo(0){}

void Animacao::atualizar(int tempo){
    _totalTempo += tempo;
    
    if(_totalTempo / _duracao > 0){
        _indice = (_indice+1)%_numeroFrames;
        _totalTempo -= _duracao;
    }
}

void Animacao::mostrar(Tela& tela){
    _posImagem.x = _indice * _tamanho.x + _frameInicial.x;
    Imagem::mostrar(tela);
}
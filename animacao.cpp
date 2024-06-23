#include "animacao.h"
#include <iostream>

Animacao::Animacao(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem, int numeroFrames, int duracao):
    Imagem(tex, tamanho, posTela, posImagem),
    _numeroFrames(numeroFrames),
    _duracao(numeroFrames),
    _indice(0),
    _tempoDecorrido(duracao),
    _frameInicial(posImagem){}

void Animacao::atualizar(int tempoDecorrido){
    _tempoDecorrido -= tempoDecorrido;
    if(_tempoDecorrido <= 0){
        _indice = (_indice+1)%_numeroFrames;

        _tempoDecorrido = _tempoDecorrido + _duracao;
        //std::cout<< "tempoDecorrido no sprite: " << _tempoDecorrido << "\n";
    }
}

void Animacao::mostrar(Tela& tela){
    _posImagem.x = _indice * _tamanho.x + _frameInicial.x;
    Imagem::mostrar(tela);
}
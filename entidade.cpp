#include "entidade.h"
#include <iostream>

Entidade::Entidade(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem):
    Imagem(tex, tamanho, posTela, posImagem),
    _indice(-1){}

void Entidade::atualizar(int tempoDecorrido){
    static int tempo = 0;

    tempo -= tempoDecorrido;
    if(tempo <= 0){
        tempo += _animacaoAtual->_duracao;

        _indice = (_indice+1)%_animacaoAtual->_numeroFrames;
        _posImagem.x = _tamanho.x * _indice + _animacaoAtual->_frameInicial.x;

        if(mostrarDebug){
            printf("x:%d y:%d posImagem.x: %d posImagem.y: %d\n", _x, _y, _posImagem.x, _posImagem.y);
            printf("numero de frames %d", _animacaoAtual->_numeroFrames);
            printf(" indice: %d \n", _indice);
            printf("\n");
        }
    }
}

void Entidade::adicionarAnimacao(std::string nome, infoAnimacao info){
    _animacoes[nome] = info;
}

void Entidade::selecionarAnimacao(std::string nome){
    if(_animacoes.count(nome) != 0){
        _indice = 0;
        _animacaoAtual = &_animacoes[nome];

        _posImagem.y = _animacaoAtual->_frameInicial.y;
    }
}
#include "entidade.h"
#include <iostream>

Entidade::Entidade(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem)
    : Imagem(tex, tamanho, posTela, posImagem), _indice(-1), _animacaoAtual(nullptr) {}

void Entidade::atualizar(int tempoDecorrido){
    static int tempo = 0;

    if(_animacaoAtual!=nullptr && _animacaoAtual->_numeroFrames > 1){
        tempo -= tempoDecorrido;
    }
    
    if(tempo <= 0){
        int temp = _animacaoAtual->_duracao;
        tempo += temp;

        _indice = (_indice+1)%_animacaoAtual->_numeroFrames;
        _posImagem.x = _tamanho.x * _indice + _animacaoAtual->_frameInicial.x;

        if(mostrarDebug){
            printf("x:%d y:%d posImagem.x: %d posImagem.y: %d\n", _x, _y, _posImagem.x, _posImagem.y);
            printf("numero de frames %d", _animacaoAtual->_numeroFrames);
            printf(" indice: %d tempo: %d duracaoAnimacao %d\n", _indice, tempo, _animacaoAtual->_duracao);
            printf("\n");
        }
    }
}

void Entidade::adicionarAnimacao(std::string nome, infoAnimacao info){
    _animacoes[nome] = info;

    if(mostrarDebug){
        std::cout<< "Duracoes: " << info._duracao << " " << _animacoes[nome]._duracao << "\n";
    }
}

void Entidade::selecionarAnimacao(std::string nome){
    if(_animacoes.count(nome) != 0){
        _indice = 0;
        _animacaoAtual = &_animacoes[nome];

        _posImagem.y = _animacaoAtual->_frameInicial.y;
        _posImagem.x = _animacaoAtual->_frameInicial.x;

        if(mostrarDebug){
            std::cout << "Duracao no ponteiro: " << _animacaoAtual->_duracao << "\n";
        }        
    }
}

infoAnimacao* Entidade::getAnimacao(std::string nome){
    return &_animacoes[nome];
}

infoAnimacao* Entidade::getPrimeiraAnimacao(){
    if(_animacoes.begin()++ != _animacoes.end()){
        return &(_animacoes.begin()++)->second;
    }
    else{
        return nullptr;
    }
}
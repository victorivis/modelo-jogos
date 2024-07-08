#include "entidade.h"
#include <iostream>

Entidade::Entidade(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem)
    : Imagem(tex, tamanho, posTela, posImagem), _indice(-1), _animacaoAtual(nullptr), _tempoDecorridoFrame(0){}

bool Entidade::atualizar(int tempoDecorrido){
    bool foiAtualizado=false;

    if(_animacaoAtual!=nullptr && _animacaoAtual->_numeroFrames > 1){
        _tempoDecorridoFrame -= tempoDecorrido;
    }
    
    if(_tempoDecorridoFrame <= 0){
        foiAtualizado = true;
        _tempoDecorridoFrame += _animacaoAtual->_duracao;

        _indice = (_indice+1) % (_animacaoAtual->_numeroFrames);
        _posImagem.x = _tamanho.x * _indice + _animacaoAtual->_frameInicial.x;

        if(mostrarDebug){
            printf("x:%d y:%d posImagem.x: %d posImagem.y: %d\n", _x, _y, _posImagem.x, _posImagem.y);
            printf("numero de frames %d", _animacaoAtual->_numeroFrames);
            printf(" indice: %d tempo: %d duracaoAnimacao %d\n", _indice, _tempoDecorridoFrame, _animacaoAtual->_duracao);
            printf("\n");
        }
    }

    _caixaColisao = Retangulo(_x, _y, _tamanho.x * aumentarSprite, _tamanho.y * aumentarSprite);

    return foiAtualizado;
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

void Entidade::empurrarX(float X){
    _x += X;
}
void Entidade::empurrarY(float Y){
    _y += Y;
}

Retangulo Entidade::getCaixaColisao(){
    return _caixaColisao;
}
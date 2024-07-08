#include "ataque.h"

Ataque::Ataque(): _ativo(false){}
Ataque::~Ataque(){}

Ataque::Ataque(Retangulo hitbox, int duracao): _hitbox(hitbox), _duracao(duracao), _backupDuracao(duracao), _ativo(true), _ladoColisao(NENHUMA){}

void Ataque::invocarAtaque(Entidade& entidade, Direcao lado){
    Retangulo hitBoxEntidade = entidade.getCaixaColisao();
    if(lado == DIREITA){
        _hitbox.setX(hitBoxEntidade.getDireita()+1);
    }
    else{
        _hitbox.setX(hitBoxEntidade.getEsquerda()-1-_hitbox.getLargura());
    }
    _hitbox.setY(hitBoxEntidade.getCentroY() - _hitbox.getAltura()/2);
    _duracao = _backupDuracao;
    _ativo = true;
    _ladoColisao = lado;
}

bool Ataque::estaColidindo(Retangulo& outro){
    if(_ativo){
        return _hitbox.colisaoAABB(outro);
    }
    return false;
}

void Ataque::atualizar(int tempoDecorrido){
    if(_ativo){
        _duracao -= tempoDecorrido;
        if(_duracao <= 0 ){
            _ativo = false;
        }
    }
}

void Ataque::mostrar(Tela& tela){
    if(_ativo){
        _hitbox.exibirRetangulo(tela);
    }
}

void Ataque::lidarColisao(Entidade& entidade){
    if(entidade.estaAtivo()){
        Retangulo hitboxEntidade = entidade.getCaixaColisao();

        int fatorEmpurro = 10;

        if(estaColidindo(hitboxEntidade)){
            if(_ladoColisao == DIREITA){
                entidade.empurrarX(fatorEmpurro);
            }
            else if(_ladoColisao == ESQUERDA){
                entidade.empurrarX(-fatorEmpurro);
            }

            entidade.morrer();
        }
    }
}

void Ataque::lidarColisao(std::vector<Morcego>& entidades){
    for(int i=0; i<entidades.size(); i++){
        lidarColisao(entidades[i]);
    }
}

bool Ataque::estaRodando(){
    return _ativo;
}
#include "entidade.h"
#include "inimigos.h"
#include <vector>

class Ataque{
    public:
        Ataque();
        Ataque(Retangulo hitbox, int duracao);
        ~Ataque();

        bool estaColidindo(Retangulo& outro);
        void atualizar(int tempoDecorrido);
        void mostrar(Tela& tela);

        void lidarColisao(Entidade& entidade);
        void lidarColisao(std::vector<Morcego>& entidades);
        void invocarAtaque(Entidade& entidade, Direcao lado);
        
        bool estaRodando();

    private:
        Retangulo _hitbox;
        Direcao _ladoColisao;
        int _duracao;
        int _backupDuracao;
        bool _ativo;

};
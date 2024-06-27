#include "entidade.h"

class Projetil : public Entidade{
    public:
        Projetil();
        ~Projetil();
        Projetil(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem, float angulo, int velocidade);
        void atualizar(int tempoDecorrido);
        void mostrar(Tela& tela);
        void lidarColisao(Retangulo& colidido);
        void desativarProjetil();
        bool estaAtivo();
    private:
        int _tempo;
        int _velocidade;
        float _angulo;
        bool _inativo;
};
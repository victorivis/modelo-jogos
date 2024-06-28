#include "entidade.h"

class Projetil : public Entidade{
    public:
        Projetil();
        ~Projetil();
        Projetil(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem, float seno, float cosseno, int velocidade);
        void atualizar(int tempoDecorrido);
        void mostrar(Tela& tela);
        void lidarColisao(Retangulo& colidido);
        void desativarProjetil();
        bool estaAtivo();
    private:
        
        int _tempo;
        Uint8 _velocidade;
        float _seno;
        float _cosseno;
        float _angulo;
        bool _inativo;
};
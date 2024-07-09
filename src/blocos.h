#include "imagem.h"
#include "retangulo.h"

class BlocoMovel : public Imagem{
    public:
        BlocoMovel();
        ~BlocoMovel();
        BlocoMovel(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem, Vector2 pontoFinal, int velocidade);
        void atualizar();
        Retangulo getHitBox();
        double getDeslocamentoX();
        double getDeslocamentoY();

    private:
        Vector2 _pontoInicio;
        Vector2 _pontoFinal;
        float _seno;
        float _cosseno;
        int _velocidade;
        bool _sentido;
};
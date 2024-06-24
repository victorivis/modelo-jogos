#include "imagem.h"
#include <map>
#include <vector>


class Animacao : public Imagem{
    public:
        Animacao(){}
        Animacao(SDL_Texture* tex, Vector2 tamanho, Vector2 posTela, Vector2 posImagem, int numeroFrames, int duracao);
        ~Animacao(){}

        void atualizar(int tempo);
        void mostrar(Tela& tela);
        void adicionarAnimacao();

    protected:
        Vector2 _frameInicial;
        int _duracao;
        int _numeroFrames;
        int _indice;
};
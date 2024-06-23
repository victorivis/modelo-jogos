#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>

//Uma classe que cuida de toda a abstracao de carregar imagens na tela
//faz com que uma mesma imagem nao seja carregada duas vezes, criar janelas e liberar as texturas ao final
class Imagens{
    public:
        Imagens();
        ~Imagens();
        SDL_Surface* carregarSuperficie(std::string caminhoParaImagem);
        SDL_Texture* carregarTextura(std::string caminhoParaImagem);
        void apresentarTela();

        SDL_Renderer* getRenderer();

    private:
        std::map<std::string, SDL_Surface*> _todasAsSuperficies;
        std::map<std::string, SDL_Texture*> _todasAsTexturas;

        SDL_Window* _janela;
        SDL_Renderer* _render;
};
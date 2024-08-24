#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>

//Uma classe que cuida de toda a abstracao de carregar imagens na tela
//faz com que uma mesma imagem nao seja carregada duas vezes, criar janelas e liberar as texturas ao final
class Tela{
    public:
        Tela();
        ~Tela();
        static SDL_Surface* carregarSuperficie(std::string caminhoParaImagem);
        static SDL_Texture* carregarTextura(std::string caminhoParaImagem);
        SDL_Texture* criarTextura();
        
        void apresentar();

        SDL_Renderer* getRenderer();
        SDL_Window* getWindow();
        void atualizarTamanhoCamera();
        void selecionarSeguirCamera(float* seguirX, float* seguirY);
        void seguirCamera();
        void moverCameraX(int X);
        void moverCameraY(int Y);
        int getCameraX();
        int getCameraY();
        

    private:
        static std::map<std::string, SDL_Surface*> _todasAsSuperficies;
        static std::map<std::string, SDL_Texture*> _todasAsTexturas;

        SDL_Rect _camera;
        SDL_Rect destino;

        SDL_Window* _janela;
        SDL_Renderer* _render;
        SDL_Cursor* _cursor;

        float* _seguirX;
        float* _seguirY;
};
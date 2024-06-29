#include "global.h"
#include "player.h"

class Inclinacao{
    public:
        Inclinacao();
        ~Inclinacao();
        Inclinacao(Vector2 p1, Vector2 p2);
        bool estaColidindo(Player& player);
        void lidarColisao(Player& player);
        void mostrar(Tela& tela);
    private:
        float _seno;
        Vector2 _p1;
        Vector2 _p2;
};
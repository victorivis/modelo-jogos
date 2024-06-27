#include <iostream>
#include <cstring>
#include <tinyxml2.h>
#include <cmath>

#include "mapa.h"

char caminhoBase[] = "assets/mapas/";

void Mapa::carregarMapa(Tela& tela, std::string caminhoParaMapa){
    std::string nomeArquivo = (caminhoBase + caminhoParaMapa + ".tmx");

    tinyxml2::XMLDocument DocumentoMapa;
    DocumentoMapa.LoadFile(nomeArquivo.c_str());
    std::cout << nomeArquivo << "\n";

    tinyxml2::XMLElement* pMapa = DocumentoMapa.FirstChildElement("map");
    int larguraBloco = pMapa->IntAttribute("tilewidth");
    int alturaBloco = pMapa->IntAttribute("tileheight");

    //recebendo blocos de colisao
    tinyxml2::XMLElement* pOjectGroup = pMapa->FirstChildElement("objectgroup");
    while(pOjectGroup){
        if(pOjectGroup->Attribute("name") == std::string("colisoes")){
            tinyxml2::XMLElement* pBlocoColisao = pOjectGroup->FirstChildElement("object");
            while(pBlocoColisao){
                int x = std::round(pBlocoColisao->FloatAttribute("x"));
                int y = std::round(pBlocoColisao->FloatAttribute("y"));
                int largura = std::round(pBlocoColisao->FloatAttribute("width"));
                int altura = std::round(pBlocoColisao->FloatAttribute("height"));
                _colisoes.push_back(Retangulo(x * aumentarSprite, y * aumentarSprite, largura * aumentarSprite, altura * aumentarSprite));

                pBlocoColisao = pBlocoColisao->NextSiblingElement("object");
            }
        }
        

        pOjectGroup = pOjectGroup->NextSiblingElement("objectgroup");
    }


    std::vector<infoBlocoAnimado> tilesAnimados;
    //recebendo informacoes do mapa
    tinyxml2::XMLElement* pTileset = pMapa->FirstChildElement("tileset");
    while(pTileset){
        int gidAtual = pTileset->IntAttribute("firstgid");

        tinyxml2::XMLElement* pImage = pTileset->FirstChildElement("image");
        const char* caminhoMapa = pImage->Attribute("source");

        std::string imagemMapa = "assets/mapas/" + std::string(caminhoMapa);
        SDL_Texture* tex = tela.carregarTextura(imagemMapa);

        //int larguraTextura = pImage->IntAttribute("width")  / larguraBloco;
        //int alturaTextura =  pImage->IntAttribute("height") / alturaBloco;

        _infoBlocos.push_back(infoBloco(tex, gidAtual));

        //Salvando animacoes
        tinyxml2::XMLElement* pTile = pTileset->FirstChildElement("tile");
        while(pTile){
            int primeiroFrame = pTile->IntAttribute("id");
            tinyxml2::XMLElement* pAnimacao = pTile->FirstChildElement("animation");
            while(pAnimacao){
                tinyxml2::XMLElement* pFrame = pAnimacao->FirstChildElement("frame");
                int duracao;
                std::vector<int> frames;
                while (pFrame){
                    frames.push_back(pFrame->IntAttribute("tileid"));
                    duracao = pFrame->IntAttribute("duration");

                    pFrame = pFrame->NextSiblingElement("frame");
                }
                tilesAnimados.push_back(infoBlocoAnimado(duracao, gidAtual, primeiroFrame, frames));

                pAnimacao = pAnimacao->NextSiblingElement("animation");
            }

            pTile = pTile->NextSiblingElement("tile");
        }

        pTileset = pTileset->NextSiblingElement("tileset");
    }
    
    tinyxml2::XMLElement* pLayer = pMapa->FirstChildElement("layer");
    int larguraMapa = pLayer->IntAttribute("width");
    int alturaMapa = pLayer->IntAttribute("height");

    //printf("%d %d %d %d\n%d %d %d %d\n", larguraMapa, alturaMapa, tilewidth, tileheight, texturaBlocoWidth, texturaBlocoHeight, larguraTextura, alturaTextura);

    std::vector<Vector2> GidPosicao;

    //Renderizando mapa
    while(pLayer){
        std::cout << "existe Layer\n";
        tinyxml2::XMLElement* pData = pLayer->FirstChildElement("data");
        while(pData){
            const char* stringMapa = pData->GetText();

            //Insere o tipo e a posicao do bloco em _GidPosicao
            lerCSV(stringMapa, ',', GidPosicao);

            pData = pData->NextSiblingElement("data");
        }

        pLayer = pLayer->NextSiblingElement("layer");
    }


    //Faz a conversao os numeros contados de um ate o final do mapa para as coordenadas x e y
    for(int i=0; i<GidPosicao.size(); i++){
        int gidAtual = GidPosicao[i].x;
        int posicaoComprimida = GidPosicao[i].y;
        infoBloco blocoAtual;

        bool temAnimacao=false;
        int posAnimacao;

        for(int i=0; i<tilesAnimados.size(); i++){
            if(tilesAnimados[i].gidAbsoluto() == gidAtual){
                printf("He he he, existe animacao %d\n", gidAtual);
                temAnimacao = true;
                posAnimacao = i;
                break;
            }
        }

        for(int i=0; i<_infoBlocos.size(); i++){
            if(gidAtual >= _infoBlocos[i].gid){
                blocoAtual = _infoBlocos[i];
            }
        }

        int larguraTextura;
        SDL_QueryTexture(blocoAtual.tex, NULL, NULL, &larguraTextura, NULL);
        larguraTextura /= larguraBloco;

        
        int posTelaX = (posicaoComprimida % larguraMapa) * larguraBloco * aumentarSprite;
        int posTelaY = (posicaoComprimida / larguraMapa) * alturaBloco  * aumentarSprite;
        Vector2 posImagem = calcularGidRelativo(gidAtual, blocoAtual.gid, larguraTextura, larguraBloco, alturaBloco);

        if(temAnimacao){
            infoBlocoAnimado infoAnimacaoAtual = tilesAnimados[posAnimacao];
            Animacao animacaoAtual(blocoAtual.tex, Vector2(larguraBloco, alturaBloco), Vector2(posTelaX, posTelaY), posImagem, infoAnimacaoAtual.framesAnimacao.size(), infoAnimacaoAtual.duracao);
            _blocosAnimados.push_back(animacaoAtual);
        }
        else{
            _blocos.push_back( Imagem(blocoAtual.tex, Vector2(larguraBloco, alturaBloco), Vector2(posTelaX, posTelaY), posImagem) );
        }
    }

   //std::cout << imagemMapa << "\n";
   //SDL_RenderCopy(tela.getRenderer(), tex, NULL, NULL);
   //tela.apresentar();
   //SDL_Delay(1000);
}

void Mapa::atualizar(int tempoDecorrido){
    for(int i=0; i<_blocosAnimados.size(); i++){
        _blocosAnimados[i].atualizar(tempoDecorrido);
    }
}

void Mapa::mostrar(Tela& tela){
    for(int i=0; i<_blocos.size(); i++){
        _blocos[i].mostrar(tela);    
    }

    if(exibirColisoes){
        for(int i=0; i<_colisoes.size(); i++){
            _colisoes[i].exibirRetangulo(tela);    
        }
    }

    for(int i=0; i<_blocosAnimados.size(); i++){
        _blocosAnimados[i].mostrar(tela);
    }
}

void Mapa::lidarColisao(Player& player){
    for(int i=0; i<_colisoes.size(); i++){
        Retangulo caixaPlayer = player.getCaixaColisao();
        //caixaPlyer.debugRetangulo();
        Direcao daColisao = _colisoes[i].ladoColisao(caixaPlayer);

        if(daColisao != NENHUMA){
            if(daColisao == DIREITA){
                player.setX(_colisoes[i].getDireita()+1);
                //std::cout << "Direita\n";
            }
            else if(daColisao == ESQUERDA){
                player.setX(_colisoes[i].getEsquerda()-caixaPlayer.getLargura()-1);
                //std::cout << "Esquerda\n";
            }
            else if(daColisao == CIMA){
                player.setY(_colisoes[i].getCima()-caixaPlayer.getAltura()-1);
                //std::cout << "Cima\n";
            }
            else if(daColisao == BAIXO){
                player.setY(_colisoes[i].getBaixo()+1);
                //std::cout << "Baixo\n";
            }
        } 
    }
}

//Recebe o valor do gid e a posicao dele no array
void lerCSV(const char* minhaString, char charDividir, std::vector<Vector2>& GidPosicao){    
    int i=0;
    int inicio=0;

    int posicao=0;
    do{
        if((minhaString[i] == charDividir || minhaString[i] == '\0') && inicio!=i){
            int atual = i;
            char subString[atual - inicio + 1];
            strncpy(subString, &minhaString[inicio], atual-inicio);
            subString[atual-inicio] = '\0';
            int subStringComoInteiro = atoi(subString);

            if(subStringComoInteiro > 0){
                GidPosicao.push_back(Vector2(subStringComoInteiro, posicao));
            }            

            posicao++;
            inicio = atual+1;
        }
        //i++;
    }while(minhaString[i++]!='\0');

    // printf("split rodou\n");
    // for(int i=0; i<GidPosicao.size(); i++){
    //     std::cout << GidPosicao[i].x << " " << GidPosicao[i].y << "\n";
    // }
}

Vector2 calcularGidRelativo(int gidAtual, int firstgid, int larguraTextura, int larguraBloco, int alturaBloco){
    int posImagemX = (gidAtual - firstgid) % larguraTextura * larguraBloco;
    int posImagemY = (gidAtual - firstgid) / larguraTextura * alturaBloco;

    return Vector2(posImagemX, posImagemY);
}
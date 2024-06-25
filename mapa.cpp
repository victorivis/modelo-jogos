#include <iostream>
#include <cstring>
#include <tinyxml2.h>

#include "mapa.h"

char caminhoBase[] = "assets/mapas/";

void Mapa::carregarMapa(Tela& tela, std::string caminhoParaMapa){
    std::string nomeArquivo = (caminhoBase + caminhoParaMapa + ".tmx");

    tinyxml2::XMLDocument DocumentoMapa;
    DocumentoMapa.LoadFile(nomeArquivo.c_str());
    std::cout << nomeArquivo << "\n";

    tinyxml2::XMLElement* pMapa = DocumentoMapa.FirstChildElement("map");

    //recebendo informacoes do mapa
    tinyxml2::XMLElement* pTileset = pMapa->FirstChildElement("tileset");
    int larguraBloco = pTileset->IntAttribute("tilewidth");
    int alturaBloco = pTileset->IntAttribute("tileheight");

    tinyxml2::XMLElement* pImage = pTileset->FirstChildElement("image");
    const char* caminhoMapa = pImage->Attribute("source");

    std::string imagemMapa = "assets/mapas/" + std::string(caminhoMapa);
    SDL_Texture* tex = tela.carregarTextura(imagemMapa);

    int larguraTextura = pImage->IntAttribute("width")  / larguraBloco;
    int alturaTextura =  pImage->IntAttribute("height") / alturaBloco;
    
    tinyxml2::XMLElement* pLayer = pMapa->FirstChildElement("layer");
    int larguraMapa = pLayer->IntAttribute("width");
    int alturaMapa = pLayer->IntAttribute("height");
    int primeiroGid = pLayer->IntAttribute("gid");

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
    

    for(int i=0; i<GidPosicao.size(); i++){
        int posTelaX = (GidPosicao[i].y % larguraMapa) * larguraBloco;
        int posTelaY = (GidPosicao[i].y / larguraMapa) * alturaBloco;

        int posImagemX = (GidPosicao[i].x-1) % larguraTextura * larguraBloco;
        int posImagemY = (GidPosicao[i].x-1) / larguraTextura * alturaBloco;

        _blocos.push_back( Imagem(tex, Vector2(larguraBloco, alturaBloco), Vector2(posTelaX, posTelaY), Vector2(posImagemX, posImagemY)) );
    }

   std::cout << imagemMapa << "\n";
   SDL_RenderCopy(tela.getRenderer(), tex, NULL, NULL);
   tela.apresentar();
   SDL_Delay(1000);
}

void Mapa::mostrar(Tela& tela){
    for(int i=0; i<_blocos.size(); i++){
        _blocos[i].mostrar(tela);
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

    printf("split rodou\n");
    for(int i=0; i<GidPosicao.size(); i++){
        std::cout << GidPosicao[i].x << " " << GidPosicao[i].y << "\n";
    }
}
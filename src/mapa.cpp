#include <iostream>
#include <cstring>
#include <tinyxml2.h>
#include <cmath>
#include <string>

#include "mapa.h"

char caminhoBase[] = "assets/mapas/";

void Mapa::carregarMapa(std::string caminhoParaMapa){
    //Destroi o mapa anterior, se existir
    _colisoes.clear();
    _blocosMoveis.clear();
    _ladeiras.clear();
    _blocos.clear();
    _blocosAnimados.clear();
    _caminhoMorcegos.clear();
    _portas.clear();

    std::cout << _ladeiras.size() << "\n";

    //Carrega o novo mapa
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
        else if(pOjectGroup->Attribute("name") == std::string("ladeiras")){
            tinyxml2::XMLElement* pLadeira = pOjectGroup->FirstChildElement("object");
            while(pLadeira){
                int x = pLadeira->IntAttribute("x");
                int y = pLadeira->IntAttribute("y");
                //std:: cout << "x: " << x << " y: " << y << "\n";

                tinyxml2::XMLElement* pPolyline = pLadeira->FirstChildElement("polyline");

                const char* texto = pPolyline->Attribute("points");
                //std::cout << "texto: " << texto << "\n";
                std::vector<std::string> pontos = split(texto, ' ');
                //printf("pontos: %s %s\n", pontos[0].c_str(), pontos[1].c_str());

                std::vector<std::string> ponto2 = split(pontos[1].c_str(), ',');

                Vector2 p1 = Vector2(x * aumentarSprite, y * aumentarSprite);
                Vector2 p2 = Vector2( (stoi(ponto2[0]) + x) * aumentarSprite, (stoi(ponto2[1]) + y) * aumentarSprite);
                
                printf("p1(%d, %d), p2(%d, %d)\n", p1.x, p1.y, p2.x, p2.y);

                _ladeiras.push_back(Inclinacao(p1, p2));

                pLadeira = pLadeira->NextSiblingElement("object");
            }
        }
        else if(pOjectGroup->Attribute("name") == std::string("spawnpoint")){
            tinyxml2::XMLElement* pObjeto = pOjectGroup->FirstChildElement("object");
            if(pObjeto){
                _spawnpoint.x = aumentarSprite * std::round(pObjeto->FloatAttribute("x"));
                _spawnpoint.y = aumentarSprite * std::round(pObjeto->FloatAttribute("y"));
            }
        }
        else if(pOjectGroup->Attribute("name") == std::string("morcegos")){
            tinyxml2::XMLElement* pMorcego = pOjectGroup->FirstChildElement("object");
            while(pMorcego){
                int x = pMorcego->IntAttribute("x");
                int y = pMorcego->IntAttribute("y");

                tinyxml2::XMLElement* pPolyline = pMorcego->FirstChildElement("polyline");

                const char* texto = pPolyline->Attribute("points");
                std::vector<std::string> pontos = split(texto, ' ');

                std::vector<std::string> ponto2 = split(pontos[1].c_str(), ',');

                Vector2 p1 = Vector2(x * aumentarSprite, y * aumentarSprite);
                Vector2 p2 = Vector2( (stoi(ponto2[0]) + x) * aumentarSprite, (stoi(ponto2[1]) + y) * aumentarSprite);

                _caminhoMorcegos.push_back(Linha(p1, p2));

                pMorcego = pMorcego->NextSiblingElement("object");
            }
        }
        else if(pOjectGroup->Attribute("name") == std::string("blocosMoveis")){
            SDL_Texture* texturaPlataforma = Tela::carregarTextura("assets/tileset/plataforma.png");
            Vector2 tamanhoPlataforma(48, 16);
            //SDL_Texture* texturaPlataforma = Tela::carregarTextura("assets/tileset/world_tileset.png");
            //Vector2 tamanhoPlataforma(16, 16);

            tinyxml2::XMLElement* pBlocosMoveis = pOjectGroup->FirstChildElement("object");
            while(pBlocosMoveis){
                int x = pBlocosMoveis->IntAttribute("x");
                int y = pBlocosMoveis->IntAttribute("y");

                tinyxml2::XMLElement* pPolyline = pBlocosMoveis->FirstChildElement("polyline");

                const char* texto = pPolyline->Attribute("points");
                std::vector<std::string> pontos = split(texto, ' ');

                std::vector<std::string> ponto2 = split(pontos[1].c_str(), ',');

                Vector2 p1 = Vector2(x * aumentarSprite, y * aumentarSprite);
                Vector2 p2 = Vector2( (stoi(ponto2[0]) + x) * aumentarSprite, (stoi(ponto2[1]) + y) * aumentarSprite);

                _blocosMoveis.push_back(BlocoMovel(texturaPlataforma, tamanhoPlataforma, p1, Vector2(0, 0), p2, 4));

                pBlocosMoveis = pBlocosMoveis->NextSiblingElement("object");
            }
        }
        else if(pOjectGroup->Attribute("name") == std::string("portas")){
            tinyxml2::XMLElement* pPorta = pOjectGroup->FirstChildElement("object");
            while(pPorta){
                int x = std::round(pPorta->FloatAttribute("x"));
                int y = std::round(pPorta->FloatAttribute("y"));
                int largura = std::round(pPorta->FloatAttribute("width"));
                int altura = std::round(pPorta->FloatAttribute("height"));
                Retangulo areaColisao = Retangulo(x, y, largura, altura);

                std::string destino = "";

                tinyxml2::XMLElement* pPropriedades = pPorta->FirstChildElement("properties");
                tinyxml2::XMLElement* pPropriedadePersonalizada = pPropriedades->FirstChildElement("property");
                while (pPropriedadePersonalizada){
                    if(std::string(pPropriedadePersonalizada->Attribute("name")) == std::string("destino")){
                        destino = std::string(pPropriedadePersonalizada->Attribute("value"));
                    }

                    pPropriedadePersonalizada = pPropriedadePersonalizada->NextSiblingElement("property");
                }

                if(destino != ""){
                    _portas.push_back(Porta(areaColisao, destino));
                }

                pPorta = pPorta->NextSiblingElement("object");
            }
            
        }

        pOjectGroup = pOjectGroup->NextSiblingElement("objectgroup");
    }


    std::vector<infoBlocoAnimado> tilesAnimados;
    std::vector<infoBloco> infoBlocos;

    //recebendo informacoes do mapa
    tinyxml2::XMLElement* pTileset = pMapa->FirstChildElement("tileset");
    while(pTileset){
        int gidAtual = pTileset->IntAttribute("firstgid");

        tinyxml2::XMLElement* pImage = pTileset->FirstChildElement("image");
        const char* caminhoMapa = pImage->Attribute("source");

        std::string imagemMapa = "assets/mapas/" + std::string(caminhoMapa);
        SDL_Texture* tex = Tela::carregarTextura(imagemMapa);

        infoBlocos.push_back(infoBloco(tex, gidAtual));

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
                temAnimacao = true;
                posAnimacao = i;
                break;
            }
        }

        for(int i=0; i<infoBlocos.size(); i++){
            if(gidAtual >= infoBlocos[i].gid){
                blocoAtual = infoBlocos[i];
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
            std::vector<Vector2> frames;
            for(int i=0; i<infoAnimacaoAtual.framesAnimacao.size(); i++){
                frames.push_back(calcularGidRelativo(infoAnimacaoAtual.framesAnimacao[i]+blocoAtual.gid, blocoAtual.gid, larguraTextura, larguraBloco, alturaBloco));
            }

            Animacao animacaoAtual(blocoAtual.tex, Vector2(larguraBloco, alturaBloco), Vector2(posTelaX, posTelaY), posImagem, frames, infoAnimacaoAtual.duracao);
            _blocosAnimados.push_back(animacaoAtual);
        }
        else{
            _blocos.push_back( Imagem(blocoAtual.tex, Vector2(larguraBloco, alturaBloco), Vector2(posTelaX, posTelaY), posImagem) );
        }
    }

    std::cout << "Numero de portas: " << _portas.size() << "\n";
}

void Mapa::atualizar(int tempoDecorrido){
    for(int i=0; i<_blocosAnimados.size(); i++){
        _blocosAnimados[i].atualizar(tempoDecorrido);
    }

    for(int i=0; i<_blocosMoveis.size(); i++){
        _blocosMoveis[i].atualizar();
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
    for(int i=0; i<_ladeiras.size(); i++){
        _ladeiras[i].mostrar(tela);
    }

    for(int i=0; i<_blocosAnimados.size(); i++){
        _blocosAnimados[i].mostrar(tela);
    }

    for(int i=0; i<_blocosMoveis.size(); i++){
        _blocosMoveis[i].mostrar(tela);
    }

    for(int i=0; i<_portas.size(); i++){
        //Retangulo teste = _portas[i].getRetangulo();
        _portas[i].getRetangulo().exibirRetangulo(tela);
    }
}

void Mapa::lidarColisao(Player& player){
    bool houveColisao(false);

    //Blocos solidos
    for(int i=0; i<_colisoes.size(); i++){
        Retangulo caixaPlayer = player.getCaixaColisao();
        caixaPlayer.setY(caixaPlayer.getCima()+1);

        Direcao daColisao = _colisoes[i].ladoColisao(caixaPlayer);

        caixaPlayer.setY(caixaPlayer.getCima()-1);

        if(daColisao != NENHUMA){
            if(daColisao == DIREITA){
                player.setX(_colisoes[i].getDireita()+1);
            }
            else if(daColisao == ESQUERDA){
                player.setX(_colisoes[i].getEsquerda()-caixaPlayer.getLargura()-1);
            }
            else if(daColisao == CIMA){
                if(player.estaCaindo()){
                    player.setY(_colisoes[i].getCima()-caixaPlayer.getAltura());
                    player.tocouChao();
                }
            }
            else if(daColisao == BAIXO){
                player.setY(_colisoes[i].getBaixo()+1);
            }
            
            houveColisao = true;
        }
    }

    //Ladeiras
    for(int i=0; i<_ladeiras.size(); i++){
        _ladeiras[i].lidarColisao(player);
    }

    //Plataformas voadoras
    for(int i=0; i<_blocosMoveis.size(); i++){
        Retangulo caixaPlayer = player.getCaixaColisao();
        Retangulo caixaBloco = _blocosMoveis[i].getHitBox();

        caixaPlayer.setY(caixaPlayer.getCima()+1);

        Direcao daColisao = caixaBloco.ladoColisao(caixaPlayer);

        caixaPlayer.setY(caixaPlayer.getCima()-1);

        if(daColisao != NENHUMA){
            if(daColisao == DIREITA){
                player.setX(caixaBloco.getDireita()+1);
            }
            else if(daColisao == ESQUERDA){
                player.setX(caixaBloco.getEsquerda()-caixaPlayer.getLargura()-1);
            }
            else if(daColisao == CIMA){
                if(player.estaCaindo()){
                    player.setY(caixaBloco.getCima()-caixaPlayer.getAltura()+1);
                    player.tocouChao();
                }
            }
            else if(daColisao == BAIXO){
                player.setY(caixaBloco.getBaixo()+1);
            }

            player.empurrarX(_blocosMoveis[i].getDeslocamentoX());
            player.empurrarY(_blocosMoveis[i].getDeslocamentoY());

            houveColisao = true;
        }
    }

    if(houveColisao == false){
        if(player.estaCaindo() == false){
            player.caiu();
        }
    }

    //Portas
    Retangulo caixaPlayer = player.getCaixaColisao();
    for(int i=0; i<_portas.size(); i++){
        if(_portas[i].getRetangulo().colisaoAABB(caixaPlayer)){
            carregarMapa(_portas[i].getDestino());
            player.setSpawnPoint(getSpawnpoint());
            player.voltarParaSpawn();
            break;
        }
    }
}

std::vector<Retangulo> Mapa::getColisoes(){
    return _colisoes;
}

std::vector<Linha> Mapa::getMorcegos(){
    return _caminhoMorcegos;
}

Vector2 Mapa::getSpawnpoint(){
    return _spawnpoint;
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

std::vector<std::string> split(const char* minhaString, char charDividir){
    std::vector<std::string> saida;
    int i=0;
    int inicio=0;

    if(minhaString[0] == '\0'){
        printf("String vazia enviada para split\n");
        return saida;
    }

    do{
        if((minhaString[i] == charDividir || minhaString[i] == '\0') && inicio!=i){
            int atual = i;
            char subString[atual - inicio + 1];
            strncpy(subString, &minhaString[inicio], atual-inicio);
            subString[atual-inicio] = '\0';
            saida.push_back(std::string(subString));
            inicio = atual+1;
        }
    }while(minhaString[i++]!='\0');
    return saida;
}

Vector2 calcularGidRelativo(int gidAtual, int firstgid, int larguraTextura, int larguraBloco, int alturaBloco){
    int posImagemX = (gidAtual - firstgid) % larguraTextura * larguraBloco;
    int posImagemY = (gidAtual - firstgid) / larguraTextura * alturaBloco;

    return Vector2(posImagemX, posImagemY);
}
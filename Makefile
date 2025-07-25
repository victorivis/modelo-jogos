# Diretório onde estão os arquivos fonte
SRC_DIR = src

# Diretório onde serão gerados os arquivos objeto
OBJ_DIR = obj

# Libs
LIBS = -I ..\SDL2\x86_64-w64-mingw32\include\ -L ..\SDL2\x86_64-w64-mingw32\lib\ -I ..\tinyxml2\ -L ..\tinyxml2 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -ltinyxml2
LIBS_LINUX = -Wall $(shell pkg-config --cflags --libs sdl2) -lSDL2_image -ltinyxml2
WEBLIBS = -s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 --preload-file assets -s INITIAL_MEMORY=52428800 -s EXIT_RUNTIME=1

web:
	WEBLIBS = -s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 --preload-file assets -s INITIAL_MEMORY=52428800 -s EXIT_RUNTIME=1
linux:
	g++ $(wildcard src/*.cpp) $(LIBS_LINUX) -o saida.out
run: linux
	./saida.out

# Arquivos objeto
obj_files = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp))

# Regra para criar o diretório OBJ_DIR se não existir
$(OBJ_DIR):
	if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

# Regras de compilação
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	g++ $< $(LIBS) -c -o $@

# Regra principal
win: $(obj_files)
	g++ $(obj_files) $(LIBS) -o main.exe
	del $(OBJ_DIR)\*.o
	.\main.exe

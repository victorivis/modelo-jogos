# Diretório onde estão os arquivos fonte
SRC_DIR = src

# Diretório onde serão gerados os arquivos objeto
OBJ_DIR = obj

# Libs
LIBS = -I ..\SDL2\x86_64-w64-mingw32\include\ -L ..\SDL2\x86_64-w64-mingw32\lib\ -I ..\tinyxml2\ -L ..\tinyxml2 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -ltinyxml2

# Arquivos objeto
obj_files = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp))

# Regra para criar o diretório OBJ_DIR se não existir
$(OBJ_DIR):
	if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

# Regras de compilação
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	g++ $< $(LIBS) -c -o $@

# Regra principal
all: $(obj_files)
	g++ $(obj_files) $(LIBS) -o main.exe
	del $(OBJ_DIR)\*.o
	.\main.exe

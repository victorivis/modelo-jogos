LIBS = -I ..\SDL2\x86_64-w64-mingw32\include\ -L ..\SDL2\x86_64-w64-mingw32\lib\ -I ..\tinyxml2\ -L ..\tinyxml2 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -ltinyxml2
obj_files = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

%.o : %.cpp
	g++ $< $(LIBS) -c -o $@

all: $(obj_files)
	g++ $(obj_files) $(LIBS) -o main.exe
	del *.o
	.\main.exe
all: compile link

compile:
	g++ -c main.cpp stdafx.cpp Game.cpp Player.cpp -I"C:\Users\PC\Documents\SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit\SFML-2.5.1\include" -DSFML_STATIC

link:
	g++ main.o stdafx.o Game.o Player.o -o main -L"C:\Users\PC\Documents\SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit\SFML-2.5.1\lib" -lsfml-graphics-s -lsfml-graphics-s -lsfml-audio-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lsfml-main

clean:
	rm -f main *.o
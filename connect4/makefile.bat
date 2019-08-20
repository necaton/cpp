@echo off
g++ -c main.cpp -I"C:\MinGW\SFML-2.5.1\include"
echo main.cpp
g++ -c connect.cpp -I"C:\MinGW\SFML-2.5.1\include"
echo connect.cpp
g++ -c minimax.cpp
echo minimax.cpp
g++ -o connect.exe main.o connect.o minimax.o -static -L"C:\MinGW\SFML-2.5.1\lib" -lsfml-graphics -lsfml-window -lsfml-system
echo connect.exe
pause > nul
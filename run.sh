#!/bin/bash
g++ calculator.cpp -o calculator
g++ -o createeditfile createeditfile.cpp -lsfml-audio -lsfml-system
g++ guessgame.cpp -o guessgame `pkg-config --cflags --libs gtk+-3.0`
g++ movefile.cpp -o movefile `pkg-config --cflags --libs gtk+-3.0`
g++ tictactoe.cpp -o tictactoe
g++ main.cpp -o main
g++ `pkg-config --cflags gtk+-3.0` -o fileinfo fileinfo.cpp `pkg-config --libs gtk+-3.0`

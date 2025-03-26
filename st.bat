@echo off

windres -i block.rc -o block.o

g++ -mwindows game.cpp block.o -o game.exe
#!/bin/bash

# Mise à jour et installation des mises à jour
yes | sudo apt update

# Installation des dépendances nécessaires pour MediaPlayer.c
yes | sudo apt-get install libsdl2-dev
yes | sudo apt-get install libsdl2-image-dev

# Installation des dépendances nécessaires pour les programmes GTK
yes | sudo apt-get install libgtk-3-dev
yes | sudo apt-get install libcanberra-gtk-dev
yes | sudo apt install build-essential

# Compilation des programmes
gcc -Wall ./MediaPlayer.c -o ./MediaPlayer.exe -lSDL2 -lSDL2_image
gcc -Wall ./MonPG1.c -o ./MonPG1.exe `pkg-config --cflags --libs gtk+-3.0`
gcc -Wall ./MonPG2.c -o ./MonPG2.exe `pkg-config --cflags --libs gtk+-3.0` -lm
gcc -Wall ./MonPG3.c -o ./MonPG3.exe `pkg-config --cflags --libs gtk+-3.0`
gcc -Wall ./MonPG4.c -o ./MonPG4.exe `pkg-config --cflags --libs gtk+-3.0`

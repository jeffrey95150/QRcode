#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include "qrcodegen.h"


// Function prototypes
static void black_square(SDL_Surface *screen, SDL_Rect position, int size_pix);
static void doBasicDemo(void);
static void printQr(const uint8_t qrcode[], int size_screen, int size_pix);
static void pause();


static void SDL_WM_SetCaption(char string[8], void *pVoid);

static SDL_Surface *SDL_SetVideoMode(int screen, int screen1, int i, int hwsurface);

static void SDL_Flip(SDL_Surface *pSurface);

// The main application program.
int main(int argc, char *argv[]) {
    doBasicDemo();
    return EXIT_SUCCESS;
}

// Creates a single QR Code, then prints it to the console.
static void doBasicDemo(void) {
    const char *text = "name : Roger\n job : Plombier\n society : Gedimat\n City :Lyon";                // User-supplied text
    enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_LOW;  // Error correction level

    // Make and print the QR Code symbol
    uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
    uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
    bool ok = qrcodegen_encodeText(text, tempBuffer, qrcode, errCorLvl,
                                   qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
    if (ok)
        printQr(qrcode, 340, 10);
}

// /*---- Utilities ----*/

// // Prints the given QR Code to the console.
static void printQr(const uint8_t qrcode[], int size_screen, int size_pix) {

    SDL_Surface *screen = NULL;
    SDL_Surface *rect = NULL;
    SDL_Rect position;

    if(SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Error in SDL init : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }


    int SDL_HWSURFACE;
    screen = SDL_SetVideoMode(size_screen, size_screen, 8, SDL_HWSURFACE);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 17, 206, 112));
    if (screen == NULL)
    {
        fprintf(stderr, "imposible to load video mode  : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("Qr code", NULL);

    int size = qrcodegen_getSize(qrcode);
    int border = 4;

    position.x = 0;
    position.y = 0;
    for (int y = 0; y < size ; y++) {
        for (int x = 0; x < size; x++) {
            if (qrcodegen_getModule(qrcode, x, y))
            {
                position.x += size_pix;
            }else{
                black_square(screen, position, size_pix);
                position.x += size_pix;
            }
        }
        position.x = 0;
        position.y += size_pix;
    }
    SDL_SaveBMP(screen, "Qr-code.bmp");
    SDL_Flip(screen);
    pause();
    SDL_Quit();
}

static void SDL_Flip(SDL_Surface *pSurface) {

}

static SDL_Surface *SDL_SetVideoMode(int screen, int screen1, int i, int hwsurface) {
    return NULL;
}

static void SDL_WM_SetCaption(char string[8], void *pVoid) {

}


void black_square(SDL_Surface *screen, SDL_Rect position, int size_pix)
{
    SDL_Surface *rect = NULL;
    Uint32 SDL_HWSURFACE;
    rect = SDL_CreateRGBSurface(SDL_HWSURFACE, size_pix, size_pix, 8, 0, 0, 0, 0);
    if (rect == NULL)
    {
        fprintf(stderr, "impossible de tracer rect : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FillRect(rect, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    SDL_BlitSurface(rect, NULL, screen, &position);
}

void pause() {
    int continuer = 1;
    SDL_Event event;

    while (continuer) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}
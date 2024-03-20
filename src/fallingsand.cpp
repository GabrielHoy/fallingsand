/*
    Gabriel Hoy
    3/18/2021
    Pixel simulation i'm testing out, nothing big yet
    - Stored for now for future reference as I rewrite this in 2024
*/
#include "SDL2/SDL.h"
#include "GLFW/glfw3.h"
#include <thread>
#include <iostream>

//I use this to simplify the process of writing data to the screen
void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
        Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
        *(Uint32*)target_pixel = pixel;
}

enum ElementType
{
    UNKNOWN = 0,
    SAND = 1,
    SAWDUST = 2
};

struct Pixel
{
    SDL_Point position;
    ElementType element = ElementType::UNKNOWN;
    unsigned int lifetime;
};

int main_old(int argv, char** args)
{
    //Constants&Variables
    int WINDOW_WIDTH = 800;
    int WINDOW_HEIGHT = 800;
    const int REAL_WIDTH = 1024;
    const int REAL_HEIGHT = 1024;
    double lastTime = 0;
    double deltaTime = 0;
    double lastFPSNotice = 0;
    bool shouldQuit = false;
    //Initializations of the libraries
    glfwInit();
    SDL_Init(SDL_INIT_EVERYTHING);
    //Create Window, Renderer, the Surface to draw pixels to and the texture to copy surface pixels to the renderer
    SDL_Window* win = SDL_CreateWindow("SandGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(renderer, 800, 800);
    SDL_Surface* surface = SDL_CreateRGBSurface(0, WINDOW_WIDTH, WINDOW_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    SDL_Event event;
    SDL_Texture* tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_SetRenderTarget(renderer, tex);
    SDL_RenderClear(renderer);
    //pixel array to draw to screen
    Uint32* pixels = (Uint32*)surface->pixels;
    //Main loop
    while (!shouldQuit) {
        //Handle FPS
        double time = glfwGetTime();
        deltaTime = time - lastTime;
        lastTime = time;
        //notify the user of the current FPS
        if (time - lastFPSNotice > 0.5) {
            std::cout << 1.0f/deltaTime << std::endl;
            lastFPSNotice = time;
        }
        //Poll inputs
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                shouldQuit = true;
            }
        }
        //Draw pixels to screen
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            set_pixel(surface, x, 0, SDL_MapRGBA(surface->format, 255, 0, 0, 255));
            for (int y = 0; y < WINDOW_HEIGHT; y++) {
                set_pixel(surface, x, y, SDL_MapRGBA(surface->format, 255, 0, 0, 255));
            }
        }
        
        SDL_UpdateTexture(tex, NULL, surface->pixels, surface->pitch); //pitch is the amount of bytes in one screen row
        //copy the texture to the renderer, and render to the screen
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, tex, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    //Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(tex);
    SDL_DestroyWindow(win);
    
    return 0;
}

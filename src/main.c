#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

/*
    TODO:

    Create a maze struct.
    Blit a maze struct.

    Generate VALID mazes, entrances on the outtermost left and exits on the outtermost right.
    Visualize the path taken to validate the maze.

    For every generated maze, perform, visualize and benchmark:
        1. Depth first search.
        2. Dijkstra's algorithm
        3. A* search algorithm
*/

#include <SDL2/SDL.h>

static void SDL_ErrorAndExit(void)
{
    fprintf(stderr, "%s\n", SDL_GetError());
    exit(EXIT_FAILURE);
}

static void blit_to_window(SDL_Window* window, uint32_t* pixels)
{
    int window_w, window_h;
    SDL_GetWindowSize(window, &window_w, &window_h);

    SDL_Surface* window_surface = SDL_GetWindowSurface(window);
    {
        SDL_UnlockSurface(window_surface);
        memcpy(window_surface->pixels, pixels, window_w * window_h * sizeof(*pixels));
        SDL_LockSurface(window_surface);
    }
    SDL_UpdateWindowSurface(window);
}

static void clear_pixels(uint32_t* pixels, int width, int height, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    for (int i = 0; i < width * height; i++)
    {
        uint32_t rgba = (a << 24) | (r << 16) | (g << 8) | (b << 0);
        pixels[i] = rgba;
    }
}

int main(void)
{
    /* ----------------------------------- Create window ---------------------------------- */
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        SDL_ErrorAndExit();

    const char* window_title = "Maze traversal";
    int window_x = 1000;
    int window_y = 100;
    int window_w = 800;
    int window_h = 450;
    uint32_t window_flags = 0;
    bool window_open = false;

    SDL_Window* window = SDL_CreateWindow(window_title, window_x, window_y, window_w, window_h, 0);
    if (!window)
        SDL_ErrorAndExit();

    /* -------------------------------- Create pixel buffer ------------------------------- */
    int pixel_buffer_w = window_w;
    int pixel_buffer_h = window_h;
    uint32_t* pixel_buffer = malloc(pixel_buffer_w * pixel_buffer_h * sizeof(*pixel_buffer));
    memset(pixel_buffer, 0, pixel_buffer_w * pixel_buffer_h * sizeof(*pixel_buffer));

    window_open = true;
    while(window_open)
    {
        /* -------------------------------------- Render -------------------------------------- */
        clear_pixels(pixel_buffer, pixel_buffer_w, pixel_buffer_h, 0xFF, 0x00, 0x00, 0xFF);
        blit_to_window(window, pixel_buffer);

        /* ------------------------------------ Poll events ----------------------------------- */
        SDL_Event* event = &(SDL_Event) {0};
        while (SDL_PollEvent(event))
        {
            switch(event->type)
            {
                case SDL_QUIT:
                {
                    window_open = false;
                } break;

                case SDL_KEYDOWN:
                {
                    SDL_Keycode keycode = event->key.keysym.sym;
                    switch (keycode)
                    {
                        case SDLK_ESCAPE:
                        {
                            window_open = false;
                        } break;
                    }
                };
            }
        }
    }

    printf("Maze traversal\n");
    exit(EXIT_SUCCESS);
}

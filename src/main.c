#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
    TODO:

    Create a pixel buffer.
    Blit to a pixel buffer.

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

int main(void)
{
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

    window_open = true;
    while(window_open)
    {
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

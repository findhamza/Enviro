#include "learners.h"

int main(int argc, const char* argv[]) {

    Uint32 frameStart, frameTime;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {

        std::cout << "Failed to initialise SDL\n";
        return -1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Demo Game",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        _WIDTH,
        _HEIGHT,
        SDL_WINDOW_OPENGL);
    if (window == nullptr) {

        SDL_Log("Could not create a window: %s", SDL_GetError());
        return -1;
    }

    assert(window);
    auto context = SDL_GL_CreateContext(window);
    if (context == nullptr) {

        SDL_Log("Failed to initizalize OPENGL conext: %s", SDL_GetError());
    }
    
    glewInit();

    objloader iron("../iron.obj");

    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    while (_RUNNING) {

        frameStart = SDL_GetTicks();

        // Get the next event
        _RUNNING = ProcessInput();


        glViewport(0, 0, _WIDTH, _HEIGHT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum(1.0 * _RATIO, 1.0 * _RATIO, 1.0, 1.0, 1.5, 100.0);
        //glOrtho(-1.0, 1.0, -1.0, 1.0, 1.5, 1000.0);
        glMatrixMode(GL_MODELVIEW);
        glClear(GL_COLOR_BUFFER_BIT);
        //cube.draw();

        iron.draw();

        SDL_GL_SwapWindow(window);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < DELAY_TIME) {

            SDL_Delay((int)(DELAY_TIME - frameTime));
        }
    }

    // Tidy up
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

bool ProcessInput() {

    SDL_Event Event;
    while (SDL_PollEvent(&Event))
    {
        if (Event.type == SDL_KEYDOWN)
        {
            switch (Event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                return false;
            case 'a':
                SDL_Delay(3000);
            default:
                break;
            }
        }
        else if (Event.type == SDL_QUIT)
        {
            return false;
        }
    }

    return true;
}
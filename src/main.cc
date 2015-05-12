#include <SDL2/SDL.h>

#include "input.h"
#include "graphics.h"

int main() {
  SDL_Init(SDL_INIT_EVERYTHING);

  Graphics graphics;
  Input input;

  SDL_Event event;
  bool running = true;

  while (running) {
    input.reset();
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      } else {
        input.handle_event(event);
      }
    }

    if (input.key_pressed(Input::UP)) {
      fprintf(stderr, "Pressed up\n");
    } else if (input.key_pressed(Input::DOWN)) {
      fprintf(stderr, "Pressed down\n");
    }

    if (input.key_pressed(Input::LEFT)) {
      fprintf(stderr, "Pressed left\n");
    } else if (input.key_pressed(Input::RIGHT)) {
      fprintf(stderr, "Pressed right\n");
    }

    if (input.key_pressed(Input::ACCEPT)) {
      fprintf(stderr, "Pressed accept\n");
    } else if (input.key_pressed(Input::CANCEL)) {
      fprintf(stderr, "Pressed cancel\n");
    }

    // updates

    graphics.clear();
    // draw
    graphics.flip();
  }
}

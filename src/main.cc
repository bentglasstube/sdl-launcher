#include <SDL2/SDL.h>

#include "input.h"
#include "graphics.h"
#include "text.h"

int main() {
  SDL_Init(SDL_INIT_EVERYTHING);

  Graphics graphics;
  Input input;
  Text text(graphics, "font");

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

    text.draw(graphics, "SDL Launcher", 320, 32, Text::CENTER);

    text.draw(graphics, "Castlevania", 200, 128);
    text.draw(graphics, "Castlevania II: Simon's Quest", 200, 144);
    text.draw(graphics, "Dr. Mario", 200, 160);
    text.draw(graphics, "Super Mario Bros.", 200, 176);
    text.draw(graphics, "The Legend of Zelda", 200, 192);

    graphics.flip();
  }
}

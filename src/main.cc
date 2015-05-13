#include <SDL2/SDL.h>

#include "input.h"
#include "graphics.h"
#include "menu_list.h"
#include "text.h"

int main() {
  SDL_Init(SDL_INIT_EVERYTHING);

  Graphics graphics;
  Input input;
  Text text(graphics, "font");

  SDL_Event event;
  bool running = true;

  std::vector<std::string> games;
  games.reserve(32);

  games.push_back("Castlevania");
  games.push_back("Castlevania II: Simon's Quest");
  games.push_back("Castlevania III: Dracula's Curse");
  games.push_back("Dr. Mario");
  games.push_back("Duck Tales");
  games.push_back("Final Fantasy");
  games.push_back("Guardian Legend, The");
  games.push_back("Legend of Zelda, The");
  games.push_back("Mega Man");
  games.push_back("Mega Man 2");
  games.push_back("Mega Man 3");
  games.push_back("Mega Man 4");
  games.push_back("Mega Man 5");
  games.push_back("Mega Man 6");
  games.push_back("Metroid");
  games.push_back("Shadowgate");
  games.push_back("Super Mario Bros.");
  games.push_back("Super Mario Bros. 2");
  games.push_back("Super Mario Bros. 3");
  games.push_back("Where's Waldo");
  games.push_back("Zelda II - The Adventure of Link");

  MenuList menu(games, 288, 280);

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
      menu.up();
    } else if (input.key_pressed(Input::DOWN)) {
      fprintf(stderr, "Pressed down\n");
      menu.down();
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

    text.draw(graphics, "Hipster Launcher", 320, 0, Text::CENTER);
    menu.draw(graphics, 16, 64);

    graphics.flip();
  }
}

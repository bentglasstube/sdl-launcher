#include <SDL2/SDL.h>

#include <sstream>

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


  games.push_back("Castlevania (USA) (Rev A)");
  games.push_back("Castlevania II - Simon's Quest (USA)");
  games.push_back("Castlevania III - Dracula's Curse (USA)");
  games.push_back("Dr. Mario (Japan, USA)");
  games.push_back("Duck Tales (USA)");
  games.push_back("Final Fantasy (USA)");
  games.push_back("Guardian Legend, The (USA)");
  games.push_back("Legend of Zelda, The (USA) (Rev A)");
  games.push_back("Mega Man (USA)");
  games.push_back("Mega Man 2 (USA)");
  games.push_back("Mega Man 3 (USA)");
  games.push_back("Mega Man 4 (USA) (Rev A)");
  games.push_back("Mega Man 5 (USA)");
  games.push_back("Mega Man 6 (USA)");
  games.push_back("Metroid (USA)");
  games.push_back("Shadowgate (USA)");
  games.push_back("Super Mario Bros. (Japan, USA)");
  games.push_back("Super Mario Bros. 2 (USA) (Rev A)");
  games.push_back("Super Mario Bros. 3 (USA) (Rev A)");
  games.push_back("Where's Waldo (USA)");
  games.push_back("Zelda II - The Adventure of Link (USA)");

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
      menu.up();
    } else if (input.key_pressed(Input::DOWN)) {
      menu.down();
    }

    if (input.key_pressed(Input::LEFT)) {
      fprintf(stderr, "Pressed left\n");
    } else if (input.key_pressed(Input::RIGHT)) {
      fprintf(stderr, "Pressed right\n");
    }

    if (input.key_pressed(Input::ACCEPT)) {
      std::ostringstream command;
      command << "retroarch -f -c ~/.config/retroarch/retroarch.cfg \"/home/alan/Downloads/Roms/NES/";
      command << menu.selected_value();
      command << ".nes\"";

      system(command.str().c_str());
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

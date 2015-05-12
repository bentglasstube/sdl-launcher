#include "text.h"

#include "graphics.h"

Text::Text(Graphics& graphics, std::string file) {
  this->file = file;
  graphics.load_image(file, true);
}

void Text::draw(Graphics& graphics, std::string text, int x, int y, Alignment alignment) {
  SDL_Rect source = {8, 0, 8, 16 };
  SDL_Rect dest = { x, y, 8, 16 };

  switch(alignment) {
    case Text::LEFT:
      break;

    case Text::CENTER:
      dest.x -= 4 * text.length();
      break;

    case Text::RIGHT:
      dest.x -= 8 * text.length();
      break;
  }

  for (std::string::iterator i = text.begin(); i != text.end(); ++i) {
    int n = (*i) - ' ';

    if (n >= 0 && n < 127) {
      source.x = (n % 16) * 8;
      source.y = (n / 16) * 16;
      graphics.blit(file, &source, &dest);
    }

    dest.x += 8;
  }
}

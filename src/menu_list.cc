#include "menu_list.h"

#include "graphics.h"
#include "text.h"

namespace {
  static const unsigned int line_height = 16;
}

MenuList::MenuList(std::vector<std::string> items, unsigned int w, unsigned int h) :
  items(items),
  current(0), scroll_pos(0),
  width(w), height(h) {}

bool MenuList::up() {
  if (current == 0) return false;

  current--;
  if (current < scroll_pos) scroll_pos = current;
  return true;
}

bool MenuList::down() {
  if (current == max()) return false;

  current++;
  if (current - scroll_pos >= lines()) scroll_pos = current - lines() + 1;
  return true;
}

unsigned int MenuList::selected() {
  return current;
}

std::string MenuList::item(unsigned int index) {
  return items[index];
}

std::string MenuList::selected_value() {
  return items[current];
}

void MenuList::draw(Graphics& graphics, unsigned int x, unsigned int y) {
  Text text(graphics, "font");

  // draw the selection background
  SDL_Rect selbg = { 8, 0, 8, 16 };
  SDL_Rect selection = {
    (int) x,
    (int) (y + line_height * (current - scroll_pos)),
    (int) (width - 16),
    (int) line_height
  };
  graphics.blit("ui", &selbg, &selection);

  // draw this list items
  for (unsigned int i = 0; i < lines(); ++i) {
    if (scroll_pos + i > max()) break;
    text.draw(graphics, item(scroll_pos + i), x, y + line_height * i);
  }

  // draw the scrollbar
  SDL_Rect sbsrc = { 0, 0, 8, 4 };
  SDL_Rect sbdest = { (int) (x + width - 8), (int) y, 8, (int) height };
  graphics.blit("ui", &sbsrc, &sbdest);

  sbsrc.y = 4;
  sbdest.y = y + height * scroll_pos / items.size();
  sbdest.h = 4;
  graphics.blit("ui", &sbsrc, &sbdest);

  sbsrc.y = 8;
  sbdest.y += 4;
  sbdest.h = height * lines() / items.size() - 8;
  graphics.blit("ui", &sbsrc, &sbdest);

  sbsrc.y = 12;
  sbdest.y += sbdest.h;
  sbdest.h = 4;
  graphics.blit("ui", &sbsrc, &sbdest);
}

unsigned int MenuList::max() {
  return items.empty() ? 0 : items.size() - 1;
}

unsigned int MenuList::lines() {
  return height / line_height;
}

#pragma once

#include <vector>
#include <string>

class Graphics;

class MenuList {
  public:

    MenuList(std::vector<std::string> items, unsigned int w, unsigned int h);

    bool up();
    bool down();
    unsigned int selected();
    std::string item(unsigned int index);
    std::string selected_value();

    void draw(Graphics& graphics, unsigned int x, unsigned int y);

  private:

    std::vector<std::string> items;
    unsigned int current, scroll_pos, width, height;

    unsigned int max();
    unsigned int lines();
};

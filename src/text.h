#pragma once

#include <string>

class Graphics;

class Text {
  public:

    enum Alignment { LEFT, CENTER, RIGHT };

    Text(Graphics& graphics, std::string file);

    void draw(Graphics& graphics, std::string text, int x, int y, Alignment alignment=LEFT);

  private:

    std::string file;
};

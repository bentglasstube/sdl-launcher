#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <map>

class Graphics {
  public:

    Graphics();
    ~Graphics();

    void clear();
    void flip();
    void blit(std::string texture, SDL_Rect* source, SDL_Rect* dest);
    void load_image(std::string file, bool transparency=false);

  private:

    typedef std::map<std::string, SDL_Texture*> TextureMap;

    SDL_Window* window;
    SDL_Renderer* renderer;
    TextureMap textures;
};

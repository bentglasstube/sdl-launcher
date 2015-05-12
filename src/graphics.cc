#include "graphics.h"

namespace {
  const unsigned int width = 640;
  const unsigned int height = 360;
}

Graphics::Graphics() {
  int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP;
  window = SDL_CreateWindow("Launcher", 0, 0, width, height, flags);
  renderer = SDL_CreateRenderer(window, -1, 0);

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
  SDL_RenderSetLogicalSize(renderer, width, height);

  SDL_ShowCursor(SDL_DISABLE);
}

Graphics::~Graphics() {
  for (TextureMap::iterator i = textures.begin(); i != textures.end(); ++i) {
    SDL_DestroyTexture(i->second);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void Graphics::clear() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void Graphics::flip() {
  SDL_RenderPresent(renderer);
}

void Graphics::blit(std::string texture, SDL_Rect* source, SDL_Rect* dest) {
  load_image(texture);
  SDL_RenderCopy(renderer, textures[texture], source, dest);
}

void Graphics::load_image(std::string file, bool transparency) {
  const std::string path("content/" + file + ".bmp");

  if (textures.count(file) == 0) {
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if (transparency) {
      const Uint32 black = SDL_MapRGB(surface->format, 0, 0, 0);
      SDL_SetColorKey(surface, SDL_TRUE, black);
    }
    textures[file] = SDL_CreateTextureFromSurface(renderer, surface);
  }
}

#pragma once

#include <map>
#include <SDL2/SDL.h>

namespace {
  const unsigned int max_axes = 8;
}

class Input {
  public:

    enum Key { NONE, UP, DOWN, LEFT, RIGHT, ACCEPT, CANCEL };

    Input();
    ~Input();

    void reset();
    void handle_event(const SDL_Event& event);
    bool key_pressed(Key key);

  private:

    void press_key(Key key);

    static Key key_map(SDL_Keycode keycode);
    static Key joy_button_map(Uint8 button);
    static Key joy_axis_map(Uint8 axis, bool positive);

    std::map<Key, bool> keys_pressed;
    SDL_Joystick* joystick;
    int axis_last[max_axes], hat_last_x, hat_last_y;
};

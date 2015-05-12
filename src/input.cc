#include "input.h"

namespace {
  const Sint16 joystick_dead_zone = 16000;
}

Input::Input() {
  if (SDL_NumJoysticks > 0) joystick = SDL_JoystickOpen(0);

  for (unsigned int i = 0; i < max_axes; ++i) {
    axis_last[i] = 0;
  }
}

Input::~Input() {
  if (joystick != NULL) SDL_JoystickClose(joystick);
}

void Input::reset() {
  keys_pressed.clear();
}

void Input::handle_event(const SDL_Event& event) {
  switch (event.type) {
    case SDL_KEYDOWN:
      if (event.key.repeat == 0) press_key(key_map(event.key.keysym.sym));
      break;

    case SDL_JOYBUTTONDOWN:
      press_key(joy_button_map(event.jbutton.button));
      break;

    case SDL_JOYHATMOTION:
      int dx, dy;

      switch (event.jhat.value) {
        case SDL_HAT_LEFTUP:    dx = -1; dy = -1; break;
        case SDL_HAT_LEFT:      dx = -1; dy =  0; break;
        case SDL_HAT_LEFTDOWN:  dx = -1; dy =  1; break;
        case SDL_HAT_UP:        dx =  0; dy = -1; break;
        case SDL_HAT_CENTERED:  dx =  0; dy =  0; break;
        case SDL_HAT_DOWN:      dx =  0; dy =  1; break;
        case SDL_HAT_RIGHTUP:   dx =  1; dy = -1; break;
        case SDL_HAT_RIGHT:     dx =  1; dy =  0; break;
        case SDL_HAT_RIGHTDOWN: dx =  1; dy =  1; break;
      }

      if (dx != 0 && dx != hat_last_x) press_key(dx < 0 ? Input::LEFT : Input::RIGHT);
      if (dy != 0 && dy != hat_last_y) press_key(dy < 0 ? Input::UP : Input::DOWN);

      hat_last_x = dx;
      hat_last_y = dy;

      break;

    case SDL_JOYAXISMOTION:
      if (event.jaxis.axis >= max_axes) break;

      int dir = 0;
      if (event.jaxis.value < -joystick_dead_zone) dir = -1;
      else if (event.jaxis.value > joystick_dead_zone) dir = 1;

      if (dir != 0 && dir != axis_last[event.jaxis.axis])
        press_key(joy_axis_map(event.jaxis.axis, dir > 0));

      axis_last[event.jaxis.axis] = dir;

      break;
  }
}

bool Input::key_pressed(Key key) {
  return keys_pressed[key];
}

void Input::press_key(Key key) {
  keys_pressed[key] = true;
}

Input::Key Input::key_map(SDL_Keycode keycode) {
  switch (keycode) {
    case SDLK_UP:
    case SDLK_w:
    case SDLK_k:
      return Input::UP;

    case SDLK_DOWN:
    case SDLK_s:
    case SDLK_j:
      return Input::DOWN;

    case SDLK_LEFT:
    case SDLK_a:
    case SDLK_h:
      return Input::LEFT;

    case SDLK_RIGHT:
    case SDLK_d:
    case SDLK_l:
      return Input::RIGHT;

    case SDLK_RETURN:
    case SDLK_SPACE:
      return Input::ACCEPT;

    case SDLK_ESCAPE:
    case SDLK_BACKQUOTE:
    case SDLK_BACKSPACE:
      return Input::CANCEL;

    default:
      return Input::NONE;
  }
}

Input::Key Input::joy_button_map(Uint8 button) {
  switch (button) {
    case  0:
    case  3:
    case  4:
    case  6:
      return Input::CANCEL;

    case  1:
    case  2:
    case  5:
    case  7:
      return Input::ACCEPT;

    default:
      return Input::NONE;
  }
}

Input::Key Input::joy_axis_map(Uint8 axis, bool positive) {
  switch (axis) {
    case 0:
    case 2:
      return positive ? Input::RIGHT : Input::LEFT;

    case 1:
    case 3:
      return positive ? Input::DOWN : Input::UP;

    case 4:
      return positive ? Input::ACCEPT : Input::NONE;

    case 6:
      return positive ? Input::CANCEL : Input::NONE;

    default:
      return Input::NONE;
  }
}

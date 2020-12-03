#include "KeyEventListener.h"

std::map<SDL_Keycode, bool> KeyEventListener::keyMap = std::map<SDL_Keycode, bool>();

void KeyEventListener::Press(const SDL_Keycode e_){
	keyMap[e_] = true;
}

void KeyEventListener::Release(SDL_Keycode e_){
	keyMap[e_] = false;
}



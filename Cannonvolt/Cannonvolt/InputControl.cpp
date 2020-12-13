#include "InputControl.h"
#include "Engine/Events/KeyEventListener.h"

InputControl::InputControl() {

}

InputControl::~InputControl(){
	player = nullptr;
}

void InputControl::Init(Character* player_){
	player = player_;
}

void InputControl::Update(float deltaTime_) {

	if (player->GetMod("Movement")) {
		if (KeyEventListener::keyMap[SDLK_a]) {
			player->Flip(true);
			player->ApplyForce(glm::vec2(-50.0f, 0.0f), player->GetRotation());
		}
		else if (KeyEventListener::keyMap[SDLK_d]) {
			player->Flip(false);
			player->ApplyForce(glm::vec2(50.0f, 0.0f), player->GetRotation());
		}

	    if (KeyEventListener::keyMap[SDLK_LSHIFT]) {
			if (player->GetSprite()->GetFlip() == true) {
				player->Translate(glm::vec2(-10.0f, 0.0f));
			}
			else {
			player->Translate(glm::vec2(10.0f, 0.0f));
			}
		}
	}
	if (player->GetMod("Jump")) {
		if (KeyEventListener::keyMap[SDLK_SPACE] && player->GetJump()) {
			player->ApplyForce(glm::vec2(0, 6250.0f), 0);
			player->SetJump(false);
		}
	}
	if (player->GetMod("Shoot")) {
		if (KeyEventListener::keyMap[SDLK_f]) {
			player->Shot();
		}
	}
	if (player->GetMod("Flight")) {
			if (KeyEventListener::keyMap[SDLK_d]) {
				player->SetRotation(player->GetRotation() + 1);
			}
			if (KeyEventListener::keyMap[SDLK_a]) {
				player->SetRotation(player->GetRotation() - 1);
			}
	}
}
/*Calls the KeyEventListener, grabs the keyMap and responds to pressing the spacebar [SDLK_SPACE]
when space is pressed, it will return an output that lets the character move 2.0f on the Y axis*/

//TO DO : LET THE CHARACTER FALL WHEN CHARACTER SPACE IS RELEASED


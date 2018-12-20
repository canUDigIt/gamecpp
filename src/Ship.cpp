#include "Ship.h"

#include "AnimSpriteComponent.h"
#include "Game.h"

Ship::Ship(Game *pGame) : Actor(pGame) {
  AnimSpriteComponent *pAsc = new AnimSpriteComponent(this);
  std::vector<SDL_Texture *> anims = {
    pGame->GetTexture("Assets/Ship01.png"),
    pGame->GetTexture("Assets/Ship02.png"),
    pGame->GetTexture("Assets/Ship03.png"),
    pGame->GetTexture("Assets/Ship04.png"),
  };
  pAsc->SetAnimTextures(anims);
  pAsc->SetAnimFPS(4.f);
  AddComponent(pAsc);
}

void Ship::UpdateActor(float deltaTime) {
  Actor::UpdateActor(deltaTime);

  Vector2 pos = GetCenterPosition();
  pos.x += m_RightSpeed * deltaTime;
  pos.y += m_DownSpeed * deltaTime;

  SetCenterPosition(pos);
}

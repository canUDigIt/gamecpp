#pragma once

#include <Actor.h>

#include <cstdint>

class Ship : public Actor {
public:
  Ship(class Game *pGame);
  void UpdateActor(float deltaTime) override;
  void ProcessKeyboard(const uint8_t *state);
  float GetRightSpeed() const { return m_RightSpeed; }
  float GetDownSpeed() const { return m_DownSpeed; }

private:
  float m_RightSpeed = 0.f;
  float m_DownSpeed = 0.f;
};
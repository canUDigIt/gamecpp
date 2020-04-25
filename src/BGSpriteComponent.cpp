#include "BGSpriteComponent.h"

#include "Actor.h"
#include <SDL.h>

#include <cmath>

float wrap(float x, float start, float end) {
    return start + fmodf((x - start), (end - start));
}

BGSpriteComponent::BGSpriteComponent(Actor *pOwner, int drawOrder)
    : SpriteComponent(pOwner, drawOrder) {}

void BGSpriteComponent::Update(float deltaTime) {
  SpriteComponent::Update(deltaTime);

  float minX = -(m_BGTextures.size() - 1) * m_ScreenSize.x;
  float maxX = m_ScreenSize.x;

  for (auto &bg : m_BGTextures) {
    bg.m_Offset.x += m_ScrollSpeed * deltaTime;
    // If this is completely off the screen, reset offset to
    // the right of the last bg texture
    bg.m_Offset.x = wrap(bg.m_Offset.x, minX, maxX);
  }
}

void BGSpriteComponent::Draw(SDL_Renderer *pRenderer) {
  for (const auto &bg : m_BGTextures) {
    SDL_Rect r;
    r.x = m_Owner->GetCenterPosition().x + bg.m_Offset.x;
    r.y = m_Owner->GetCenterPosition().y + bg.m_Offset.y;
    r.w = m_ScreenSize.x;
    r.h = m_ScreenSize.y;
    SDL_RenderCopy(pRenderer, bg.m_pTexture, nullptr, &r);
  }
}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture *> &textures) {
  float minX = -(textures.size() - 1) * m_ScreenSize.x;
  float maxX = m_ScreenSize.x;
  for (int count = 0; count < textures.size(); ++count) {
    BGTexture temp;
    temp.m_Offset.x = wrap(count * m_ScreenSize.x, minX, maxX);
    temp.m_Offset.y = 0;
    temp.m_pTexture = textures[count];
    m_BGTextures.emplace_back(temp);
  }
}

#include "BGSpriteComponent.h"

#include "Actor.h"
#include <SDL.h>

BGSpriteComponent::BGSpriteComponent(Actor *pOwner, int drawOrder)
    : SpriteComponent(pOwner, drawOrder) {}

void BGSpriteComponent::Update(float deltaTime) {
  SpriteComponent::Update(deltaTime);
  for (auto &bg : m_BGTextures) {
    bg.m_Offset.x += m_ScrollSpeed * deltaTime;
    // If this is completely off the screen, reset offset to
    // the right of the last bg texture
    if (bg.m_Offset.x > m_ScreenSize.x) {
      bg.m_Offset.x = (m_BGTextures.size() - 1) * m_ScreenSize.x - 1;
    }
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
  int count = 0;
  for (const auto &tex : textures) {
    BGTexture temp;
    temp.m_Offset.x = count * m_ScreenSize.x;
    temp.m_Offset.y = 0;
    temp.m_pTexture = tex;
    m_BGTextures.emplace_back(temp);
    count++;
  }
}

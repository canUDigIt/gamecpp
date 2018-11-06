#include <SpriteComponent.h>

#include <Actor.h>
#include <Game.h>
#include <SDL.h>

SpriteComponent::SpriteComponent(Actor *pOwner, int drawOrder)
    : Component(pOwner), m_DrawOrder(drawOrder) {
  m_Owner->AddComponent(this);
  m_Owner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() { m_Owner->RemoveComponent(this); }

void SpriteComponent::Draw(SDL_Renderer *pRenderer) {
  if (m_pTexture) {
    SDL_Rect r;
    r.w = static_cast<int>(m_TexWidth * m_Owner->GetScale());
    r.h = static_cast<int>(m_TexHeight * m_Owner->GetScale());
    r.x = static_cast<int>(m_Owner->GetCenterPosition().x - r.w / 2);
    r.y = static_cast<int>(m_Owner->GetCenterPosition().y - r.h / 2);

    int ret = SDL_RenderCopyEx(pRenderer, m_pTexture, nullptr, &r,
                     m_Owner->GetRotation().ToDegrees(), nullptr,
                     SDL_FLIP_NONE);
    if (ret != 0) {
        SDL_Log("Sprite rendering failed: %s", SDL_GetError());
    }
  }
}

void SpriteComponent::SetTexture(SDL_Texture *pTexture) {
  m_pTexture = pTexture;
  SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_TexWidth, &m_TexHeight);
}

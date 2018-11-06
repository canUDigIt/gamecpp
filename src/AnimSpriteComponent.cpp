#include <AnimSpriteComponent.h>

AnimSpriteComponent::AnimSpriteComponent(Actor *pOwner, int drawOrder)
    : SpriteComponent(pOwner, drawOrder) {}

void AnimSpriteComponent::Update(float deltaTime) {
  SpriteComponent::Update(deltaTime);

  if (m_AnimTextures.size() > 0) {
    // Update current frame based on frame rate and delta time
    m_CurrFrame += m_AnimFPS * deltaTime;

    // Wrap current frame if needed
    while (m_CurrFrame >= m_AnimTextures.size()) {
      m_CurrFrame -= m_AnimTextures.size();
    }

    SetTexture(m_AnimTextures[static_cast<int>(m_CurrFrame)]);
  }
}

void AnimSpriteComponent::SetAnimTextures(
    const std::vector<SDL_Texture *> &textures) {
  m_AnimTextures = textures;
  m_CurrFrame = 0.f;
  SetTexture(textures[static_cast<int>(m_CurrFrame)]);
}

#ifndef BGSPRITECOMPONENT_H
#define BGSPRITECOMPONENT_H

#include <SpriteComponent.h>

#include <Vector2.h>

#include <vector>

class BGSpriteComponent : public SpriteComponent {
public:
  BGSpriteComponent(class Actor *pOwner, int drawOrder = 10);

  void Update(float deltaTime) override;
  void Draw(SDL_Renderer *pRenderer) override;

  void SetBGTextures(const std::vector<SDL_Texture *> &textures);
  void SetScreenSize(const Vector2 &size) { m_ScreenSize = size; }
  void SetScrollSpeed(float speed) { m_ScrollSpeed = speed; }
  float GetScrollSpeed() const { return m_ScrollSpeed; }

private:
  struct BGTexture {
    SDL_Texture *m_pTexture;
    Vector2 m_Offset;
  };
  std::vector<BGTexture> m_BGTextures;
  Vector2 m_ScreenSize;
  float m_ScrollSpeed = 0.f;
};

#endif

#include <SpriteComponent.h>

#include <vector>

class AnimSpriteComponent : public SpriteComponent {
public:
  AnimSpriteComponent(class Actor *pOwner, int drawOrder = 100);

  // Update animation every frame (overriden from component)
  void Update(float deltaTime) override;
  void SetAnimTextures(const std::vector<SDL_Texture *> &textures);

  float GetAnimFPS() const { return m_AnimFPS; }
  void SetAnimFPS(float fps) { m_AnimFPS = fps; }

private:
  std::vector<SDL_Texture *> m_AnimTextures;
  float m_CurrFrame = 0.f;
  float m_AnimFPS = 0.f;
};

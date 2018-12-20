#pragma once

#include "Component.h"

class SpriteComponent : public Component
{
public:
    SpriteComponent(class Actor* pOwner, int drawOrder = 100);
    ~SpriteComponent();
    virtual void Draw(class SDL_Renderer* pRenderer);
    virtual void SetTexture(class SDL_Texture* pTexture);

    int GetDrawOrder() const { return m_DrawOrder; }
    int GetTexHeight() const { return m_TexHeight; }
    int GetTexWidth() const { return m_TexWidth; }

protected:
    class SDL_Texture* m_pTexture;
    int m_DrawOrder = 100;
    int m_TexWidth = 0;
    int m_TexHeight = 0;
};

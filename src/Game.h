#pragma once

#include <vector>
#include <string>
#include <map>

class SDL_Window;
class SDL_Texture;
class SDL_Renderer;

class Game {
public:
  Game();
  bool Initialize();
  void RunLoop();
  void Shutdown();

  void AddActor(class Actor *pActor);
  void RemoveActor(class Actor *pActor);

  void AddSprite(class SpriteComponent* pSprite);
  void RemoveSprite(class SpriteComponent* pSprite);

  SDL_Texture* GetTexture(const std::string& filename);

private:
  void ProcessInputs();
  void UpdateGame();
  void GenerateOutput();
  SDL_Texture* LoadTexture(const std::string& filename);
  void LoadData();

  SDL_Window *m_Window = nullptr;
  SDL_Renderer* m_pRenderer = nullptr;

  float m_TicksCount = 0.0f;

  bool m_IsRunning = true;
  bool m_UpdatingActors = false;

  std::vector<class Actor *> m_Actors;
  std::vector<class Actor *> m_PendingActors;

  std::vector<class SpriteComponent *> m_Sprites;

  std::map<std::string, SDL_Texture*> m_Textures;
};

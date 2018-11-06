#include <Game.h>

#include <SDL.h>
#include <SDL_image.h>

#include <BGSpriteComponent.h>
#include <Ship.h>

#include <algorithm>

Game::Game() {}

bool Game::Initialize() {
  int sdlResult = SDL_Init(SDL_INIT_VIDEO);
  if (sdlResult != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return false;
  }

  m_Window = SDL_CreateWindow("Game Programming in C++ (Chapter 1)", 100, 100,
                              1024, 768, 0);

  if (!m_Window) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return false;
  }

  m_pRenderer = SDL_CreateRenderer(
      m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!m_pRenderer) {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    return false;
  }
  SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);

  IMG_Init(IMG_INIT_PNG);

  LoadData();

  return true;
}

void Game::Shutdown() {
  // Because ~Actor calls RemoveActor, delete backwards
  while (!m_Actors.empty()) {
    delete m_Actors.back();
  }

  for (const auto &item : m_Textures) {
    SDL_DestroyTexture(item.second);
  }

  SDL_DestroyRenderer(m_pRenderer);
  SDL_DestroyWindow(m_Window);
  SDL_Quit();
}

void Game::RunLoop() {
  while (m_IsRunning) {
    ProcessInputs();
    UpdateGame();
    GenerateOutput();
  }
}

void Game::AddActor(Actor *pActor) {
  if (m_UpdatingActors) {
    m_PendingActors.emplace_back(pActor);
  } else {
    m_Actors.emplace_back(pActor);
  }
}

void Game::RemoveActor(Actor *pActor) {
  if (!m_PendingActors.empty()) {
    m_PendingActors.erase(std::remove(std::begin(m_PendingActors),
                                      std::end(m_PendingActors), pActor));
  }

  if (!m_Actors.empty()) {
    m_Actors.erase(
        std::remove(std::begin(m_Actors), std::end(m_Actors), pActor));
  }
}

void Game::AddSprite(SpriteComponent *pSprite) {
  // Find the insertion point in the sorted vector
  // (The first element with a higher draw order than me)
  int myDrawOrder = pSprite->GetDrawOrder();
  auto iter = std::find_if(std::begin(m_Sprites), std::end(m_Sprites),
                           [myDrawOrder](SpriteComponent *pItem) {
                             return myDrawOrder < pItem->GetDrawOrder();
                           });
  m_Sprites.insert(iter, pSprite);
}

void Game::RemoveSprite(SpriteComponent *pSprite) {
  m_Sprites.erase(
      std::remove(std::begin(m_Sprites), std::end(m_Sprites), pSprite));
}

SDL_Texture *Game::GetTexture(const std::string &filename) {
  SDL_Texture *pTexture = nullptr;
  auto texture = m_Textures.find(filename);
  if (texture != m_Textures.end()) {
    pTexture = texture->second;
  } else {
    pTexture = LoadTexture(filename);
    if (pTexture) {
      m_Textures.emplace(filename, pTexture);
    }
  }
  return pTexture;
}

void Game::ProcessInputs() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      m_IsRunning = false;
      break;
    default:
      break;
    }
  }

  const Uint8 *state = SDL_GetKeyboardState(nullptr);
  if (state[SDL_SCANCODE_ESCAPE]) {
    m_IsRunning = false;
  }
}

void Game::UpdateGame() {
  float deltaTime = (SDL_GetTicks() - m_TicksCount) / 1000.0f;
  m_TicksCount = SDL_GetTicks();

  m_UpdatingActors = true;
  for (auto pActor : m_Actors) {
    pActor->Update(deltaTime);
  }
  m_UpdatingActors = false;

  for (auto pPending : m_PendingActors) {
    m_Actors.emplace_back(pPending);
  }
  m_PendingActors.clear();

  std::vector<Actor *> deadActors;
  for (auto pActor : m_Actors) {
    if (pActor->GetState() == Actor::State::EDead) {
      deadActors.emplace_back(pActor);
    }
  }

  for (auto pActor : deadActors) {
    delete pActor;
  }
}

void Game::GenerateOutput() {
  SDL_RenderClear(m_pRenderer);

  for (auto pSprite : m_Sprites) {
    pSprite->Draw(m_pRenderer);
  }

  SDL_RenderPresent(m_pRenderer);
}

SDL_Texture *Game::LoadTexture(const std::string &filename) {
  SDL_Surface *pSurface = IMG_Load(filename.c_str());
  if (!pSurface) {
    SDL_Log("Failed to load texture file %s", filename.c_str());
    return nullptr;
  }

  SDL_Texture *pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);
  SDL_FreeSurface(pSurface);
  if (!pTexture) {
    SDL_Log("Failed to convert surface to texture for %s", filename.c_str());
    return nullptr;
  }
  return pTexture;
}

void Game::LoadData() {
  Ship *pShip = new Ship(this);

  int w = 0, h = 0;
  SDL_GetWindowSize(m_Window, &w, &h);
  Vector2 pos {w/3.f, h/2.f};
  pShip->SetCenterPosition(pos);

  Actor *pSpace = new Actor(this);
  BGSpriteComponent *pForeground = new BGSpriteComponent(pSpace, 1);
  BGSpriteComponent *pBackground = new BGSpriteComponent(pSpace, 0);
  std::vector<SDL_Texture *> foregroundTextures = {
      GetTexture("Assets/Stars.png")};
  std::vector<SDL_Texture *> backgroundTextures = {
      GetTexture("Assets/Farback01.png"), GetTexture("Assets/Farback02.png")};

  Vector2 windowSize{static_cast<float>(w), static_cast<float>(h)};
  pForeground->SetScreenSize(windowSize);
  pForeground->SetScrollSpeed(10.0f);
  pForeground->SetBGTextures(foregroundTextures);
  pBackground->SetScreenSize(windowSize);
  pBackground->SetScrollSpeed(5.0f);
  pBackground->SetBGTextures(backgroundTextures);
}

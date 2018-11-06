#include <Actor.h>

#include <Component.h>
#include <Game.h>

#include <algorithm>
#include <functional>

Actor::Actor(Game* pGame) : m_pGame(pGame) {
    m_pGame->AddActor(this);
}
Actor::~Actor() {
    m_pGame->RemoveActor(this);
}

void Actor::Update(float deltaTime) {
    if (GetState() == Actor::State::EActive) {
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
    if (GetState() == Actor::State::EDead) {
        m_pGame->RemoveActor(this);
    }
}
void Actor::UpdateComponents(float deltaTime) {
    std::for_each(std::begin(m_Components), std::end(m_Components), [deltaTime](Component* pComp) { pComp->Update(deltaTime); });
}
void Actor::UpdateActor(float /*deltaTime*/) {}

void Actor::SetState(State state) {
    m_State = state;
}
Actor::State Actor::GetState() const {
    return m_State;
}

void Actor::SetCenterPosition(const Vector2& pos) {
    m_CenterPosition = pos;
}
Vector2 Actor::GetCenterPosition() const {
    return m_CenterPosition;
}

void Actor::SetScale(float scale) {
    m_Scale = scale;
}
float Actor::GetScale() const {
    return m_Scale;
}

void Actor::SetRotation(const Radians& rot) {
    m_Rotation = rot;
}
Radians Actor::GetRotation() const {
    return m_Rotation;
}

Game* Actor::GetGame() const { return m_pGame; }

void Actor::AddComponent(Component* pComponent) {
    m_Components.push_back(pComponent);
}
void Actor::RemoveComponent(Component* pComponent) {
    m_Components.erase(std::remove(std::begin(m_Components), std::end(m_Components), pComponent));
}

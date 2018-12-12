#pragma once

#include <Vector2.h>
#include <Angles.h>

#include <vector>

class Actor
{
public:
    enum class State
    {
        EActive,
        EPaused,
        EDead
    };

    Actor(class Game* pGame);
    virtual ~Actor();

    // Update function called from Game
    void Update(float deltaTime);
    // Updates all components attached to the actor
    void UpdateComponents(float deltaTime);
    // Any actor-specific update code
    virtual void UpdateActor(float deltaTime);

    // Getters/Setters
    void SetState(State state);
    State GetState() const;

    void SetCenterPosition(const Vector2& pos);
    Vector2 GetCenterPosition() const;

    void SetScale(float scale);
    float GetScale() const;

    void SetRotation(const Radians& rot);
    Radians GetRotation() const;

    class Game* GetGame() const;

    // Add/remove components
    void AddComponent(class Component* pComponent);
    void RemoveComponent(class Component* pComponent);

private:
    State m_State = State::EActive;

    // Transform
    Vector2 m_CenterPosition;
    float m_Scale = 1.f;
    Radians m_Rotation;

    // Components
    std::vector<class Component*> m_Components;
    class Game* m_pGame = nullptr;
};
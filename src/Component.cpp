#include <Component.h>

Component::Component(Actor* pOwner, int updateOrder) : m_Owner(pOwner), m_UpdateOrder(updateOrder) {}
Component::~Component() {}

void Component::Update(float /*deltaTime*/) {}

int Component::GetUpdateOrder() const {
    return m_UpdateOrder;
}

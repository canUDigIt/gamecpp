#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
public:
    Component(class Actor* owner, int updateOrder = 100);
    virtual ~Component();

    virtual void Update(float deltaTime);
    int GetUpdateOrder() const;

protected:
    class Actor* m_Owner;
    int m_UpdateOrder;
};

#endif

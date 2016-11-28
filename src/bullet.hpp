#pragma once

#include "gameObject.hpp"

const int BULLET_HP = 1;
const Box2D BULLET_BOX = Box2D(Point2D(0, 0),Point2D(1, 1));

class Bullet : public GameObject
{
public:
  using TOnUpdateHandler = std::function<void()>;
  
  Bullet()
    : GameObject(BULLET_BOX, BULLET_HP)
  {}

  Bullet(Point2D p)
    : GameObject((BULLET_BOX + p), BULLET_HP)
  {}

  // Конструктор копирования.
  Bullet(Bullet const & obj)
    : GameObject(obj), m_updateHandler(obj.m_updateHandler)
  {}
    
  Bullet(Box2D const & obj)
    : GameObject(obj, BULLET_HP)
  {}
  
  // Конструктор перемещения
  Bullet(Bullet && obj)
  {
    std::swap(HealthPoints(), obj.HealthPoints());
    std::swap(Box(), obj.Box());
    std::swap(m_updateHandler, obj.m_updateHandler);
  }
  
  //Оператор перемещения
  Bullet & operator = (Bullet && obj)
  {
    if (this == &obj) return *this;
    std::swap(HealthPoints(), obj.HealthPoints());
    std::swap(Box(), obj.Box());
    std::swap(m_updateHandler, obj.m_updateHandler);
    return *this;
  }
  
  // Оператор логического равенства.
  bool operator == (Bullet const & obj) const
  {
    return ((HealthPoints() == obj.HealthPoints()) && (Box() == obj.Box()));
  }
  
  // Оператор присваивания.
  Bullet & operator = (Bullet const & obj)
  {
    if (this == &obj) return *this;
    HealthPoints() = obj.HealthPoints();
    Box() = obj.Box();
    m_updateHandler = obj.m_updateHandler;
    return *this;
  }

  // Оператор логического неравенства.
  bool operator != (Bullet const & obj) const
  {
    return !operator==(obj);
  }
  
  void SetUpdateHandler(TOnUpdateHandler const & handler)
  {
    m_updateHandler = handler;
  }

  void Update()
  {
    GameEntity::Update();
    
    if (m_updateHandler != nullptr)
      m_updateHandler();
  };
  friend std::ostream & operator << (std::ostream & os, Bullet const & obj)
  {
    os << "Bullet HP: " << obj.HealthPoints() << " Bullet box: " << obj.Box();
    return os;
  }
private:
  TOnUpdateHandler m_updateHandler;
};

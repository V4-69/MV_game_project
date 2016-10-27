#pragma once

#include "gameObject.hpp"

const int BULLET_HP = 1;
const Box2D BULLET_BOX = Box2D(Point2D(0, 0),Point2D(1, 1));

class Bullet : public GameObject
{
public:
  Bullet()
    : GameObject(BULLET_BOX, BULLET_HP)
  {}

  Bullet(Point2D p)
    : GameObject((BULLET_BOX + p), BULLET_HP)
  {}

  // Конструктор копирования.
  Bullet(Bullet const & obj)
    : GameObject(obj)
  {}
    
  Bullet(Box2D const & obj)
    : GameObject(obj, BULLET_HP)
  {}
  
  // Конструктор перемещения
  Bullet(Bullet && obj)
  {
    std::swap(HealthPoints(), obj.HealthPoints());
    std::swap(Box(), obj.Box());
  }
  
  //Оператор перемещения
  Bullet & operator = (Bullet && obj)
  {
    if (this == &obj) return *this;
    std::swap(HealthPoints(), obj.HealthPoints());
    std::swap(Box(), obj.Box());
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
    return *this;
  }

  // Оператор логического неравенства.
  bool operator != (Bullet const & obj) const
  {
    return !operator==(obj);
  }

  void Update()
  {
    GameEntity::Update();
    // код для bullet
  };
  friend std::ostream & operator << (std::ostream & os, Bullet const & obj)
  {
    os << "Bullet HP: " << obj.HealthPoints() << " Bullet box: " << obj.Box();
    return os;
  }
};

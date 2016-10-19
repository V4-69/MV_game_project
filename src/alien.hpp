#pragma once

#include "gameEntity.hpp"
#include "gameObject.hpp"
#include "bullet.hpp"
#include <ostream>

const int DEFAULT_ALIEN_HP = 3;
const Box2D DEFAULT_ALIEN_BOX = Box2D(Point2D(0, 0),Point2D(1, 1));

class Alien: public GameObject
{
public:
  // Конструктор по дефолту
  Alien()
    : GameObject(DEFAULT_ALIEN_BOX, DEFAULT_ALIEN_HP)
  {}
  
  // Копирования
  Alien(Alien const & obj)
    : GameObject(obj)
  {}

  Alien(int healthpoints)
    : GameObject(DEFAULT_ALIEN_BOX, healthpoints)
  {}

  Alien(Box2D box, int healthpoints)
    : GameObject(box, healthpoints)
  {}

  Alien(Box2D box)
    : GameObject(box, DEFAULT_ALIEN_HP)
  {}
  
  // Конструктор перемещения
  Alien(Alien && obj)
  {
    std::swap(HealthPoints(), obj.HealthPoints());
    std::swap(Box(), obj.Box());
  }
  
  // Оператор перемещения
  Alien & operator = (Alien && obj)
  {
    if (this == &obj) return *this;
    std::swap(HealthPoints(), obj.HealthPoints());
    std::swap(Box(), obj.Box());
    return *this;
  }
  
  // Оператор логического равенства.
  bool operator == (Alien const & obj) const
  {
    return ((HealthPoints() == obj.HealthPoints()) && (Box() == obj.Box()));
  }
  
  // Оператор присваивания.
  Alien & operator = (Alien const & obj)
  {
    if (this == &obj) return *this;
    HealthPoints() = obj.HealthPoints();
    Box() = obj.Box();
    return *this;
  }

  // Оператор логического неравенства.
  bool operator != (Alien const & obj) const
  {
    return !operator==(obj);
  }

  void Update()
  {
    GameEntity::Update();
    // код для Alien
  };
  
  Bullet makeShot()
  {
    return Bullet( Point2D(Box().BoxCenter().x(), Box().boxMin().y()) );
  }

};

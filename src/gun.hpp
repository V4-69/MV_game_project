#pragma once

#include "gameEntity.hpp"
#include "gameObject.hpp"
#include "bullet.hpp"

const int DEFAULT_GUN_HP = 3;
const Box2D DEFAULT_GUN_BOX = Box2D(Point2D(0, 0), Point2D(1, 1));

class Gun: public GameObject
{
public:

  //Конструктор по дефолту
  Gun()
    : GameObject(DEFAULT_GUN_BOX, DEFAULT_GUN_HP)
  {}

  //Копирования
  Gun(Gun const & obj)
    : GameObject(obj)
  {}

  Gun(int healthpoints)
    : GameObject(DEFAULT_GUN_BOX, healthpoints)
  {}

  Gun(Box2D const & box, int healthpoints)
    : GameObject(box, healthpoints)
  {}

  Gun(Box2D const & box)
    : GameObject(box, DEFAULT_GUN_HP)
  {}
  
  // Конструктор перемещения
  Gun(Gun && obj)
  {
    std::swap(HealthPoints(), obj.HealthPoints());
    std::swap(Box(), obj.Box());
  }
  
  //Оператор перемещения
  Gun & operator = (Gun && obj)
  {
    if (this == &obj) return *this;
    std::swap(HealthPoints(), obj.HealthPoints());
    std::swap(Box(), obj.Box());
    return *this;
  }
  
  // Оператор логического равенства.
  bool operator == (Gun const & obj) const
  {
    return ((HealthPoints() == obj.HealthPoints()) && (Box() == obj.Box()));
  }
  
  // Оператор присваивания.
  Gun & operator = (Gun const & obj)
  {
    if (this == &obj) return *this;
    HealthPoints() = obj.HealthPoints();
    Box() = obj.Box();
    return *this;
  }

  // Оператор логического неравенства.
  bool operator != (Gun const & obj) const
  {
    return !operator==(obj);
  }

  void Update()
  {
    GameEntity::Update();
    // код для gun
  };
  
  Bullet makeShot()
  {
    return Bullet( Point2D( Box().BoxCenter().x(), Box().boxMax().y() ) );
  }
  
};
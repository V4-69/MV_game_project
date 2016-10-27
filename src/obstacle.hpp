#pragma once

#include "gameObject.hpp"
#include <ostream>

#define DEFAULT_OBSTACLE_HP 3
#define DEFAULT_OBSTACLE_BOX Box2D(Point2D(0,0),Point2D(1,1))

class Obstacle: public GameObject
{
public:
  // Конструктор по дефолту
  Obstacle()
    : GameObject(DEFAULT_OBSTACLE_BOX, DEFAULT_OBSTACLE_HP)
  {}
  
  // Копирования
  Obstacle(Obstacle const & obj)
    : GameObject(obj.Box(), obj.HealthPoints())
  {}

  Obstacle(int healthpoints)
    : GameObject(DEFAULT_OBSTACLE_BOX, healthpoints)
  {}

  Obstacle(Box2D box, int healthpoints)
    : GameObject(box, healthpoints)
  {}

  Obstacle(Box2D box)
    : GameObject(box, DEFAULT_OBSTACLE_HP)
  {}
  
  // Конструктор перемещения
  Obstacle(Obstacle && obj)
  {
    std::swap(HealthPoints(), obj.HealthPoints());
    std::swap(Box(), obj.Box());
  }
  
  // Оператор перемещения
  Obstacle & operator = (Obstacle && obj)
  {
    if (this == &obj) return *this;
    std::swap(HealthPoints(), obj.HealthPoints());
    std::swap(Box(), obj.Box());
    return *this;
  }
  
  // Оператор логического равенства.
  bool operator == (Obstacle const & obj) const
  {
    return ((HealthPoints() == obj.HealthPoints()) && (Box() == obj.Box()));
  }
  
  // Оператор присваивания.
  Obstacle & operator = (Obstacle const & obj)
  {
    if (this == &obj) return *this;
    HealthPoints() = obj.HealthPoints();
    Box() = obj.Box();
    return *this;
  }

  // Оператор логического неравенства.
  bool operator != (Obstacle const & obj) const
  {
    return !operator==(obj);
  }

  void Update()
  {
    GameEntity::Update();
    // код для Obstacle
  };

  friend std::ostream & operator << (std::ostream & os, Obstacle const & obj)
  {
    os << "Obstacle HP: " << obj.HealthPoints() << " Obstacle box: " << obj.Box();
    return os;
  }
};

#pragma once

#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>
#include "box2d.hpp"
#include "gameEntity.hpp"

#define DEFAULT_SPACE_BOX Box2D(Point2D(0,0),Point2D(1,1))

class Space:public GameEntity
{
public:
  // Разрешаем конструирование по умолчанию.
  Space()
    : GameEntity(DEFAULT_SPACE_BOX)
  {}
  // Конструктор копирования.
  Space(Space const & obj)
    : GameEntity(obj)
  {}
  
  Space(Box2D const & obj)
    : GameEntity(obj)
  {}
   
  // Конструктор перемещения
  Space(Space && obj)
  {
    std::swap(Box(), obj.Box());
  }
  
  //Оператор перемещения
  Space & operator = (Space && obj)
  {
    if (this == &obj) return *this;
    std::swap(Box(), obj.Box());
    return *this;
  }
  
  // Оператор логического равенства.
  bool operator == (Space const & obj) const
  {
    return (Box() == obj.Box());
  }

  // Оператор присваивания.
  Space & operator = (Space const & obj)
  {
    if (this == &obj) return *this;
    Box() = obj.Box();
    return *this;
  }

  // Оператор логического неравенства.
  bool operator != (Space const & obj) const
  {
    return !operator==(obj);
  }
    
  void Update()
  {
    GameEntity::Update();
    // код для Space
  };

};

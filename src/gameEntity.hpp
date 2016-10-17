#pragma once

#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>
#include "box2d.hpp"

class GameEntity
{
public:
  // Разрешаем конструирование по умолчанию.
  GameEntity() = default;

  // Конструктор копирования.
  GameEntity(GameEntity const & obj)
    : m_box(obj.m_box)
  {}

  // Конструктор с параметрами.
  GameEntity(Box2D box)
    : m_box(box)
  {}
  
  // Конструктор перемещения
  GameEntity(GameEntity && obj)
  {
    std::swap(m_box, obj.m_box);
  }
  
  //Оператор перемещения
  GameEntity & operator = (GameEntity && obj)
  {
    if (this == &obj) return *this;
    std::swap(m_box, obj.m_box);
    return *this;
  }
  
  // Оператор логического равенства.
  bool operator == (GameEntity const & obj) const
  {
    return (m_box == obj.m_box);
  }

  Box2D & Box() { return m_box; }

  Box2D const & Box() const { return m_box; }

  // Конструктор со списком инициализации.
  GameEntity(std::initializer_list<Box2D> const & lst)
  {
    Box2D * vals[] = { &m_box };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
  }
  
  // Виртуальный деструктор
  virtual ~GameEntity(){};
  
  // Оператор присваивания.
  GameEntity & operator = (GameEntity const & obj)
  {
    if (this == &obj) return *this;
    m_box = obj.m_box;
    return *this;
  }

  // Оператор логического неравенства.
  bool operator != (GameEntity const & obj) const
  {
    return !operator==(obj);
  }

  // Переопределение оператора [].
  Box2D operator [] (unsigned int index) const
  {
    if (index >= 1) return Box2D();
    return m_box;
  }
  
  void Update(){};
private:

  Box2D m_box;
};
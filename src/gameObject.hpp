#pragma once

#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>
#include "box2d.hpp"
#include "gameEntity.hpp"

class GameObject: public GameEntity
{
public:
  // Разрешаем конструирование по умолчанию.
  GameObject() = default;

  // Конструктор копирования.
  GameObject(GameObject const & obj)
    : GameEntity(obj), m_healthPoints(obj.m_healthPoints)
  {}

  // Конструктор с параметрами.
  GameObject(int healthPoints)
    : GameEntity(), m_healthPoints(healthPoints)
  {
    ObjectCorrect();
  }
  
  GameObject(Box2D const & obj, int healthPoints)
    : GameEntity(obj), m_healthPoints(healthPoints)
  {
    ObjectCorrect();
  }
  
  GameObject(Box2D const & obj)
    : GameEntity(obj), m_healthPoints(0)
  {}
  
  // Конструктор перемещения
  GameObject(GameObject && obj)
  {
    std::swap(m_healthPoints, obj.m_healthPoints);
    std::swap(Box(), obj.Box());
  }
  
  virtual ~GameObject(){};
  //Оператор перемещения
  GameObject & operator = (GameObject && obj)
  {
    if (this == &obj) return *this;
    std::swap(m_healthPoints, obj.m_healthPoints);
    std::swap(Box(), obj.Box());
    return *this;
  }
  
  // Оператор логического равенства.
  bool operator == (GameObject const & obj) const
  {
    return ((m_healthPoints == obj.m_healthPoints) && (Box() == obj.Box()));
  }

  int & HealthPoints() { return m_healthPoints; }

  int const & HealthPoints() const { return m_healthPoints; }

  // Оператор присваивания.
  GameObject & operator = (GameObject const & obj)
  {
    if (this == &obj) return *this;
    m_healthPoints = obj.m_healthPoints;
    Box() = obj.Box();
    return *this;
  }

  // Оператор логического неравенства.
  bool operator != (GameObject const & obj) const
  {
    return !operator==(obj);
  }
  
  void ChangeHP(int damage)
  {
    if(m_healthPoints > damage) 
      m_healthPoints -= damage;
    else 
      m_healthPoints = 0;
  }

  void ObjectMove()
  {
    // Движение
  }
  
  void Update(){}
  
private:
  void ObjectCorrect()
  {
    try
    {
      if (m_healthPoints < 0) throw IncorrectDataExceptions("Object have HP < 0");
    }
    catch (IncorrectDataExceptions const & ex)
    {
      std::cout << ex.messageException() << std::endl;
      std::cerr << ex.messageException() << std::endl;
      m_healthPoints = 0;
    }
  }

  int m_healthPoints = 0;
};

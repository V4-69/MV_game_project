#pragma once

#include "incorrectDataExceptions.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

float const kEps = 1e-5;

class Point2D
{
public:
  // Разрешаем конструирование по умолчанию.
  Point2D() = default;

  // Конструктор копирования.
  Point2D(Point2D const & obj)
    : m_x(obj.m_x), m_y(obj.m_y)
  {}

  // Конструктор с параметрами.
  Point2D(float x, float y)
    : m_x(x), m_y(y)
  {}
  
  // Конструктор перемещения
  Point2D(Point2D && obj)
  {
    std::swap(m_x, obj.m_x);
    std::swap(m_y, obj.m_y);
  }
  
  //Оператор перемещения
  Point2D & operator = (Point2D && obj)
  {
    if (this == &obj) return *this;
    std::swap(m_x, obj.m_x);
    std::swap(m_y, obj.m_y);
    return *this;
  }
  
  // Оператор логического равенства.
  bool operator == (Point2D const & obj) const
  {
    return EqualWithEps(m_x, obj.m_x) && EqualWithEps(m_y, obj.m_y);
  }

  float & x() { return m_x; }
  float & y() { return m_y; }

  float const & x() const { return m_x; }
  float const & y() const { return m_y; }

  // Конструктор со списком инициализации.
  Point2D(std::initializer_list<float> const & lst)
  {
    float * vals[] = { &m_x, &m_y };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
  }

  // Оператор присваивания.
  Point2D & operator = (Point2D const & obj)
  {
    if (this == &obj) return *this;
    m_x = obj.m_x;
    m_y = obj.m_y;
    return *this;
  }

  // Оператор логического неравенства.
  bool operator != (Point2D const & obj) const
  {
    return !operator==(obj);
  }

  // Оператор меньше.
  bool operator < (Point2D const & obj) const
  {
    if (m_x != obj.m_x) return m_x < obj.m_x;
    return m_y < obj.m_y;
  }

  // Сложение.
  Point2D operator + (Point2D const & obj) const
  {
    return { m_x + obj.m_x, m_y + obj.m_y };
  }

  // Вычитание.
  Point2D operator - (Point2D const & obj) const
  {
    return { m_x - obj.m_x, m_y - obj.m_y };
  }

  // Математическое отрицание.
  Point2D operator - () const
  {
    return { -m_x, -m_y };
  }

  // Умножение на число.
  Point2D operator * (float scale) const
  {
    return { m_x * scale, m_y * scale };
  }

  // Деление на число.
  Point2D operator / (float scale) const
  {
    //TODO: обработать деление на 0.
    return { m_x / scale, m_y / scale };
  }

  Point2D & operator += (Point2D const & obj)
  {
    m_x += obj.m_x;
    m_y += obj.m_y;
    return *this;
  }

  Point2D & operator -= (Point2D const & obj)
  {
    m_x -= obj.m_x;
    m_y -= obj.m_y;
    return *this;
  }

  Point2D & operator *= (float scale)
  {
    m_x *= scale;
    m_y *= scale;
    return *this;
  }

  Point2D & operator /= (float scale)
  {
    try
    {
      if (EqualWithEps (scale, 0.0f)) throw IncorrectDataExceptions("division by 0");
      m_x /= scale;
      m_y /= scale;
    }
    catch (IncorrectDataExceptions const & ex)
    {
      std::cerr << ex.what() << std::endl;
      throw;
    }

    return *this;
  }

  // Переопределение оператора [].
  float operator [] (unsigned int index) const
  {
    if (index >= 2) return 0.0f;
    return index == 0 ? m_x : m_y;
  }

  // Добавим внутреннюю сущность для вычисления хэша.
  struct Hash
  {
    size_t operator()(Point2D const & p) const
    {
      auto hasher = std::hash<float>();
      return (hasher(p.x()) ^ (hasher(p.y()) << 1));
    }
  };
  
  void Normalize()
  {
    float abs = sqrt(m_x * m_x + m_y * m_y);
    if (EqualWithEps (abs, 0.0f)) throw IncorrectDataExceptions("0 length of vector");
    m_x = m_x / abs;
    m_y = m_y / abs;
  }
  
  bool EqualWithEpsX(float v) const
  {
    return EqualWithEps(m_x, v);
  }
  
  bool EqualWithEpsY(float v) const
  {
    return EqualWithEps(m_y, v);
  }
  
private:
  bool EqualWithEps(float v1, float v2) const
  {
    return fabs(v1 - v2) < kEps;
  }

  float m_x = 0.0f, m_y = 0.0f;
};

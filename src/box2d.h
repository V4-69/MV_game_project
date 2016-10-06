#pragma once

#include "point2d.hpp"
#include "nvect.hpp"
#include "ray2d.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

class Box2D
{
public:
  // Разрешаем конструирование по умолчанию.
  Box2D() = default;

  // Конструктор копирования.
  Box2D(Box2D const & obj)
    : m_min(obj.m_min), m_max(obj.m_max)
  {
      box_correct();
  }

  // Конструктор с параметрами.
  Box2D(Point2D min, Point2D max)
    : m_min(min), m_max(max)
  {}

  // Оператор логического равенства.
  bool operator == (Box2D const & obj) const
  {
    return (m_min == obj.m_min) && (m_max == obj.m_max);
  }

  Point2D & min() { return m_min; }
  Point2D & max() { return m_max; }

  Point2D const & min() const { return m_min; }
  Point2D const & max() const { return m_max; }

  // Конструктор со списком инициализации.
  Box2D(std::initializer_list<Point2D> const & lst)
  {
    Point2D * vals[] = { &m_min, &m_max };
    int const count = sizeof(vals) / sizeof(vals[0]);
    auto it = lst.begin();
    for (int i = 0; i < count && it != lst.end(); i++, ++it)
      *vals[i] = *it;
    box_correct();
  }

  // Оператор присваивания.
  Box2D & operator = (Box2D const & obj)
  {
    if (this == &obj) return *this;
    m_min = obj.m_min;
    m_max = obj.m_max;
    return *this;
  }

  // Оператор логического неравенства.
  bool operator != (Box2D const & obj) const
  {
    return !operator==(obj);
  }

  // Переопределение оператора [].
  Point2D operator [] (unsigned int index) const
  {
    if (index >= 2) return Point2D(0.0f,0.0f);
    return index == 0 ? m_min : m_max;
  }
  bool boxes_intersect(const Box2D &obj)
  {
    if (m_max.x() < obj.min().x()) return false; // a is left of b
    if (m_min.x() > obj.max().x()) return false; // a is right of b
    if (m_max.y() < obj.min().y()) return false; // a is above b
    if (m_min.y() > obj.max().y()) return false; // a is below b
    return true;
  }
  bool inside(const Point2D &obj)
  {
    if ((obj.x() <= m_max.x()) && (obj.y() <= m_max.y()) && (obj.x() >= m_min.x()) && (obj.y() >= m_min.y()))
    {
      return true;
    }
      return false;
  }

  bool box_ray_intersect(const Ray2D &obj)
  {
    if (inside(obj.origin()))
    {
      return true;
    }
    else
    {
      float k_ray = obj.direction().y()/obj.direction().x();
      float b_ray = obj.origin().y() - k_ray*obj.origin().x();
      float k_dia_1 = (m_max.y()- m_min.y()) / (m_max.x()- m_min.x());
      float k_dia_2 = -k_dia_1;
      float b_dia_1 = m_max.y() - k_dia_1*m_max.x();
      float b_dia_2 = m_max.y() - k_dia_2*m_min.x();
      float x = - (b_ray - b_dia_1) / (k_ray - k_dia_1);
      float y = k_ray * x + b_ray;
      if (!inside(Point2D(x,y)))    {
        x = - (b_ray - b_dia_2) / (k_ray - k_dia_2);
        y = k_ray * x + b_ray;
      }
      if (!inside(Point2D(x,y)))    {
        return false;
      }
      if (obj.direction().x() != 0)
      {
        if ((x - obj.origin().x())*obj.direction().x() > 0)
          return true;
      }
      else
      {
        if ((y - obj.origin().y())*obj.direction().y() > 0)
          return true;
      }
      return false;
    }
  }

private:

  Point2D m_min = Point2D(0.0f,0.0f), m_max = Point2D(0.0f,0.0f);
  void box_correct()
  {
      if (m_max < m_min)
      {
          Point2D x;
          Point2D y;
          if (m_max.x() < m_min.x())
          {
              x = {m_max.x(),m_min.x()};
          }
          else
          {
              x = {m_min.x(),m_max.x()};
          }
          if (m_max.y() < m_min.y())
          {
              y = {m_max.y(),m_min.y()};
          }
          else
          {
              y = {m_min.y(),m_max.y()};
          }
          m_min = {x[0],y[0]};
          m_max = {x[1],y[1]};
      }
  }

};

std::ostream & operator << (std::ostream & os, Box2D const & obj)
{
  os << "Box2D {" << obj.min() << ", " << obj.max() << "}";
  return os;
}
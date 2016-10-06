#pragma once
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>
#include "point2d.hpp"
#include "nvect.hpp"


class Ray2D
{
public:

    Ray2D() = default;

    Ray2D(Ray2D const & obj)
        : m_origin(obj.m_origin), m_direction(obj.m_direction)
    {}

    Ray2D(Point2D pt,Vect2D vc)
    {
        m_origin=pt;
        m_direction=vc;
    }

    Ray2D(float x1,float y1,float x2,float y2)
    {
        Point2D pt(x1,y1);
        Vect2D vc(x2,y2);
        m_origin=pt;
        m_direction=vc;
    }
    // Оператор логического равенства.
    bool operator == (Ray2D const & obj) const
    {
        return ((m_origin==obj.m_origin) && (m_direction==obj.m_direction));
    }

    bool operator != (Ray2D const & obj) const
    {
      return !operator==(obj);
    }

    Ray2D & operator = (Ray2D const & obj)
    {
        if (this == &obj) return *this;
        m_origin = obj.m_origin;
        m_direction = obj.m_direction;
        return *this;
    }

    Point2D const & origin () const
    {
        return m_origin;
    }

    Vect2D const & direction () const
    {
        return m_direction;
    }

private:

    Point2D m_origin;

    Vect2D m_direction;
};

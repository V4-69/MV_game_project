#pragma once
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

class Vect2D
{
public:
    Vect2D()=default;

    Vect2D(Vect2D const & obj)
        : m_dx(obj.m_dx), m_dy(obj.m_dy)
    {}

    Vect2D(float x,float y)
    {
        float abs=sqrt(x*x+y*y);
        m_dx=x/abs;
        m_dy=y/abs;
    }

    bool operator == (Vect2D const & obj) const
    {
        return (EqualWithEps(m_dx,obj.m_dx)&&EqualWithEps(m_dy,obj.m_dy));
    }

    float & x()
    {
        return m_dx;
    }
    float & y()
    {
        return m_dy;
    }

    float const & x() const
    {
        return m_dx;
    }
    float const & y() const
    {
        return m_dy;
    }

    Vect2D & operator = (Vect2D const & obj)
    {
        if (this == &obj) return *this;
        m_dx=obj.m_dx;
        m_dy=obj.m_dy;
        return *this;
    }

private:

    bool EqualWithEps(float v1, float v2) const
    {
        return fabs(v1 - v2) < kEps;
    }

    float m_dx=1;
    float m_dy=0;

};

std::ostream & operator << (std::ostream & os, Vect2D const & obj)
{
    os << "Vect2D {" << obj.x() << ", " << obj.y() << "}";
    return os;
}

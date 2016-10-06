#include "gtest/gtest.h"
#include "point2d.hpp"
#include "Ray2D.hpp"
#include "nvect.hpp"
#include <sstream>
#include <unordered_set>

TEST(ray2d_test, test_construction)
{
  // Тест на создание объекта по умолчанию.
  Ray2D r1;
  Point2D p1;
  Vect2D v1;

  EXPECT_EQ(r1.origin(), p1);
  EXPECT_EQ(r1.direction(), v1);

  // Тест на создание объекта с параметрами.
  Ray2D r2(1,2,3,4);
  Point2D p2(1,2);
  Vect2D v2(0.6,0.8);
  EXPECT_EQ(r2.origin(),p2);
  EXPECT_EQ(r2.direction(), v2);

  //Тест инициализации по точе и вектору
  Vect2D v3(0,1);
  Point2D p3(2,3);
  Ray2D r3(p3,v3);
  EXPEXT_EQ(r3.origin(),p3);
  EXPECT_EQ(r3.direction(),v3);
  // Тест на создание копии объекта.
  Ray2D r3 = r2;
  EXPECT_EQ(r3, r2);
}

TEST(ray2d_test, test_equality)
{
  Ray2D r1(1.0f,2.0f,3.0f,4.0f);
  Ray2D r2(1.0f,2.0f,3.0f,4.0f);
  Ray2D r3(1.0f,2.0f,5.0f,8.0f);
  EXPECT_EQ(r1, r2);
  EXPECT_NE(r1, r3);
}

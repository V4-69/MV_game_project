#include "gtest/gtest.h"
#include "point2d.hpp"
#include "box2d.hpp"
#include "nvect.hpp"
#include "ray2d.hpp"
#include <sstream>
#include <unordered_set>

TEST(box2d_test, test_construction)
{
  // Тест на создание объекта по умолчанию.
  Box2D b1;
  Point2D p1;
  EXPECT_EQ(b1.min(), p1);
  EXPECT_EQ(b1.max(), p1);

  // Тест на создание объекта с параметрами.
  Point2D p2_1 = { 1.3f, 2.5f };
  Point2D p2_2 = { 2.0f, 3.5f };
  Box2D b2 = { p2_1, p2_2 };
  EXPECT_EQ(b2.min(), p2_1);
  EXPECT_EQ(b2.max(), p2_2);

  // Тест на создание копии объекта.
  Box2D b3 = b2;
  EXPECT_EQ(b3, b2);
}

TEST(box2d_test, test_initializer_list)
{
  Point2D p1 = { 1.3f, 2.5f };
  Point2D p2 = { 2.0f, 3.5f };
  Point2D p3 = { 3.3f, 4.5f };

  Box2D b1 = { p1, p2, p3 };
  EXPECT_EQ(b1.min(), p1);
  EXPECT_EQ(b1.max(), p2);

  Box2D b2 = { p1 };
  Point2D p4;
  EXPECT_EQ(b2.min(), p1);
  EXPECT_EQ(b2.max(), p4);
}

TEST(box2d_test, test_assignment)
{
  Box2D b1;
  Point2D p1 = { 1.3f, 2.5f };
  Point2D p2 = { 2.0f, 3.5f };
  b1 = { p1, p2 };
  EXPECT_EQ(b1, Box2D(p1, p2));
}

TEST(box2d_test, test_equality)
{
  Point2D p1 = { 1.2f, 2.4f };
  Point2D p2 = { 1.24f, 2.44f };
  Point2D p3 = { 1.3f, 2.4f };
  Box2D b1 = {p1,p2};
  Box2D b2 = {p1,p2};
  Box2D b3 = {p1,p3};
  EXPECT_EQ(b1, b2);
  EXPECT_NE(b1, b3);
}

TEST(box2d_test, test_square_brackets)
{
  Point2D p1 = { 1.2f, 2.4f };
  Point2D p2 = { 1.3f, 2.4f };
  Point2D p3;
  Box2D b1 = {p1,p2};
  EXPECT_EQ(b1[0], p1);
  EXPECT_EQ(b1[1], p2);
  EXPECT_EQ(b1[2], p3);
}

TEST(box2d_test, test_output)
{
  std::stringstream s;
  Point2D p1 = { 1.2f, 2.4f };
  Point2D p2 = { 1.3f, 2.4f };
  s << Box2D(p1, p2);
  EXPECT_EQ(s.str(), "Box2D {Point2D {1.2, 2.4}, Point2D {1.3, 2.4}}");
}
TEST(box2d_test, test_boxes_intersect)
{
  Point2D p1 = { 1.0f, 2.0f };
  Point2D p2 = { 2.0f, 3.0f };
  Point2D p3 = { 1.5f, 2.5f };
  Point2D p4 = { 2.5f, 3.5f };
  Point2D p5 = { 3.5f, 2.5f };
  Point2D p6 = { 4.5f, 3.5f };
  Box2D b1 = {p1,p2};
  Box2D b2 = {p3,p4};
  Box2D b3 = {p5,p6};
  
  bool f1 = true;
  bool f2 = false;
  EXPECT_EQ(b1.boxes_intersect(b2), f1);
  EXPECT_EQ(b1.boxes_intersect(b3), f2);
}
TEST(box2d_test, test_box_ray_intersect)
{
  Point2D p1 = { 0.0f, 2.0f };
  Point2D p2 = { 1.0f, 3.0f };
  Point2D p3 = { 0.0f, 2.0f };
  Point2D p4 = { 4.0f, 3.0f };
  Vect2D vect(1.0f,1.0f);
  Box2D b1 = {p1,p2};
  Box2D b2 = {p3,p4};
  Ray2D ray(Point2D(0.0f,0.0f),vect);
  bool f1 = false;
  bool f2 = true;
  EXPECT_EQ(b1.box_ray_intersect(ray), f1);
  EXPECT_EQ(b2.box_ray_intersect(ray), f2);
}

#include "gtest/gtest.h"
#include "ray2d.hpp"
#include <sstream>
#include <unordered_set>

TEST(ray2d_test, test_construction)
{

  Ray2D r1;
  Point2D p1;
  Point2D v1 = {1.0f, 0.0f};

  EXPECT_EQ(r1.origin(), p1);
  EXPECT_EQ(r1.direction(), v1);

  Ray2D r2(1.0f, 2.0f, 3.0f, 4.0f);
  Point2D p2(1.0f, 2.0f);
  Point2D v2(0.6f, 0.8f);
  EXPECT_EQ(r2.origin(), p2);
  EXPECT_EQ(r2.direction(), v2);

  Point2D v3(0.0f, 1.0f);
  Point2D p3(2.0f, 3.0f);
  Ray2D r3(p3, v3);
  EXPECT_EQ(r3.origin(), p3);
  EXPECT_EQ(r3.direction(), v3);
  
  Ray2D r4 = r2;
  EXPECT_EQ(r4, r2);
}
TEST(ray2d_test, test_initializer_list)
{
  Point2D p1 = { 1.3f, 2.5f };
  Point2D p2 = { 1.0f, 0.0f };
  Point2D p3 = { 3.3f, 4.5f };

  Ray2D r1 = { p1, p2, p3 };
  EXPECT_EQ(r1.origin(), p1);
  EXPECT_EQ(r1.direction(), p2);

  Ray2D r2 = { p1 };
  Point2D p4 = {1.0f, 0.0f};
  EXPECT_EQ(r2.origin(), p1);
  EXPECT_EQ(r2.direction(), p4);
}
TEST(ray2d_test, test_equality)
{
  Ray2D r1(1.0f,2.0f,3.0f,4.0f);
  Ray2D r2(1.0f,2.0f,3.0f,4.0f);
  Ray2D r3(1.0f,2.0f,5.0f,8.0f);
  EXPECT_EQ(r1, r2);
  EXPECT_NE(r1, r3);
}
TEST(ray2d_test, test_square_brackets)
{
  Point2D p1 = { 1.2f, 2.4f };
  Point2D p2 = { 1.0f, 0.0f };
  Point2D p3;
  Ray2D r1 = {p1,p2};
  EXPECT_EQ(r1[0], p1);
  EXPECT_EQ(r1[1], p2);
  EXPECT_EQ(r1[2], p3);
}
TEST(ray2d_test, test_move)
{
  Point2D p1 = { 0.0f, 2.0f };
  Point2D p2 = { 0.0f, 1.0f };
  Point2D p3 = { 0.0f, 2.0f };
  Point2D p4 = { 1.0f, 0.0f };
  Ray2D r1 = { p1, p2 };
  Ray2D r2 = { p3, p4 };
  // move constructor
  Ray2D r3 = std::move(r1);
  EXPECT_EQ(r1, Ray2D(Point2D { 0.0f, 0.0f }, Point2D { 1.0f, 0.0f }));
  EXPECT_EQ(r3, Ray2D(Point2D { 0.0f, 2.0f }, Point2D { 0.0f, 1.0f }));
  // move
  r1 = std::move(r2);
  EXPECT_EQ(r1, Ray2D(Point2D { 0.0f, 2.0f }, Point2D { 1.0f, 0.0f }));
  EXPECT_EQ(r2, Ray2D(Point2D { 0.0f, 0.0f }, Point2D { 1.0f, 0.0f }));
}

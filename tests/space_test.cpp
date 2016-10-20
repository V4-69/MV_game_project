#pragma once

#include "gtest/gtest.h"
#include "space.hpp"
#include <sstream>
#include <unordered_set>

TEST(space_test, test_construction)
{
  // Тест на создание объекта по умолчанию.
  Box2D b1 = DEFAULT_SPACE_BOX;
  Space gO1;
  EXPECT_EQ( gO1.Box(), b1 );

  // Тест на создание объекта с параметрами.
  Point2D p2_1 = { 1.3f, 2.5f };
  Point2D p2_2 = { 2.0f, 3.5f };
  Box2D b2 = { p2_1, p2_2 };
  Space gO2( b2 );
  EXPECT_EQ( gO2.Box(), b2 );

  // Тест на создание копии объекта.
  GameEntity gO4 = gO2;
  EXPECT_EQ( gO4, gO2 );
}

TEST(space_test, test_assignment)
{
  Box2D b1;
  Point2D p1 = { 1.3f, 2.5f };
  Point2D p2 = { 2.0f, 3.5f };
  b1 = { p1, p2 };
  Space gO1 = { b1 };
  EXPECT_EQ( gO1, Space( b1 ) );
}

TEST(space_test, test_equality)
{
  Point2D p1 = { 1.2f, 2.4f };
  Point2D p2 = { 1.24f, 2.44f };
  Point2D p3 = { 1.3f, 2.8f };
  Box2D b1 = { p1, p2 };
  Box2D b2 = { p1, p2 };
  Box2D b3 = { p1, p3 };
  Space gO1( b1 );
  Space gO2( b2 );
  Space gO3( b3 );
  EXPECT_EQ( gO1, gO2 );
  EXPECT_NE( gO1, gO3 );
}

TEST(space_test, test_move)
{
  Point2D p1 = { 0.0f, 2.0f };
  Point2D p2 = { 1.0f, 3.0f };
  Point2D p3 = { 0.0f, 2.0f };
  Point2D p4 = { 4.0f, 3.0f };
  Box2D b1 = { p1, p2 };
  Box2D b2 = { p3, p4 };
  Box2D b00;
  Box2D b10 = b1;
  Box2D b20 = b2;
  Space gO1( b1 );
  Space gO2( b2 );
  Space gO00( b00 );
  Space gO10( b10 );
  Space gO20( b20 );
  // move constructor
  Space gO3 = std::move(gO1);
  EXPECT_EQ( gO1, gO00 );
  EXPECT_EQ( gO3, gO10 );
  // move
  gO1 = std::move(gO2);
  EXPECT_EQ( gO1, gO20 );
  EXPECT_EQ( gO2, gO00 );
}

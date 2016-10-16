#pragma once

#include "gtest/gtest.h"
#include "gameEntity.hpp"
#include <sstream>
#include <unordered_set>

TEST(gameEntity_test, test_construction)
{
  // Тест на создание объекта по умолчанию.
  Box2D b1;
  GameEntity gE1;
  EXPECT_EQ(gE1.Box(), b1);

  // Тест на создание объекта с параметрами.
  Point2D p2_1 = { 1.3f, 2.5f };
  Point2D p2_2 = { 2.0f, 3.5f };
  Box2D b2 = { p2_1, p2_2 };
  GameEntity gE2(b2);
  EXPECT_EQ(gE2.Box(), b2);

  // Тест на создание копии объекта.
  GameEntity gE3 = gE2;
  EXPECT_EQ(gE3, gE2);
}

TEST(gameEntity_test, test_assignment)
{
  Box2D b1;
  Point2D p1 = { 1.3f, 2.5f };
  Point2D p2 = { 2.0f, 3.5f };
  b1 = { p1, p2 };
  GameEntity gE1 = { b1 };
  EXPECT_EQ(gE1, GameEntity( b1 ));
}

TEST(gameEntity_test, test_equality)
{
  Point2D p1 = { 1.2f, 2.4f };
  Point2D p2 = { 1.24f, 2.44f };
  Point2D p3 = { 1.3f, 2.4f };
  Box2D b1 = {p1, p2};
  Box2D b2 = {p1, p2};
  Box2D b3 = {p1, p3};
  GameEntity gE1(b1);
  GameEntity gE2(b2);
  GameEntity gE3(b3);
  EXPECT_EQ(gE1, gE2);
  EXPECT_NE(gE1, gE3);
}

TEST(gameEntity_test, test_move)
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
  GameEntity gE1(b1);
  GameEntity gE2(b2);
  GameEntity gE00(b00);
  GameEntity gE10(b10);
  GameEntity gE20(b20);
  // move constructor
  GameEntity gE3 = std::move(gE1);
  EXPECT_EQ( gE1, gE00 );
  EXPECT_EQ( gE3, gE10 );
  // move
  gE1 = std::move(gE2);
  EXPECT_EQ( gE1, gE20 );
  EXPECT_EQ( gE2, gE00 );
}

#pragma once

#include "gtest/gtest.h"
#include "gameObject.hpp"
#include <sstream>
#include <unordered_set>

TEST(gameObject_test, test_construction)
{
  // Тест на создание объекта по умолчанию.
  Box2D b1;
  GameObject gO1;
  EXPECT_EQ( gO1.Box(), b1 );
  EXPECT_EQ( gO1.HealthPoints(), 0 );

  // Тест на создание объекта с параметрами.
  Point2D p2_1 = { 1.3f, 2.5f };
  Point2D p2_2 = { 2.0f, 3.5f };
  Box2D b2 = { p2_1, p2_2 };
  GameObject gO2( b2, 5 );
  EXPECT_EQ( gO2.Box(), b2 );
  EXPECT_EQ( gO2.HealthPoints(), 5 );
  
  // Тест на создание объекта с параметрами.
  GameObject gO3(b2);
  EXPECT_EQ( gO3.Box(), b2 );
  EXPECT_EQ( gO3.HealthPoints(), 0 );

  // Тест на создание копии объекта.
  GameEntity gO4 = gO2;
  EXPECT_EQ( gO4, gO2 );
}

TEST(gameObject_test, test_assignment)
{
  Box2D b1;
  Point2D p1 = { 1.3f, 2.5f };
  Point2D p2 = { 2.0f, 3.5f };
  b1 = { p1, p2 };
  GameObject gO1 = { b1 , 5 };
  EXPECT_EQ(gO1, GameObject( b1 , 5 ));
}

TEST(gameObject_test, test_equality)
{
  Point2D p1 = { 1.2f, 2.4f };
  Point2D p2 = { 1.24f, 2.44f };
  Point2D p3 = { 1.3f, 2.7f };
  Box2D b1 = { p1, p2 };
  Box2D b2 = { p1, p2 };
  Box2D b3 = { p1, p3 };
  GameObject gO1( b1, 1 );
  GameObject gO2( b2, 1 );
  GameObject gO3( b3, 2 );
  EXPECT_EQ( gO1, gO2 );
  EXPECT_NE( gO1, gO3 );
}

TEST(gameObject_test, test_move)
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
  GameObject gO1( b1, 2 );
  GameObject gO2( b2, 3 );
  GameObject gO00( b00 );
  GameObject gO10( b10, 2 );
  GameObject gO20( b20, 3 );
  // move constructor
  GameObject gO3 = std::move(gO1);
  EXPECT_EQ( gO1, gO00 );
  EXPECT_EQ( gO3, gO10 );
  // move
  gO1 = std::move(gO2);
  EXPECT_EQ( gO1, gO20 );
  EXPECT_EQ( gO2, gO00 );
}

TEST(gameObject_test, test_exception)
{
  // Тест на исключения.
  EXPECT_THROW(GameObject gO1(-3), IncorrectDataExceptions);

  Point2D p2_1 = { 1.3f, 2.5f };
  Point2D p2_2 = { 2.0f, 3.5f };
  Box2D b2 = { p2_1, p2_2 };
  EXPECT_THROW(GameObject gO2( b2, -5 ), IncorrectDataExceptions);
}

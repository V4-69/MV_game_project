#pragma once

#include "gtest/gtest.h"
#include "gameEntity.hpp"
#include "factory.hpp"
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
  Point2D p3 = { 1.3f, 2.6f };
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

TEST(gameEntity_test, test_output)
{
  Point2D p2_1 = { 1.3f, 2.5f };
  Point2D p2_2 = { 2.0f, 3.5f };
  Box2D b2 = { p2_1, p2_2 };
  GameEntity gE2(b2);
  std::stringstream s;
  std::stringstream sOut;
  s << gE2;
  sOut << "GameEntity box: " << gE2.Box();
  EXPECT_EQ(s.str(), sOut.str());
}

TEST(gameEntity_test, test_logger)
{
  std::string create = "create";
  std::string emptyS = "[----------]";

  Point2D p1 = { 1.0f, 2.0f };
  Point2D p2 = { 2.0f, 3.0f };
  Point2D p3 = { 3.0f, 4.0f };
  Point2D p4 = { 4.0f, 5.0f };

  Box2D b1 = { p1, p2 };
  Box2D b2 = { p3, p4 };

  GameEntity gE1(b1);
  GameEntity gE2(b2);

  std::stringstream s;
  std::stringstream sOut;
  Logger::Log(gE1, s);
  sOut << emptyS << std::endl << gE1 << std::endl << emptyS << "\n\n";
  EXPECT_EQ(s.str(), sOut.str());

  std::stringstream s1;
  std::stringstream sOut1;
  Logger::Log(gE1, create, s1);
  sOut1 << emptyS << std::endl << create << std::endl << gE1 << std::endl << emptyS << "\n\n";
  EXPECT_EQ(s1.str(), sOut1.str());

  std::vector<GameEntity> v = { gE1, gE2 };
  std::stringstream s2;
  std::stringstream sOut2;
  Logger::Log(v, create, s2);
  sOut2 << emptyS << std::endl << create << std::endl << gE1 << std::endl << emptyS << "\n\n";
  sOut2 << emptyS << std::endl << create << std::endl << gE2 << std::endl << emptyS << "\n\n";
  EXPECT_EQ(s2.str(), sOut2.str());

  std::vector<GameEntity> v1 = { gE1, gE2 };
  std::stringstream s3;
  std::stringstream sOut3;
  Logger::Log(v1, s3);
  sOut3 << emptyS << std::endl << gE1 << std::endl << emptyS << "\n\n";
  sOut3 << emptyS << std::endl << gE2 << std::endl << emptyS << "\n\n";
  EXPECT_EQ(s3.str(), sOut3.str());
}

TEST(gameEntity_test, test_factory)
{
  Factory factory;
  Box2D b1;
  auto gE1 = factory.Create<GameEntity>();
  EXPECT_EQ(gE1->Box(), b1);

  Point2D p2_1 = { 1.3f, 2.5f };
  Point2D p2_2 = { 2.0f, 3.5f };
  Box2D b2 = { p2_1, p2_2 };
  auto gE2 = factory.Create<GameEntity>(b2);
  EXPECT_EQ(gE2->Box(), b2);
}
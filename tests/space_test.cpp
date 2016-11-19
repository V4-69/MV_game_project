#pragma once

#include "gtest/gtest.h"
#include "space.hpp"
#include "factory.hpp"
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

TEST(space_test, test_output)
{
  Point2D p2_1 = { 1.3f, 2.5f };
  Point2D p2_2 = { 2.0f, 3.5f };
  Box2D b1 = { p2_1, p2_2 };
  Space sp(b1);
  std::stringstream s;
  std::stringstream sOut;
  s << sp;
  sOut << "Space box: " << sp.Box();
  EXPECT_EQ(s.str(), sOut.str());
}

TEST(space_test, test_logger)
{
  std::string create = "create";
  std::string emptyS = "[----------]";

  Point2D p1 = { 1.0f, 2.0f };
  Point2D p2 = { 2.0f, 3.0f };
  Point2D p3 = { 3.0f, 4.0f };
  Point2D p4 = { 4.0f, 5.0f };

  Box2D b1 = { p1, p2 };
  Box2D b2 = { p3, p4 };

  Space sp1(b1);
  Space sp2(b2);

  std::stringstream s;
  std::stringstream sOut;
  Logger::Log(sp1, s);
  sOut << emptyS << std::endl << sp1 << std::endl << emptyS << "\n\n";
  EXPECT_EQ(s.str(), sOut.str());

  std::stringstream s1;
  std::stringstream sOut1;
  Logger::Log(sp1, create, s1);
  sOut1 << emptyS << std::endl << create << std::endl << sp1 << std::endl << emptyS << "\n\n";
  EXPECT_EQ(s1.str(), sOut1.str());

  std::vector<Space> v = { sp1, sp2 };
  std::stringstream s2;
  std::stringstream sOut2;
  Logger::Log(v, create, s2);
  sOut2 << emptyS << std::endl << create << std::endl << sp1 << std::endl << emptyS << "\n\n";
  sOut2 << emptyS << std::endl << create << std::endl << sp2 << std::endl << emptyS << "\n\n";
  EXPECT_EQ(s2.str(), sOut2.str());

  std::vector<Space> v1 = { sp1, sp2 };
  std::stringstream s3;
  std::stringstream sOut3;
  Logger::Log(v1, s3);
  sOut3 << emptyS << std::endl << sp1 << std::endl << emptyS << "\n\n";
  sOut3 << emptyS << std::endl << sp2 << std::endl << emptyS << "\n\n";
  EXPECT_EQ(s3.str(), sOut3.str());
}

TEST(space_test, test_factory)
{
  Factory factory;
  Box2D b1 = DEFAULT_SPACE_BOX;
  auto gO1 = factory.Create<Space>();
  EXPECT_EQ( gO1->Box(), b1 );

  Point2D p2_1 = { 1.3f, 2.5f };
  Point2D p2_2 = { 2.0f, 3.5f };
  Box2D b2 = { p2_1, p2_2 };
  auto gO2 = factory.Create<Space>(b2);
  EXPECT_EQ( gO2->Box(), b2 );
}
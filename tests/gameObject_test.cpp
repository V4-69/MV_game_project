#pragma once

#include "gtest/gtest.h"
#include "gameObject.hpp"
#include "factory.hpp"
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

TEST(gameObject_test, test_output)
{
  Point2D p2_1 = { 1.3f, 2.5f };
  Point2D p2_2 = { 2.0f, 3.5f };
  Box2D b = { p2_1, p2_2 };
  GameObject a(b, 5);
  std::stringstream s;
  std::stringstream sOut;
  s << a;
  sOut << "GameObject HP: " << a.HealthPoints() << " GameObject box: " << a.Box();
  EXPECT_EQ(s.str(), sOut.str());
}

TEST(gameObject_test, test_logger)
{
  std::string create = "create";
  std::string emptyS = "[----------]";

  GameObject a1;
  GameObject a2(5);
  GameObject a3(7);

  std::stringstream s;
  std::stringstream sOut;
  Logger::Log(a1, s);
  sOut << emptyS << std::endl << a1 << std::endl << emptyS <<std::endl<<std::endl;
  EXPECT_EQ(s.str(), sOut.str());

  std::stringstream s1;
  std::stringstream sOut1;
  Logger::Log(a1, create, s1);
  sOut1 << emptyS << std::endl << create << std::endl << a1 << std::endl << emptyS <<std::endl<<std::endl;
  EXPECT_EQ(s1.str(), sOut1.str());

  std::vector<GameObject> v = { a1, a2, a3 };
  std::stringstream s2;
  std::stringstream sOut2;
  Logger::Log(v, create, s2);
  sOut2 << emptyS << std::endl << create << std::endl << a1 << std::endl << emptyS <<std::endl<<std::endl;
  sOut2 << emptyS << std::endl << create << std::endl << a2 << std::endl << emptyS <<std::endl<<std::endl;
  sOut2 << emptyS << std::endl << create << std::endl << a3 << std::endl << emptyS <<std::endl<<std::endl;
  EXPECT_EQ(s2.str(), sOut2.str());

  std::stringstream s3;
  std::stringstream sOut3;
  Logger::Log(v, s3);
  sOut3 << emptyS << std::endl << create << std::endl << a1 << std::endl << emptyS <<std::endl<<std::endl;
  sOut3 << emptyS << std::endl << create << std::endl << a2 << std::endl << emptyS <<std::endl<<std::endl;
  sOut3 << emptyS << std::endl << create << std::endl << a3 << std::endl << emptyS <<std::endl<<std::endl;
  EXPECT_EQ(s2.str(), sOut3.str());
}

TEST(gameObject_test, test_factory)
{
  Factory factory;
  Box2D b1;
  auto gO1 = factory.Create<GameObject>();
  EXPECT_EQ( gO1->Box(), b1 );
  EXPECT_EQ( gO1->HealthPoints(), 0 );

  Point2D p2_1 = { 1.3f, 2.5f };
  Point2D p2_2 = { 2.0f, 3.5f };
  Box2D b2 = { p2_1, p2_2 };
  auto gO2 = factory.Create<GameObject>( b2, 5 );
  EXPECT_EQ( gO2->Box(), b2 );
  EXPECT_EQ( gO2->HealthPoints(), 5 );
  
  auto gO3 = factory.Create<GameObject>( b2 );
  EXPECT_EQ( gO3->Box(), b2 );
  EXPECT_EQ( gO3->HealthPoints(), 0 );

}
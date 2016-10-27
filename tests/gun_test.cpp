#pragma once

#include "gtest/gtest.h"
#include "gun.hpp"
#include <sstream>
#include <unordered_set>

TEST(gun_test, test_construction)
{
  // Тест на создание пришельца по умолчанию.
  Box2D b1 = DEFAULT_GUN_BOX;
  Gun g1;
  EXPECT_EQ( g1.HealthPoints(), DEFAULT_GUN_HP );
  EXPECT_EQ( g1.Box(), b1);
  
  //Тест на создание пришельца с заданным здоровьем
  Gun g2(5);
  EXPECT_EQ( g2.HealthPoints(), 5);
  EXPECT_EQ( g2.Box(), b1);

  //Тест на создание пришельца с заданным боксом
  Box2D b2 = Box2D( Point2D(5, 5), Point2D(7, 7) );
  Gun g3(b2);
  EXPECT_EQ( g3.HealthPoints(), DEFAULT_GUN_HP );
  EXPECT_EQ( g3.Box(), b2 );

  //Тест на создание пришельца с заданными здоровьем и боксом
  Gun g4( b2, 5 );
  EXPECT_EQ( g4.HealthPoints(), 5 );
  EXPECT_EQ( g4.Box(), b2 );
  
  // Тест на создание копии
  Gun g5 = g1;
  EXPECT_EQ( g5, g1 );
}

TEST(gun_test, test_equality)
{
  Point2D p1 = { 1.2f, 2.4f };
  Point2D p2 = { 1.24f, 2.44f };
  Point2D p3 = { 1.3f, 2.7f };
  Box2D b1 = { p1, p2 };
  Box2D b2 = { p1, p2 };
  Box2D b3 = { p1, p3 };
  Gun g1( b1, 1 );
  Gun g2( b2, 1 );
  Gun g3( b3, 2 );
  Gun g4( b1, 2 ); 
  EXPECT_EQ( g1, g2 );
  EXPECT_NE( g1, g3 );
  EXPECT_NE( g1, g4 );
  EXPECT_NE( g4, g3 );
}

TEST(gun_test, test_move)
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
  Gun g1( b1, 2 );
  Gun g2( b2, 3 );
  Gun g00( b00, 0 );
  Gun g10( b10, 2 );
  Gun g20( b20, 3 );
  // move constructor
  Gun g3 = std::move(g1);
  EXPECT_EQ( g1, g00 );
  EXPECT_EQ( g3, g10 );
  // move
  g1 = std::move(g2);
  EXPECT_EQ( g1, g20 );
  EXPECT_EQ( g2, g00 );
  //EXPECT_EQ( g2.HealthPoints(), 0 );
}

TEST(gun_test, test_changeHP)
{
  Gun g1;
  g1.ChangeHP(1);
  EXPECT_EQ( g1.HealthPoints(), DEFAULT_GUN_HP - 1);
  Gun g2;
  g2.ChangeHP( DEFAULT_GUN_HP + 1 );
  EXPECT_EQ( g2.HealthPoints(), 0);
}

TEST(gun_test, test_exception)
{
  EXPECT_THROW(Gun g1(-3), IncorrectDataExceptions);

  Point2D p2_1 = { 1.3f, 2.5f };
  Point2D p2_2 = { 2.0f, 3.5f };
  Box2D b2 = { p2_1, p2_2 };
  EXPECT_THROW(Gun g2( b2, -5 ), IncorrectDataExceptions);
}

TEST(gun_test, test_output)
{
  Point2D p2_1 = { 1.3f, 2.5f };
  Point2D p2_2 = { 2.0f, 3.5f };
  Box2D b = { p2_1, p2_2 };
  Gun g(b, 5);
  std::stringstream s;
  std::stringstream sOut;
  s << g;
  sOut << "Gun HP: " << g.HealthPoints() << " Gun box: " << g.Box();
  EXPECT_EQ(s.str(), sOut.str());
}

TEST(gun_test, test_logger)
{
  std::string create = "create";
  std::string emptyS = "[----------]";

  Gun a1;
  Gun a2(5);
  Gun a3(7);

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

  std::vector<Gun> v = { a1, a2, a3 };
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

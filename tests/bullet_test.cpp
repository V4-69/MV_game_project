#pragma once

#include "gtest/gtest.h"
#include "bullet.hpp"
#include <sstream>
#include <unordered_set>

TEST(bullet_test, test_construction)
{
  // Тест на создание пули по умолчанию.
  Box2D b1 = BULLET_BOX;
  Bullet g1;
  EXPECT_EQ( g1.HealthPoints(), BULLET_HP );
  EXPECT_EQ( g1.Box(), b1 );
  

  //Тест на создание пули с заданым боксом
  Box2D b2 = Box2D( Point2D(5, 5),Point2D(7, 7) );
  Bullet g3(b2);
  EXPECT_EQ( g3.HealthPoints(), BULLET_HP );
  EXPECT_EQ( g3.Box(), b2 );

  //Тест на создание копии
  Bullet g5 = g1;
  EXPECT_EQ( g5, g1 );

  // Тест на создание пули с началом в задданой точке
  Point2D p( 5, 5 );
  Box2D b3( Point2D(5,5), Point2D(6,6) ); // Поменять ,если изменится BULLET_BOX
  Bullet g6(p);
  EXPECT_EQ( g6.Box(), b3 );
}

TEST(bullet_test, test_equality)
{
  Point2D p1 = { 1.2f, 2.4f };
  Point2D p2 = { 1.24f, 2.44f };
  Point2D p3 = { 1.3f, 2.8f };
  Box2D b1 = { p1, p2 };
  Box2D b2 = { p1, p2 };
  Box2D b3 = { p1, p3 };
  Bullet g1( b1 );
  Bullet g2( b2 );
  Bullet g3( b3 );
  Bullet g4( p1 );
  Bullet g5( p3 );
  Bullet g6( Point2D(1.2f, 2.4f) );
  EXPECT_EQ( g1, g2 );
  EXPECT_NE( g1, g3 );
  EXPECT_EQ( g4, g6 );
  EXPECT_NE( g4, g5 );
}

TEST(bullet_test, test_move)
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
  Bullet g1( b1 );
  Bullet g2( b2 );
  Bullet g00( b00 );
  Bullet g10( b10 );
  Bullet g20( b20 );
  // move constructor
  Bullet g3 = std::move(g1);
  EXPECT_EQ( g1.Box(), g00.Box() );
  EXPECT_EQ( g1.HealthPoints(), 0 );
  EXPECT_EQ( g3, g10 );
  // move
  g1 = std::move(g2);
  EXPECT_EQ( g1, g20 );
  EXPECT_EQ( g2.Box(), g00.Box() );
  EXPECT_EQ( g2.HealthPoints(), 0 );
}

TEST(bullet_test, test_changeHP)
{
  Bullet g1;
  g1.ChangeHP(1);
  EXPECT_EQ( g1.HealthPoints(), 0);
}

TEST(bullet_test, test_output)
{
  Point2D p2_1 = { 1.3f, 2.5f };
  Point2D p2_2 = { 2.0f, 3.5f };
  Box2D b = { p2_1, p2_2 };
  Bullet a(b);
  std::stringstream s;
  std::stringstream sOut;
  s << a;
  sOut << "Bullet HP: " << a.HealthPoints() << " Bullet box: " << a.Box();
  EXPECT_EQ(s.str(), sOut.str());
}

TEST(bullet_test, test_logger)
{
  std::string create = "create";
  std::string emptyS = "[----------]";

  Bullet a1;
  Bullet a2;
  Bullet a3;

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

  std::vector<Bullet> v = { a1, a2, a3 };
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

#include "gtest/gtest.h"
#include "alien.hpp"
#include <sstream>
#include <unordered_set>

TEST(alien_test, test_construction)
{
  // Тест на создание пришельца по умолчанию.
  Box2D b1 = DEFAULT_ALIEN_BOX;
  Alien a1;
  EXPECT_EQ( a1.HealthPoints(), DEFAULT_ALIEN_HP );
  EXPECT_EQ( a1.Box(), b1);
  
  //Тест на создание пришельца с заданным здоровьем
  Alien a2(5);
  EXPECT_EQ( a2.HealthPoints(), 5);
  EXPECT_EQ( a2.Box(), b1);

  //Тест на создание пришельца с заданным боксом
  Box2D b2 = Box2D( Point2D(5, 5),Point2D(7, 7) );
  Alien a3(b2);
  EXPECT_EQ( a3.HealthPoints(), DEFAULT_ALIEN_HP );
  EXPECT_EQ( a3.Box(), b2 );

  //Тест на создание пришельца с заданными здоровьем и боксом
  Alien a4(b2, 5);
  EXPECT_EQ( a4.HealthPoints(), 5);
  EXPECT_EQ( a4.Box(), b2 );
  
  // Тест на создание копии
  Alien a5 = a1;
  EXPECT_EQ( a5,a1 );
}

TEST(alien_test, test_equality)
{
  Point2D p1 = { 1.2f, 2.4f };
  Point2D p2 = { 1.24f, 2.44f };
  Point2D p3 = { 1.3f, 2.7f };
  Box2D b1 = { p1, p2 };
  Box2D b2 = { p1, p2 };
  Box2D b3 = { p1, p3 };
  Alien a1( b1, 1 );
  Alien a2( b2, 1 );
  Alien a3( b3, 2 );
  Alien a4( b1, 2 ); 
  EXPECT_EQ( a1, a2 );
  EXPECT_NE( a1, a3 );
  EXPECT_NE( a1, a4 );
  EXPECT_NE( a4, a3 );
}

TEST(alien_test, test_move)
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
  Alien a1( b1, 2 );
  Alien a2( b2, 3 );
  Alien a00( b00, 0 );
  Alien a10( b10, 2 );
  Alien a20( b20, 3 );
  // move constructor
  Alien a3 = std::move(a1);
  EXPECT_EQ( a1, a00 );
  EXPECT_EQ( a3, a10 );
  // move
  a1 = std::move(a2);
  EXPECT_EQ( a1, a20 );
  EXPECT_EQ( a2, a00 );
}

TEST(alien_test, test_changehp)
{
  Alien a1;
  a1.ChangeHP(1);
  EXPECT_EQ( a1.HealthPoints(), DEFAULT_ALIEN_HP-1);
  Alien a2;
  a2.ChangeHP( DEFAULT_ALIEN_HP + 1 );
  EXPECT_EQ( a2.HealthPoints(), 0);
  Alien a3;
}

TEST(alien_test, test_exception)
{
  EXPECT_THROW(Alien a1(-3), IncorrectDataExceptions);

  Point2D p2_1 = { 1.3f, 2.5f };
  Point2D p2_2 = { 2.0f, 3.5f };
  Box2D b2 = { p2_1, p2_2 };
  EXPECT_THROW(Alien a2( b2, -5 ), IncorrectDataExceptions);
}

TEST(alien_test, test_output)
{
  Point2D p2_1 = { 1.3f, 2.5f };
  Point2D p2_2 = { 2.0f, 3.5f };
  Box2D b = { p2_1, p2_2 };
  Alien a(b, 5);
  std::stringstream s;
  std::stringstream sOut;
  s << a;
  sOut << "Alien HP: " << a.HealthPoints() << " Alien box: " << a.Box();
  EXPECT_EQ(s.str(), sOut.str());
}

TEST(alien_test, test_logger)
{
  std::string create = "create";
  std::string emptyS = "[----------]";

  Alien a1;
  Alien a2(5);
  Alien a3(7);

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

  std::vector<Alien> v = { a1, a2, a3 };
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

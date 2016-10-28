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

TEST(ray2d_test, test_exception)
{
  // Тесты на исключения.
  Point2D p1 = { 0.0f, 2.0f };
  Point2D p2 = { 0.0f, 0.0f };
  Point2D p3 = { 2.0f, 3.0f };
  EXPECT_THROW(Ray2D r1( p1, p2 ), IncorrectDataExceptions);
  EXPECT_THROW(Ray2D r2(1.0f, 2.0f, 0.0f, 0.0f), IncorrectDataExceptions);
}

TEST(ray2d_test, test_output)
{
  std::stringstream s;
  Point2D p1 = { 0.0f, 2.0f };
  Point2D p2 = { 1.0f, 0.0f };
  s << Ray2D(p1, p2);
  EXPECT_EQ(s.str(), "Ray2D {Point2D {0, 2}, Point2D {1, 0}}");
}

TEST(ray2d_test, test_logger)
{
  std::string create = "create";
  std::string emptyS = "[----------]";

  Point2D p1 = { 1.0f, 2.0f };
  Point2D p2 = { 1.0f, 0.0f };
  Point2D p3 = { 3.0f, 4.0f };
  Point2D p4 = { 0.0f, 1.0f };

  Ray2D b1 = { p1, p2 };
  Ray2D b2 = { p3, p4 };

  std::stringstream s;
  std::stringstream sOut;
  Logger::Log(b1, s);
  sOut << emptyS << std::endl << b1 << std::endl << emptyS << "\n\n";
  EXPECT_EQ(s.str(), sOut.str());

  std::stringstream s1;
  std::stringstream sOut1;
  Logger::Log(b1, create, s1);
  sOut1 << emptyS << std::endl << create << std::endl << b1 << std::endl << emptyS << "\n\n";
  EXPECT_EQ(s1.str(), sOut1.str());

  std::vector<Ray2D> v = { b1, b2 };
  std::stringstream s2;
  std::stringstream sOut2;
  Logger::Log(v, create, s2);
  sOut2 << emptyS << std::endl << create << std::endl << b1 << std::endl << emptyS << "\n\n";
  sOut2 << emptyS << std::endl << create << std::endl << b2 << std::endl << emptyS << "\n\n";
  EXPECT_EQ(s2.str(), sOut2.str());

  std::vector<Ray2D> v1 = { b1, b2 };
  std::stringstream s3;
  std::stringstream sOut3;
  Logger::Log(v1, s3);
  sOut3 << emptyS << std::endl << b1 << std::endl << emptyS << "\n\n";
  sOut3 << emptyS << std::endl << b2 << std::endl << emptyS << "\n\n";
  EXPECT_EQ(s3.str(), sOut3.str());
}

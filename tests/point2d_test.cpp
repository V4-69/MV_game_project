#include "gtest/gtest.h"
#include "point2d.hpp"
#include <sstream>
#include <unordered_set>

TEST(point2d_test, test_construction)
{
  // Тест на создание объекта по умолчанию.
  Point2D p1;
  EXPECT_EQ(p1.x(), 0.0f);
  EXPECT_EQ(p1.y(), 0.0f);

  // Тест на создание объекта с параметрами.
  Point2D p2 = { 1.2f, 2.4f };
  EXPECT_EQ(p2.x(), 1.2f);
  EXPECT_EQ(p2.y(), 2.4f);

  // Тест на создание копии объекта.
  Point2D p3 = p2;
  EXPECT_EQ(p3, p2);
}

TEST(point2d_test, test_initializer_list)
{
  Point2D p1 = { 1.0f, 2.0f, 3.0f };
  EXPECT_EQ(p1.x(), 1.0f);
  EXPECT_EQ(p1.y(), 2.0f);

  Point2D p2 = { 1.0f };
  EXPECT_EQ(p2.x(), 1.0f);
  EXPECT_EQ(p2.y(), 0.0f);
}

TEST(point2d_test, test_assignment)
{
  Point2D p1;
  p1 = { 1.2f, 2.4f };
  EXPECT_EQ(p1, Point2D(1.2f, 2.4f));
}

TEST(point2d_test, test_equality)
{
  Point2D p1 = { 1.2f, 2.4f };
  Point2D p2 = { 1.2f, 2.4f };
  Point2D p3 = { 1.3f, 2.4f };
  Point2D p4 = { 1.2f, 2.5f };

  EXPECT_EQ(p1, p2);
  EXPECT_NE(p1, p3);
  EXPECT_LT(p1, p3);
  EXPECT_LT(p1, p4);
}

TEST(point2d_test, test_calculus)
{
  Point2D p1 = { 1.2f, 2.4f };
  Point2D p2 = { 1.0f, 2.0f };

  EXPECT_EQ(p1 + p2, Point2D(2.2f, 4.4f));
  EXPECT_EQ(p1 - p2, Point2D(0.2f, 0.4f));
  EXPECT_EQ(p1 * 2.0f, Point2D(2.4f, 4.8f));
  EXPECT_EQ(p1 / 2.0f, Point2D(0.6f, 1.2f));

  p1 += { 1.2f, 2.4f };
  EXPECT_EQ(p1, Point2D(2.4f, 4.8f));

  p1 -= { 1.2f, 2.4f };
  EXPECT_EQ(p1, Point2D(1.2f, 2.4f));

  p1 *= 2.0f;
  EXPECT_EQ(p1, Point2D(2.4f, 4.8f));

  p1 /= 2.0f;
  EXPECT_EQ(p1, Point2D(1.2f, 2.4f));
}

TEST(point2d_test, test_square_brackets)
{
  Point2D p1 = { 1.2f, 2.4f };
  EXPECT_EQ(p1[0], 1.2f);
  EXPECT_EQ(p1[1], 2.4f);
  EXPECT_EQ(p1[2], 0.0f);
}

TEST(point2d_test, test_output)
{
  std::stringstream s;
  s << Point2D(1.2f, 0.2f);
  EXPECT_EQ(s.str(), "Point2D {1.2, 0.2}");
}

TEST(point2d_test, test_hash)
{
  Point2D::Hash hasher;
  EXPECT_EQ(hasher(Point2D(0.0f, 0.0f)), 0);

  std::unordered_set<Point2D, Point2D::Hash> hashTable;
  hashTable.insert(Point2D(0.0f, 0.0f));
  hashTable.insert(Point2D(1.0f, 0.0f));
  EXPECT_EQ(hashTable.size(), 2);
}

TEST(point2d_test, test_move)
{
  Point2D p1 = { 1.0f, 2.0f };
  Point2D p2 = { 3.0f, 4.0f };
  
  // move constructor
  Point2D p3 = std::move(p1);
  EXPECT_EQ(p1, Point2D ( 0.0f, 0.0f ));
  EXPECT_EQ(p3, Point2D ( 1.0f, 2.0f ));
  // move
  p1 = std::move(p2);
  EXPECT_EQ(p1, Point2D ( 3.0f, 4.0f ));
  EXPECT_EQ(p2, Point2D ( 0.0f, 0.0f ));
}

TEST(point2d_test, test_exception)
{
  // Тесты на исключения.
  Point2D p1 = { 0.0f, 0.0f };
  EXPECT_THROW({p1.Normalize();}, IncorrectDataExceptions);
  EXPECT_THROW({p1 /= 0.0f;}, IncorrectDataExceptions);
}
TEST(point2d_test, test_logger)
{
  std::string create = "create";
  std::string emptyS = "[----------]";

  Point2D p1 = { 1.0f, 2.0f };
  Point2D p2 = { 2.0f, 3.0f };
  Point2D p3 = { 3.0f, 4.0f };

  std::stringstream s;
  std::stringstream sOut;
  Logger::Log(p1, s);
  sOut << emptyS << std::endl << p1 << std::endl << emptyS << "\n\n";
  EXPECT_EQ(s.str(), sOut.str());

  std::stringstream s1;
  std::stringstream sOut1;
  Logger::Log(p1, create, s1);
  sOut1 << emptyS << std::endl << create << std::endl << p1 << std::endl << emptyS << "\n\n";
  EXPECT_EQ(s1.str(), sOut1.str());

  std::vector<Point2D> v = { p1, p2, p3 };
  std::stringstream s2;
  std::stringstream sOut2;
  Logger::Log(v, create, s2);
  sOut2 << emptyS << std::endl << create << std::endl << p1 << std::endl << emptyS << "\n\n";
  sOut2 << emptyS << std::endl << create << std::endl << p2 << std::endl << emptyS << "\n\n";
  sOut2 << emptyS << std::endl << create << std::endl << p3 << std::endl << emptyS << "\n\n";
  EXPECT_EQ(s2.str(), sOut2.str());

  std::vector<Point2D> v1 = { p1, p2, p3 };
  std::stringstream s3;
  std::stringstream sOut3;
  Logger::Log(v1, s3);
  sOut3 << emptyS << std::endl << p1 << std::endl << emptyS << "\n\n";
  sOut3 << emptyS << std::endl << p2 << std::endl << emptyS << "\n\n";
  sOut3 << emptyS << std::endl << p3 << std::endl << emptyS << "\n\n";
  EXPECT_EQ(s3.str(), sOut3.str());
}

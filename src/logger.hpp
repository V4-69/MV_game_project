#pragma once

#include <ostream>
#include <iostream>
#include <string>
#include <initializer_list>
#include <fstream>
#include <singleton.hpp>

class Logger : public Singleton<Logger>
{
public:
  template <typename T>
  static std::ostream & Log(T const &obj, std::ostream & os)
  {
    os << "[----------]" << std::endl;
    os << obj << std::endl;
    os << "[----------]" << std::endl << std::endl;
    return os;
  }

  template <typename T>
  static std::ostream & Log(T const &obj, std::string const & act, std::ostream & os)
  {
    os << "[----------]" << std::endl;
    os << act << std::endl;
    os << obj << std::endl;
    os << "[----------]" << std::endl << std::endl;
    return os;
  }

  template <typename T, template<typename, typename...> class C, typename... Args>
  static std::ostream & Log(C <T, Args...> const & objects, std::ostream & os)
  {
    for (auto const & obj : objects)
      Log(obj, os);
    return os;
  }

  template <typename T, template<typename, typename...> class C, typename... Args>
  static std::ostream & Log(C <T, Args...> const & objects, std::string const & act, std::ostream & os)
  {
    for (auto const & obj : objects)
      Log(obj, act, os);
    return os;
  }

  template <typename T>
  static void LogFile(T const &obj)
  {
    std::ofstream file("Log.txt", std::ios_base::app );
    file << "[----------]" << std::endl;
    file << obj << std::endl;
    file << "[----------]" << std::endl << std::endl;
    file.close();
  }
  template <typename T>
  static void LogFile(T const &obj, std::string const & act)
  {
    std::ofstream file("Log.txt", std::ios_base::app );
    file << "[----------]" << std::endl;
    file << act << std::endl;
    file << obj << std::endl;
    file << "[----------]" << std::endl << std::endl;
    file.close();
  }

  template <typename T, template<typename, typename...> class C, typename... Args>
  static void LogFile(C <T, Args...> const & objects)
  {
    for (auto const & obj : objects)
      LogFile(obj);
  }

  template <typename T, template<typename, typename...> class C, typename... Args>
  static void LogFile(C <T, Args...> const & objects, std::string const & act)
  {
    for (auto const & obj : objects)
      LogFile(obj, act);
  }

private:
  friend class Singleton<Logger>;
  Logger() = default;
};

#pragma once

#include <ostream>
#include <iostream>
#include <string>
#include <initializer_list>

class Logger
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
};

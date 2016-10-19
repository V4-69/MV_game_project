#include <ostream>
#include <string>

class IncorrectDataExceptions : public std::invalid_argument
{
public:
  IncorrectDataExceptions() = default;
  IncorrectDataExceptions(const std::string& message):std::invalid_argument(message) {};
  const char* what() const noexcept { return std::invalid_argument::what(); }
  ~IncorrectDataExceptions(){};
};

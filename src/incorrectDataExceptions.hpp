#include <ostream>
#include <string>

class IncorrectDataExceptions : public std::invalid_argument
{
public:
  IncorrectDataExceptions() = default;
  IncorrectDataExceptions(std::string const & message):std::invalid_argument(message) {};
  const char* what() const noexcept { /*будт своя обработка*/ return std::invalid_argument::what(); }
  ~IncorrectDataExceptions(){};
};

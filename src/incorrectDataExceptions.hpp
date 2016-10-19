#include <ostream>
#include <string>

class IncorrectDataExceptions : public std::exception 
{
public:
  IncorrectDataExceptions() = default;
  IncorrectDataExceptions(std::string const & obj): m_messageException(obj){};
  std::string const & messageException() const { return m_messageException; }
  
private:
  std::string m_messageException;
};

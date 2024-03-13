#include <sstream>
#include "token.h"

std::ostream& operator<<(std::ostream& os, const Token& t) {
      std::stringstream tmp;
      tmp << t.tag << ": " << t.word;
      os << tmp.str();
      return os;
}

bool Token::operator==(Token other) const {
    return tag == other.tag;
}

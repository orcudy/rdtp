//
//  Parser2.hpp
//  Parser
//
//  Created by Orcudy on 10/8/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#ifndef COParser
#define COParser

#include <string>
#include <vector>

class Parser {
public:
  static std::vector<std::string> parse(std::string astring, std::string delimiters);
};

#endif

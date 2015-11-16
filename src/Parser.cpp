//
//  Parser.cpp
//  Utils
//
//  Created by Chris Orcutt on 10/8/15.
//  Copyright © 2015 Chris Orcutt. All rights reserved.
//

#include "Parser.hpp"
#include <string>
#include <vector>

using namespace std;

vector<string> Parser::parse(string astring, string delimiters) {
  vector<string> results;
  size_t startPosition = 0;
  ssize_t endPosition = 0;
  string token;
  
  // empty string
  if (astring.empty()){
    return results;
  }
  
  while (endPosition != string::npos) {
    endPosition = astring.find_first_of(delimiters, startPosition);
    
    if (endPosition == string::npos) {
      token = astring.substr(startPosition, astring.length());
    } else {
      token = astring.substr(startPosition, endPosition - startPosition);
    }
    
    if (!token.empty() ){
      results.push_back(token);
    }
    
    startPosition = endPosition + 1;
    
  }
  return results;
}

#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <exception>

/**
 * Reads in a scene description file in XML.
 * */

class parser
{
private:
  static const className = "PARSER";

public:
  parser(){};
  parser(const string &path_to_file);
  ~parser(){};
};

parser::parser(const string &path_to_file)
{
  std::ifstream ifs(path_to_file);
  if (ifs.is_open())
  {
    try
    {
      

      // ...
      ifs.close();
    }
    catch (std::exception e)
    {
      std::cerr << "E\\" << className << ": " << e.what << "\n";
    }
  }
  // tipos de elementos:
  // <e1> </e1>
  // <e1 param="value"> </e1>
  // <e2 />
  // <e2 param="value"/>
}

#endif
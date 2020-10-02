#include <iostream>

#include "api.hpp"
#include "cxxopts.hpp"
#include "parser.hpp"

int main(int argc, char** argv) {
  cxxopts::Options options("RT3", "Ray Tracing Program under development");

  // Args parser
  options.add_options()("i,input", "input xml filename path",
    cxxopts::value<std::string>())  // a bool parameter
    ("v,verbose", "verbose output",
      cxxopts::value<bool>()->default_value("false"));

  auto parsedArgs = options.parse(argc, argv);

  if (parsedArgs.count("help")) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  bool verbose = parsedArgs["verbose"].as<bool>();
  std::string filename;
  if (parsedArgs.count("input")) {
    filename = parsedArgs["input"].as<std::string>();

    // XML parser
    rt3::API api;
    Parser parser(filename);
    parser.extractData(api);

    // API commands
    if (verbose) {
      api.print();
    }

    api.RT();
    api.save();

  }
  else {
    std::cout << options.help() << std::endl;
    return 1;
  }
  return 0;
}

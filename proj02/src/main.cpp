#include <iostream>

#include "api.hpp"
#include "cxxopts.hpp"
#include "parser.hpp"

bool arguments_parsing(int argc, char** argv, bool& verbose, std::string& filename) {
  cxxopts::Options options("RT3", "Ray Tracing Program under development");

  // Args parser
  options.add_options()("i,input", "input xml filename path",
    cxxopts::value<std::string>())  // a bool parameter
    ("v,verbose", "verbose output",
      cxxopts::value<bool>()->default_value("false"));

  auto parsedArgs = options.parse(argc, argv);

  if (parsedArgs.count("help")) {
    std::cout << options.help() << std::endl;
    return false;
  }

  verbose = parsedArgs["verbose"].as<bool>();
  if (parsedArgs.count("input")) {
    filename = parsedArgs["input"].as<std::string>();

    return true;
  }
  else {
    std::cout << options.help() << std::endl;
    return false;
  }
}

void start_api(bool verbose, std::string& filename) {
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

void run_parsing_args(int argc, char** argv) {
  bool verbose;
  std::string filename;

  if (arguments_parsing(argc, argv, verbose, filename)) {
    start_api(verbose, filename);
  }

}

void run_default(const bool verbose, const char* xmlpath) {
  std::string filename = xmlpath;

  start_api(verbose, filename);

}

int main(int argc, char** argv) {

  // run_parsing_args(argc, argv);

  // run_default(true, "../data/in/ex1-2-interpolated.xml");
  run_default(true, "../data/in/ex2-1-ortographic.xml");
  // run_default(true, "../data/in/ex2-1-ot.xml");


  return 0;
}

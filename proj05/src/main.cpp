#include <iostream>
#include <iomanip> 

#include "core/api.hpp"
#include "external/cxxopts.hpp"
#include "external/progress_bar.hpp"
#include "core/parser.hpp"

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
  // if (verbose) {
  //   api.print();
  // }

  // api.render();
  // api.save();
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
  // run_default(true, "../data/in/ex2-1-ortographic.xml");
  // run_default(true, "../data/in/ex2-2-perspective.xml");
  // run_default(true, "../data/in/basic_prj02.xml");
  // run_default(true, "../data/in/basic_prj02_ortho.xml");
  // run_default(true, "../data/in/ex3-1-orto.xml");
  // run_default(true, "../data/in/ex3-2-pers.xml");
  // run_default(true, "../data/in/ex4-1-pers.xml");
  run_default(true, "../scenes/projects_references/proj_05_blinn_phong/lights_scene/bphong_scene_main.xml");

  // progressbar(1, std::string("ave"));
  // progressbar(2, "maria");
  // progressbar_finish();


  return 0;
}

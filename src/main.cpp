#include <iostream>
#include "vector3.hpp"
#include "parser.hpp"

#include "camera.hpp"
#include "film.hpp"
#include "background.hpp"

void RT()
{
  int nx = 200;
  int ny = 100;
  std::cout << "P3\n"
            << nx << " " << ny << "\n"
            << "255\n";
  for (int y = 0; y < ny; y++)
  {
    for (int x = 0; x < nx; x++)
    {
      Vector3 col(float(x) / float(nx), float(y) / float(ny), 0.2);
      int ir = int(255.99 * col.r());
      int ig = int(255.99 * col.g());
      int ib = int(255.99 * col.b());
      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}

int main(int argc, char const *argv[])
{
  Camera camera;
  Film film;
  Background bg;

  Parser parser("ex1.xml");
  parser.extractData(camera, film, bg);

  film.print();
  bg.print();
  
  return 0;
}

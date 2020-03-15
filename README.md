---

1. A class Film that handles pixels values as an image color buffer. This allows the ray tracer to save the color buffer to an image file in PPM or PNG format. The class is named Film because it plays a role similar to a film in an analog camera, or sensor in a modern digital camera.
2. A class Background that is responsible for returning a color each time the primary ray misses any object in the scene (i.e. hits nothing).
3. A set of classes to handle the math operations on vectors and matrices. In this case you might either implement your own library (Vector3, Point3, Mat3x3, etc.) based on the one provided in "Ray Tracing in One Weekend", or adopt other math libraries such as OpenGL Mathematics, or cyCodeBase.
4. The main loop of the  ray tracing algorithm, which should traverse the image pixels and shoot rays into the scene. At this stage, the main loop only traverses the image and samples colors from the Background object. (no rays are shot just yet)
5. A parser class or set of functions that reads in a scene description file in XML with the format explained below.

---

https://projetos.imd.ufrn.br/CG_20201/ray-tracer-teaching-tool/tree/master/prj01

https://github.com/jarro2783/cxxopts - tratamento de args passados para o programa
https://github.com/lvandeve/lodepng - salvar imagens no formato PNG
https://github.com/RayTracing/raytracing.github.io/tree/master/src/InOneWeekend - vector3.hpp
https://github.com/leethomason/tinyxml2 - parser de arquivos que obdeçam o formato xml
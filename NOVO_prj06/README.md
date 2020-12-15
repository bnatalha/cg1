# Projeto 06

### __Testado apenas em Linux!__

## O que foi feito

### pr5
- [x] blinn-phong:
    - [x] difuse,
    - [x] specular
    - [x] ambient;
- [ ] lights:
    - [x] point;
    - [x] ambient;
    - [x] directional;
    - [ ] spot;
- [ ] hard shadows;
    - [x] point;
    - [ ] directional;
    - [ ] spot;
- [x] mirror;

### pr6
- [x] triangle mesh:
    - [ ] calcular a normal
    - [x] ler da cena;
    - [x] ler de obj;
- blin phong shading;

### pr7


## Compilando
Para compilar, basta digitar o comando `$ make` no terminal estando dentro deste diretório.

Certifique-se de possuir uma versão recente do __clang__ instalada; caso contrário, altere a flag `CC` no arquivo _makefile_ para compilar o projeto com o __gcc__. 

## Executando o programa

Para executar o programa, digite `$ bin/main`. Os arquivos `xml` se encontram no diretorio `../data/in`.

### Rodando os exemplos do projeto 5:

- `$ bin/main ` 

## Bibliotecas externas utilizadas
1. https://github.com/jarro2783/cxxopts - tratamento de args passados para o programa
2. https://github.com/lvandeve/lodepng - salvar imagens no formato PNG
3. https://github.com/RayTracing/raytracing.github.io/tree/master/src/InOneWeekend - vector3.hpp
4. https://github.com/leethomason/tinyxml2 - parser de arquivos que obdeçam o formato xml

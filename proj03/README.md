# Projeto 03

### __Testado apenas em Linux!__

## Compilando
Para compilar, basta digitar o comando `$ make` no terminal estando dentro deste diretório.

Certifique-se de possuir uma versão recente do __clang__ instalada; caso contrário, altere a flag `CC` no arquivo _makefile_ para compilar o projeto com o __gcc__. 

## Executando o programa

Para executar o programa, digite `$ bin/main`. Os arquivos `xml` se encontram no diretorio `../data/in`.

### Rodando os exemplos do projeto 3:

- `$ bin/main -i ../data/in/ex3-2-pers.xml` 
- `$ bin/main -i ../data/in/ex3-1-orto.xml`

## Bibliotecas externas utilizadas
1. https://github.com/jarro2783/cxxopts - tratamento de args passados para o programa
2. https://github.com/lvandeve/lodepng - salvar imagens no formato PNG
3. https://github.com/RayTracing/raytracing.github.io/tree/master/src/InOneWeekend - vector3.hpp
4. https://github.com/leethomason/tinyxml2 - parser de arquivos que obdeçam o formato xml

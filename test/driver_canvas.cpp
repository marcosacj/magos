#include <iostream>
#include <cstring>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "canvas.h"

using namespace canvas;

int main(void)
{
    // Cria um objeto canvas de 800 por 600 pixels de dimensão.
    Canvas c( 800, 600 );

    // Definie a cor de fundo da imagem.
    c.clear( LIGHT_GREY );

    // Vamos desenhar um retângulo cujo canto superior esquerdo está em (100,100).
    coord_type orig_x{100}, orig_y{100};
    // Vamos utilizar uma linha com 3 pixels de largura.
    c.thickness( 3 );
    // Um retângulo pode ser formado através do desenho de 4 linhas.
    c.hline( orig_x, orig_x, 300, RED );
    c.vline( orig_x, orig_y, 200, STEEL_BLUE );
    c.hline( orig_x, orig_y+200, 300, GREEN );
    c.vline( orig_x+300, orig_y, 200, YELLOW );
    // Preencher o interior do retângulo com um quadrado de 50 x 50 pixels.
    c.box( orig_x+125, orig_y+75, 50, 50, DEEP_SKY_BLUE );

    // Recuperar as informações do Canvas (imagem) para poder gravar um arquivo PNG.
    auto width = c.width();
    auto height = c.height();
    auto pixels = c.buffer(); // Ponteiro para o vetor de bytes representando a imagem.

    // Invocando a função de gravação da biblioteca STB para gravar PNG.
    stbi_write_png_compression_level = 0;    // defaults to 8; set to higher for more compression
    stbi_write_png( "../data/teste.png",      // file name
                width, height,        // image dimensions
                3,                    // # of channels per pixel
                pixels,               // the pixels
                width*3)  ;           // length of a row (in bytes), see above.

    // Testando construtor copia
    Canvas p(c);

    width  = p.width();
    height = p.height();
    pixels = p.buffer();

    stbi_write_png( "../data/teste_copia.png", width, height, 3, pixels, width*3);

    // Testando construtor atribuicao
    Canvas a;

    a = c;

    width  = a.width();
    height = a.height();
    pixels = a.buffer();

    stbi_write_png( "../data/teste_assign.png", width, height, 3, pixels, width*3);

    // Testando obtencao de cor de um pixel
    assert( c.pixel(10,15) == LIGHT_GREY );

}

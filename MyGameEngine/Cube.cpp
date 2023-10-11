#include "Cube.h"
#include <IL/il.h>

Cube::Cube() :
    a(-1, -1, 1),
    b(1, -1, 1),
    c(1, 1, 1),
    d(-1, 1, 1),
    e(-1, -1, -1),
    f(1, -1, -1),
    g(1, 1, -1),
    h(-1, 1, -1),
    red(1, 0, 0),
    green(0, 1, 0),
    blue(0, 0, 1),
    yellow(1, 1, 0),
    white(0, 1, 1),
    black(1, 0, 1) {

    ilInit();

    auto img = ilGenImage();
    ilBindImage(img);
    ilLoadImage("Lenna.png");
    auto width = ilGetInteger(IL_IMAGE_WIDTH);
    auto height = ilGetInteger(IL_IMAGE_HEIGHT);
    auto channels = ilGetInteger(IL_IMAGE_CHANNELS);
    auto data = ilGetData();



}


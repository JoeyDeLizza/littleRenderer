#include "tgaimage.h"
#include <cstdlib>
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);
void plotLineLow(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);
void plotLineHigh(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color); 

int main(int argc, char** argv) {
        TGAImage image(100, 100, TGAImage::RGB);
        line(0,0,50,50, image, white);

	image.flip_vertically();
        image.write_tga_file("output.tga");
        return 0;
}

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
  
  if (std::abs(y1 - y0) < std::abs(x1 - x0)) {
    if (x0 > x1) {
      plotLineLow(x1, y1, x0, y0, image, color);
    } else {
      plotLineLow(x0, y0, x1, y1, image, color);
    }
  } else {
    if (y0 > y1) {
       plotLineHigh(x1, y1, x0, y0, image, color);
    } else {
      plotLineHigh(x0, y0, x1, y1, image, color);
    }
  }
  
}

void plotLineHigh(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  int xi = 1;
  if (dx < 0) {
    xi = -1;
    dx = -dx;
  }

  int D = (2* dx) - dy;
  int x = x0;
  for(int y = y0; y <=y1; y++) {
    image.set(x, y, color);
    if (D > 0) {
      x = x +xi;
      D = D + (2 * (dx - dy));
    } else{
      D = D + 2*dx;
    }
  }
}

void plotLineLow(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  int yi = 1;
  if (dy < 0) {
    yi = -1;
    dy = -dy;
  }

  int D = (2*dy) -dx;
  int y = y0;
  for(int x = x0; x <= x1; x++) {
    image.set(x, y, color);
    if(D > 0) {
      y = y + yi;
      D = D + (2 * (dy -dx));
    } else {
      D = D + 2*dy;
    }
  }
}

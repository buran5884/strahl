#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "img_handler.hpp"
#include "strahl.hpp"

using namespace std;

#define HEIGHT 100
#define WIDTH 100
#define CHANNEL_NUM 3

int drawLine(RenderedImg& img,int x0,int y0,int x1,int y1){
    RGBA col(0,255,0);
    int dx = x1-x0;
    int dy  = y1-y0;
    int D = 0;
    // img.SetPixelColor(x0,y0,col);
    int y= y0;
    for(int x = x0;x <= x1;x++){
        img.SetPixelColor(x,y,col);
        D += 2*dy;
        if(D > dx){
            y += 1;
            D -= 2*dx;
        }
    }
    return 0;
}

int main() {
    RenderedImg img(WIDTH, HEIGHT, MODE_RGB);
    RGBA fillcolor(0, 0, 0);
    RGBA pixelcolor(0, 255, 255);
    img.FillColor(fillcolor);
    // img.SetPixelColor(9, 9, pixelcolor);
    drawLine(img,80,50,90,90);
    img.SaveImg("result.png");

    return 0;
}

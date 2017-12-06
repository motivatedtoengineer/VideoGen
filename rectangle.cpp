#include "rectangle.h"
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cstring>

Rectangle::Rectangle() {
    // Constract the ffmpeg to run.
    const char * cmd =
    "ffmpeg              "
    "-y                  "
    "-hide_banner        "
    "-f rawvideo         " // input to be raw video data
    "-pixel_format rgb24 "
    "-video_size 720x480 "
    "-r 60               " // frames per second
    "-i -                " // read data from the standard input stream
    "-pix_fmt yuv420p    " // to render with Quicktime
    "-vcodec mpeg4       "
    "-an                 " // no audio
    "-q:v 5              " // quality level; 1 <= q <= 32
    "output.mp4          ";
    
    // Run the ffmpeg command and get pipe to write into its standard input stream.
#ifdef _WIN32
    FILE * p = _popen(cmd, "wb");
#else
    FILE * p = popen(cmd, "w");
#endif
    // handle error creating renderer
    if (p == 0) {
        std::cout << "error: " << strerror(errno) << std::endl;
        //return 1;
    }
    
    pipe = p;
}

Rectangle::~Rectangle() {
    fflush(pipe);
    
#ifdef _WIN32
    _pclose(pipe);
#else
    pclose(pipe);
#endif
}


void Rectangle::clear_frame() {
    memset(frame, 0, sizeof(frame));
}

void Rectangle::clamp(int * x, int * y) {
    if (*x < 0) *x = 0; else if (*x >= W) *x = W - 1;
    if (*y < 0) *y = 0; else if (*y >= H) *y = H - 1;
}

bool Rectangle::outside_frame(int * x, int * y) const {
    return *x < 0 || *x >= W || *y < 0 || *y >= H;
}

void Rectangle::draw_rect(int x, int y, int w, int h, byte r, byte g, byte b){
    if (outside_frame(&x, &y)) return;
    int x0 = x;
    int x1 = x + w;
    int y0 = y;
    int y1 = y + h;
    clamp(&x0, &y0);
    clamp(&x1, &y1);
    for (int y = y0; y < y1; ++y) {
        for (int x = x0; x < x1; ++x) {
            frame[y][x][0] = r;
            frame[y][x][1] = g;
            frame[y][x][2] = b;
        }
    }
    fwrite(frame, 3, W * H, pipe);
}

//going to draw each rectangle
void Rectangle::draw_frame(double t) {
    clear_frame();
    const double pps = 80;
    //determines size, location, and color or rectangle
    draw_rect(100, 0 + t * pps, 25, 12, 0xff, 0x00, 0x00);
    draw_rect(480, 0 + t * pps, 100, 30, 0x00, 0xff, 0x00);
    draw_rect(300, 0 + t * pps, 70, 20, 0x00, 0x00, 0xff);
}

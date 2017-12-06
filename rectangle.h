#include <stdio.h>

#define W 720
#define H 480

typedef unsigned char byte;

class Rectangle {
public:
    Rectangle();
    ~Rectangle();
    void draw_rect(int x, int y, int w, int h, byte r, byte g, byte b);
    void clear_frame();
    void clamp(int * x, int * y);
    void draw_frame(double t);
    bool outside_frame(int * x, int * y) const;
private:
    FILE *pipe;
    unsigned char frame[H][W][3];
};

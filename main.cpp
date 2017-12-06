#include <iostream>
#include "rectangle.h"

using namespace std;

const double frames_per_sec = 20;
const int dur_in_sec = 5;

Rectangle rect;

int main() {
    int num_frames = dur_in_sec * frames_per_sec;
    for (int i = 0; i < num_frames; ++i) {
        double time_in_sec = i / frames_per_sec;
        rect.draw_frame(time_in_sec);
    }
    
    cout << "num_frames: " << num_frames << endl;
    cout << "Done." << endl;
    return 0;
}

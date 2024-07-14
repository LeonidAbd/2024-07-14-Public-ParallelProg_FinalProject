#include <iostream>
#include "graphics.h"

using namespace std;

int main(void) {
    Graphics instance = *Graphics::get_instance();
    instance.mainloop();
}
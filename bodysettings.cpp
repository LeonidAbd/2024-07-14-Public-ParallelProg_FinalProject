#include <cmath>

using namespace std;

struct Body_Setting {
public:
    int x;
    int y;
    double size;
    Body_Setting(double* coordinates, double size) {
        this->x = round(coordinates[0]);
        this->y = round(coordinates[1]);
        this->size = size;
    }
};
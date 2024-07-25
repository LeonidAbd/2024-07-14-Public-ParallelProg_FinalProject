#include <iostream>
#include <vector>
#include "graphics.h"
#include "body.h"
#include <random>
#include "bodymanager.h"
#include <omp.h>

using namespace std;

#include "includes.h"

void f(vector<int> array) {
    array.push_back(0);
}

int main(int argc, char *argv[])
{
    omp_set_num_threads(NUM_THREADS);
    vector<Body> bodies = BodyManager::get_bodies(argc, argv);

    if (bodies.empty())
    {
        cerr << "No bodies to display." << endl;
        return 1;
    }

    Graphics instance = *Graphics::get_instance(1.0, bodies);
    instance.mainloop();

    return 0;
}

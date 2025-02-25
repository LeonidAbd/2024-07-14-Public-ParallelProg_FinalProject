#include "includes.h"
#include "bodymanager.h"
#include <random>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <string>

vector<Body> BodyManager::generate_orbiting_bodies(int num_bodies, double central_mass)
{
    vector<Body> bodies;

    random_device rd;
    mt19937 generator(rd());

    uniform_real_distribution<double> radius_dist(50.0, 300.0);
    uniform_real_distribution<double> velocity_dist(10.0, 100.0);
    uniform_real_distribution<double> size_dist(1.0, 10.0);

    Body central_body(CENTRAL_BODY_MASS, 400, 400, 0, 0);
    central_body.set_size(30);
    bodies.push_back(central_body);

    for (int i = 0; i < num_bodies; ++i)
    {
        double radius = radius_dist(generator);
        double angle = uniform_real_distribution<double>(0.0, 2 * M_PI)(generator);

        double coord_x = 400 + radius * cos(angle);
        double coord_y = 400 + radius * sin(angle);

        double velocity = sqrt(GRAVITY_CONSTANT * CENTRAL_BODY_MASS / radius);
        double velocity_x = -velocity * sin(angle);
        double velocity_y = velocity * cos(angle);

        double size = size_dist(generator);

        Body body(1.0, coord_x, coord_y, velocity_x, velocity_y);
        body.set_size(size);

        bodies.push_back(body);
    }

    return bodies;
}

vector<Body> BodyManager::create_static_bodies()
{
    vector<Body> bodies(0);

    Body body1(1000000.0, 400, 400, 0, 0);
    body1.set_size(5);
    bodies.push_back(body1);

    Body body2(10000.0, 360, 400, 0, 100);
    bodies.push_back(body2);
    Body body3(10000.0, 470, 400, 0, -100);
    bodies.push_back(body3);
    Body body4(10000.0, 400, 510, 100, 0);
    bodies.push_back(body4);
    Body body5(10000.0, 400, 280, -100, 0);
    bodies.push_back(body5);

    return bodies;
}

std::vector<Body> BodyManager::get_bodies(int argc, char *argv[])
{
    if (argc > 1)
    {
        int num_bodies;
        try
        {
            num_bodies = std::stoi(argv[1]);
            if (num_bodies < 1)
            {
                throw std::invalid_argument("Number of bodies must be positive.");
            }
            return generate_orbiting_bodies(num_bodies, CENTRAL_BODY_MASS);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            return {};
        }
    }
    else
    {
        return create_static_bodies();
    }
}

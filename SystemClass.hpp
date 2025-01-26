#ifndef SystemClass_h
#define SystemClass_h

#include <iostream>
#include <vector>
#include "ParticleClasses.hpp"
#include "GUIClass.hpp"

namespace particles
{
    class System
    {
        std::vector<Particle*> parts;
        int steps;
        GUI* gui;
        public:
        System(int seed, int lighcount, int heavycount);
        System(System& sys);
        void operator=(System& sys);
        void check_collisions();
        void step();
        void addParticle(Particle* part);
        void deleteParticle();
        std::vector<Particle*> get_parts();
        int get_steps() const;
        void set_steps(int n);
        void draw();
        ~System();

        static const int yoffset = 55;
    };
}

#endif
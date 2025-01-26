#include<iostream>
#include<vector>
#include"ParticleClasses.hpp"
#include"SystemClass.hpp"
#include"GUIClass.hpp"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>

int main(int argc, char** argv)
{
    int seed = atoi(argv[1]), lightcount = atoi(argv[2]), heavycount = atoi(argv[3]);
    particles::System sys(seed, lightcount, heavycount); 
    Fl::run();
}
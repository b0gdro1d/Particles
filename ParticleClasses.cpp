#include"ParticleClasses.hpp"
#include<cmath>
#include<cstdlib>
#include<random>

using namespace particles;

Particle::Particle(): coordinates(20,20), v(10,10) {} 



std::pair<double, double> Particle::move() {return std::make_pair(0,0);}

std::pair<double, double> Particle::get_coordinates() { return coordinates;}

double Particle::get_x() const {return coordinates.first;}
double Particle::get_y() const {return coordinates.second;}

void Particle::set_coordinates(std::pair<double, double> new_coordinates)  {coordinates = new_coordinates;}

std::pair<double, double> Particle::get_v() { return v;}
void Particle::set_v(std::pair<double, double> new_v)  {v = new_v;}

void Particle::collision(Particle& part) {}

void Particle::coordinates_correction(Particle& other, double xnorm, double ynorm, double distance)
{
    double correction_x = xnorm * (get_r() + other.get_r() - distance);  
    double correction_y = ynorm * (get_r() + other.get_r() - distance);  
    double newx = coordinates.first - correction_x * (get_weight() / (get_weight() + other.get_weight()));  
    double newy = coordinates.second - correction_y * (get_weight() / (get_weight() + other.get_weight()));  
    coordinates = std::make_pair(newx, newy);  
    double newox = other.get_x() + correction_x * (other.get_weight() / (get_weight() + other.get_weight()));  
    double newoy = other.get_y() + correction_y * (other.get_weight() / (get_weight() + other.get_weight()));  
    other.set_coordinates(std::make_pair(newox, newoy)); 
}

void Particle::wall_collision()
{
    if (coordinates.first - get_r() < 0) 
    {
        v.first*=-1;
        coordinates.first = get_r();
    }
    if (coordinates.second - get_r() < 0) 
    {
        v.second*=-1;
        coordinates.second = get_r();
    }
    if (coordinates.first + get_r() > width) 
    {
        v.first= -(11 > v.first ? 11 : v.first);
        coordinates.first=width - get_r();
    }
    if (coordinates.second + get_r() > height) 
    {
        v.second= -(11 > v.second ? 11 : v.second);
        coordinates.second=height - get_r();
    }
}

LightParticle::LightParticle() : Particle()
{
    coordinates.first = abs(rand())%(width - 2 * r) + r;
    coordinates.second = abs(rand())%(height - 2 * r) + r;
    v.first = rand()%40;
    v.second = rand()%40;
}

double LightParticle::get_r() const { return r;}

double LightParticle::get_weight() { return 5;}

std::pair<double, double> LightParticle::move()
{
    coordinates.first += v.first * dt;
    coordinates.second += v.second * dt;
    return coordinates;
}

void LightParticle::collision(Particle& other)
{
    double dx = other.get_x() - coordinates.first;  
    double dy = other.get_y() - coordinates.second;  
    double distance = sqrt(dx*dx + dy*dy); 
    if (r + other.get_r() < distance) return;  
    double xnorm = dx / distance;  
    double ynorm = dy / distance;  
    coordinates_correction(other, xnorm, ynorm , distance);
    if(other.get_r() == 5)
    {
        std::pair<double, double> temp = std::make_pair(v.first, v.second);
        v = other.get_v();
        other.set_v(temp);
    }
    else
    {
        double v1n = v.first * xnorm + v.second * ynorm;  
        double v2n = other.get_v().first * xnorm + other.get_v().second * ynorm;  
        double v1 = (v1n * (weight - other.get_weight()) + 2 * other.get_weight() * v2n) / (weight + other.get_weight());  
        double v2 = (v2n * (other.get_weight() - weight) + 2 * weight * v1n) / (weight + other.get_weight());  
        double newvx = v.first + (v1 - v1n) * xnorm;  
        double newvy = v.second + (v1 - v1n) * ynorm;  
        v = std::make_pair(newvx, newvy);  
        double newovx = other.get_v().first + (v2 - v2n) * xnorm;  
        double newovy = other.get_v().second + (v2 - v2n) * ynorm;  
        other.set_v(std::make_pair(newovx, newovy)); 
    }
}

HeavyParticle::HeavyParticle() : Particle()
{
    r = abs(rand())%50 + 10;
    weight = abs(rand())%20 + 10;
    coordinates.first = abs(rand())%800 + r;
    coordinates.second = abs(rand())%600 + r + yoffset;
    v.first = rand()%50;
    v.second = rand()%50;
}

double HeavyParticle::get_r() const { return r;}

double HeavyParticle::get_weight() { return weight;}

std::pair<double, double> HeavyParticle::move()
{
    coordinates.first += (double) ceil(v.first * dt);
    coordinates.second += (double) ceil(v.second * dt);
    return coordinates;
}

void HeavyParticle::collision(Particle& other)
{
    double dx = other.get_x() - coordinates.first;  
    double dy = other.get_y() - coordinates.second;  
    double distance = sqrt(dx*dx + dy*dy);    
    if (r + other.get_r() < distance) return;
    double xnorm = dx / distance;  
    double ynorm = dy / distance;  
    coordinates_correction(other, xnorm, ynorm, distance); 
    double v1n = v.first * xnorm + v.second * ynorm;  
    double v2n = other.get_v().first * xnorm + other.get_v().second * ynorm;  
    double v1 = (v1n * (weight - other.get_weight()) + 2 * other.get_weight() * v2n) / (weight + other.get_weight());  
    double v2 = (v2n * (other.get_weight() - weight) + 2 * weight * v1n) / (weight + other.get_weight());  
    double newvx = v.first + (v1 - v1n) * xnorm;  
    double newvy = v.second + (v1 - v1n) * ynorm;  
    v = std::make_pair(newvx, newvy);  
    double newovx = other.get_v().first + (v2 - v2n) * xnorm;  
    double newovy = other.get_v().second + (v2 - v2n) * ynorm;  
    other.set_v(std::make_pair(newovx, newovy));  
}

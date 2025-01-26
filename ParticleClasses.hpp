#ifndef ParticleClasses_h
#define ParticleClasses_h

#include <iostream>
#include <vector>

namespace particles
{
    class HeavyParticle;

    class Particle
    {
        protected:
        std::pair<double, double> coordinates; 
        std::pair<double, double> v;
        public:
        Particle();

        virtual std::pair<double, double> move() = 0;

        virtual void collision(Particle& other) = 0;

        void coordinates_correction(Particle& other, double xnorm, double ynorm, double distance);

        virtual void wall_collision();

        std::pair<double, double> get_coordinates();

        double get_x() const;
        double get_y() const;
        
        void set_coordinates(std::pair<double, double> new_coordinates);

        std::pair<double, double> get_v();
        void set_v(std::pair<double, double> new_v);

        virtual double get_r() const = 0;
        
        virtual double get_weight() = 0;

        virtual ~Particle() = default;

        const static int width = 945;
        const static int height = 795;
        const double dt = 0.1;
        const static int yoffset = 55;
    };

    class LightParticle : public Particle
    {
        static const int r = 5;
        static const int weight = 5;
        public:
        LightParticle();

        double get_r() const;
        
        double get_weight();

        std::pair<double, double> move();

        void collision(Particle& other) override;

        ~LightParticle() = default;
    };

    class HeavyParticle : public Particle
    {
        int r;
        int weight;
        public:
        HeavyParticle();

        double get_r() const;
        
        double get_weight();

        std::pair<double, double> move();

        void collision(Particle& other) override;

        ~HeavyParticle() = default;
    };
}

#endif


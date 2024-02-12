#ifndef Darwin_PS_Generator_Sphere_HH
#define Darwin_PS_Generator_Sphere_HH

#include <iostream>
#include <random>
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"

using namespace std;

class Darwin_PS_Generator_Sphere:
    public G4VUserPrimaryGeneratorAction
{
    public:
        Darwin_PS_Generator_Sphere(G4double gen_radius_cc,
                                std::vector<G4double> upper_cc,
                                std::vector<G4double> lower_cc,
                                std::vector<G4double> flux_prob_cc);
        ~Darwin_PS_Generator_Sphere();
        virtual void GeneratePrimaries(G4Event*);
    
    private:
        G4ParticleGun *fParticleGun;

        //init xyz
        G4double init_x, init_y, init_z;
        G4ThreeVector init_position;
        //init momentum direction
        G4double init_px, init_py, init_pz;
        G4ThreeVector init_MomDirec;
        //kinetic energy and spectrum
        std::vector<G4double> upper,lower,flux_prob;
        G4double Ek;

        //init generate surface radius
        G4double gen_radius;

        //init function for xyz, momentum direction and Ek
        void init(G4double &init_x,  G4double &init_y,  G4double &init_z,
                  G4double &init_px, G4double &init_py, G4double &init_pz,
                  G4double gen_radius);
        G4double init_Ek(std::vector<G4double> upper,
				       std::vector<G4double> lower,
				       std::vector<G4double> flux_prob);
        
        //Spherical Surface Generation
        void Marsaglia(G4double &x, G4double &y, G4double &z, G4double R);

        //random number generator
        long int time_now;
        mt19937 generator;
        uniform_real_distribution<double> distribution;

        G4double rand();
};

#endif
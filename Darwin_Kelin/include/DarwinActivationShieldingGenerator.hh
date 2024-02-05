#ifndef DarwinActivationShieldingGenerator_HH
#define DarwinActivationShieldingGenerator_HH

#include <iostream>
#include <random>
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"

using namespace std;

class DarwinActivationShieldingGenerator :
public G4VUserPrimaryGeneratorAction
{
public:
	DarwinActivationShieldingGenerator(G4double world_length_cc, 
									   G4double gen_radius_cc,
									   std::vector<G4double> upper_cc, 
									   std::vector<G4double> lower_cc,
									   std::vector<G4double> flux_prob_cc,
									   G4String sphere_cc,
									   G4String file_name_cc,
									   G4double gen_z_cc);
	~DarwinActivationShieldingGenerator();
	virtual void GeneratePrimaries(G4Event*);
	
					   

private:
	G4ParticleGun *fParticleGun;

	//Parameters from main function
	G4double world_length;	//Range of position 
	G4String p_type;			//Momentum Reading type
	G4String file_name;

	//position and momentum limit
	G4double init_x, init_y, init_z, init_p, init_px, init_py, init_pz;
	G4double gen_radius,gen_z;
	std::vector<G4double> upper,lower,flux_prob;

	G4String sphere;
	void init_Sphere_Real_Posi_Mom(G4double& init_x,G4double& init_y,G4double& init_z,
					   G4double& init_px,G4double& init_py,G4double& init_pz,
					   G4double& init_p, G4String p_type, G4double world_length,
					   G4double gen_radius,
					   std::vector<G4double> upper,
					   std::vector<G4double> lower,
					   std::vector<G4double> flux_prob);
	void init_Sphere_Center_Posi_Mom(G4double& init_x,G4double& init_y,G4double& init_z,
					   G4double& init_px,G4double& init_py,G4double& init_pz,
					   G4double& init_p, G4String p_type, G4double world_length,
					   G4double gen_radius,
					   std::vector<G4double> upper,
					   std::vector<G4double> lower,
					   std::vector<G4double> flux_prob);
	void init_True_Real_Posi_Mom(G4double& init_x,G4double& init_y,G4double& init_z,
					   G4double& init_px,G4double& init_py,G4double& init_pz,
					   G4double& init_p, G4String p_type, G4double world_length,
					   G4double gen_radius,
					   std::vector<G4double> upper,
					   std::vector<G4double> lower,
					   std::vector<G4double> flux_prob);	//flat spectrum

	void init_Real_Clin_Posi_Mom(G4double& init_x,G4double& init_y,G4double& init_z,
					   G4double& init_px,G4double& init_py,G4double& init_pz,
					   G4double& init_p, G4String p_type, G4double world_length,
					   G4double gen_radius, G4double gen_z,
					   std::vector<G4double> upper,
					   std::vector<G4double> lower,
					   std::vector<G4double> flux_prob);
	
	//Spherical Surface Average
	G4double u,v,r0;
	void Marsaglia(G4double &x, G4double &y, G4double &z);

	//random number
	long int time_now;
	mt19937 generator;
	uniform_real_distribution<double> distribution;

	double MT_random();
	
};
	

#endif
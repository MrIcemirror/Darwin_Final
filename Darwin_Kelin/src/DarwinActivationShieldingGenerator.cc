#include "DarwinActivationShieldingGenerator.hh"

#include <cmath>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <cstdlib>

using std::stringstream;
using std::vector;
using namespace std;

#include "G4Event.hh"
#include <random>
#include <ctime>
#include "Randomize.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"

DarwinActivationShieldingGenerator::
    DarwinActivationShieldingGenerator(G4double world_length_cc,
                                       G4double gen_radius_cc,
									   std::vector<G4double> upper_cc, 
									   std::vector<G4double> lower_cc,
									   std::vector<G4double> flux_prob_cc,
                                       G4String sphere_cc,
                                       G4String file_name_cc,
                                       G4double gen_z_cc = 0):
    world_length(world_length_cc),gen_radius(gen_radius_cc),
        upper(upper_cc),lower(lower_cc),flux_prob(flux_prob_cc)
{
    gen_z = gen_z_cc;
    time_now = time(NULL);
    generator = mt19937(time_now);
    distribution = uniform_real_distribution<double>(0.0,1.0);
    sphere = sphere_cc;
    file_name = file_name_cc;
    fParticleGun = new G4ParticleGun(1);
}
    
    

DarwinActivationShieldingGenerator::~DarwinActivationShieldingGenerator()
{
    delete fParticleGun;
}

void DarwinActivationShieldingGenerator::GeneratePrimaries(G4Event* anEvent)
{
    //initiate particle type
    G4ParticleTable *ParticleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *ParticleDefinition = ParticleTable->FindParticle("neutron");

    //initiate parameters
    G4double init_x, init_y, init_z, init_p, init_px, init_py, init_pz = 0;
    if(sphere == "Sphere_Real")
    {init_Sphere_Real_Posi_Mom(init_x,init_y,init_z,init_px,init_py,init_pz,init_p,p_type, world_length,gen_radius,upper,lower,flux_prob);}
    else if(sphere == "Sphere_Center")
    {init_Sphere_Center_Posi_Mom(init_x,init_y,init_z,init_px,init_py,init_pz,init_p,p_type, world_length,gen_radius,upper,lower,flux_prob);}
    else if(sphere == "True_Real")
    {init_True_Real_Posi_Mom(init_x,init_y,init_z,init_px,init_py,init_pz,init_p,p_type, world_length,gen_radius,upper,lower,flux_prob);}
    else if(sphere == "Clinder")
    {
        init_Real_Clin_Posi_Mom(init_x,init_y,init_z,init_px,init_py,init_pz,init_p,p_type, world_length,gen_radius,gen_z,upper,lower,flux_prob);
        }
    

    //initialize particle motion
    G4ThreeVector init_Position(init_x,init_y,init_z);
    G4ThreeVector init_MomDirec(init_px,init_py,init_pz);

    //Generate particle
    fParticleGun->SetParticlePosition(init_Position);
    fParticleGun->SetParticleMomentumDirection(init_MomDirec);
    fParticleGun->SetParticleMomentum(init_p);
    fParticleGun->SetParticleDefinition(ParticleDefinition);

    G4double primary_Ek = fParticleGun->GetParticleEnergy();
    std::fstream file(file_name, std::ios::app); 
    file << "### Primary Ek = " << primary_Ek << "  ###" << endl;
   // file << "### x = "<< init_x << "|| y = " << init_y << "|| z = " << init_z << "###" << endl;
    file.close();

    fParticleGun->GeneratePrimaryVertex(anEvent);
}



void DarwinActivationShieldingGenerator::
     init_Sphere_Real_Posi_Mom(G4double& init_x,G4double& init_y,G4double& init_z,
				   G4double& init_px,G4double& init_py,G4double& init_pz,G4double& init_p, 
                   G4String p_type, G4double world_length, G4double gen_radius,
                   std::vector<G4double> upper,
                   std::vector<G4double> lower,
                   std::vector<G4double> flux_prob)
{
    //initial radius of position sphere
    //G4double deltaR = 2.*m;
    G4double R = 1.00*gen_radius;

    Marsaglia(init_x,init_y,init_z);

    G4double init_x0 = -init_x;
    G4double init_y0 = -init_y;
    G4double init_z0 = -init_z;

    init_x = init_x*R;
    init_y = init_y*R;
    init_z = init_z*R;
    
    //initial momentum value
    G4int data_size = upper.size();
    G4double momentum_prob = MT_random();
    G4int band_number;
    for(G4int i=0; i<data_size;i++)
    {
        if(momentum_prob<=flux_prob[i]){band_number=i;break;}
        else{continue;}
    }
    G4double Ek = 20*MT_random()*MeV;
    init_p = sqrt(2.*Ek*neutron_mass_c2);
    
    //initial momentum direction
    //semi-sphere defined by the position vector (pv):
    //use the end point of pv as the center point and start point as the top point to generate a semi-sphere
    while(true)
    {

        Marsaglia(init_px,init_py,init_pz);
        G4double cond = init_x0*init_px+init_y0*init_py+init_z0*init_pz;
            //G4cout << ptheta << " "<< ppsi<< " " <<  cond <<std::endl;
            //G4cout << init_x0 << " " << init_y0 << " " << init_z0 << " " <<init_px << " " << init_py <<" "<<init_pz << endl;
        if(cond>=0)
        {
            G4double mR = sqrt(init_px*init_px+init_py*init_py+init_pz*init_pz);
            init_px = init_px/mR;
            init_py = init_py/mR;
            init_pz = init_pz/mR;    
            break;
        }
        
    } 
}

void DarwinActivationShieldingGenerator::
     init_Sphere_Center_Posi_Mom(G4double& init_x,G4double& init_y,G4double& init_z,
				   G4double& init_px,G4double& init_py,G4double& init_pz,G4double& init_p, 
                   G4String p_type, G4double world_length, G4double gen_radius,
                   std::vector<G4double> upper,
                   std::vector<G4double> lower,
                   std::vector<G4double> flux_prob)
{
    //initial radius of position sphere
    //G4double deltaR = 2.*m;
    G4double R = 1.00*gen_radius;

    //initial exact emission location on sphere
    Marsaglia(init_x,init_y,init_z);

    G4double init_x0 = -init_x;
    G4double init_y0 = -init_y;
    G4double init_z0 = -init_z;

    init_x = init_x*R;
    init_y = init_y*R;
    init_z = init_z*R;
    
    //initial momentum value
    G4int data_size = upper.size();
    G4double momentum_prob = MT_random();
    G4int band_number;
    for(G4int i=0; i<data_size;i++)
    {
        if(momentum_prob<=flux_prob[i]){band_number=i;break;}
        else{continue;}
    }
    G4double Ek = 20*MT_random()*MeV;
    init_p = sqrt(2.*Ek*neutron_mass_c2);
    
    //initial momentum direction
    //semi-sphere defined by the position vector (pv):
    //use the end point of pv as the center point and start point as the top point to generate a semi-sphere
    init_px = init_x0;
    init_py = init_y0;
    init_pz = init_z0;
}

void DarwinActivationShieldingGenerator::
     init_True_Real_Posi_Mom(G4double& init_x,G4double& init_y,G4double& init_z,
				   G4double& init_px,G4double& init_py,G4double& init_pz,G4double& init_p, 
                   G4String p_type, G4double world_length, G4double gen_radius,
                   std::vector<G4double> upper,
                   std::vector<G4double> lower,
                   std::vector<G4double> flux_prob)
{
    //initial radius of position sphere
    //G4double deltaR = 2.*m;
    G4double R = 1.00*gen_radius;

    //initial exact emission location on sphere
    Marsaglia(init_x,init_y,init_z);
    //if(init_z<0){init_z = -init_z;}
    

    G4double init_x0 = -init_x;
    G4double init_y0 = -init_y;
    G4double init_z0 = -init_z;

    init_x = init_x*R;
    init_y = init_y*R;
    init_z = init_z*R;
    
    //initial momentum value
    G4int data_size = upper.size();
    G4double momentum_prob = MT_random();
    G4int band_number;
    for(G4int i=0; i<data_size;i++)
    {
        if(momentum_prob<=flux_prob[i]){band_number=i;break;}
        else{continue;}
    }
    G4double Ek = (lower[band_number]+(upper[band_number]-lower[band_number])*MT_random())*MeV;
    init_p = sqrt(2.*Ek*neutron_mass_c2);
    
    //initial momentum direction
    //semi-sphere defined by the position vector (pv):
    //use the end point of pv as the center point and start point as the top point to generate a semi-sphere
    while(true)
    {
        Marsaglia(init_px,init_py,init_pz);
        G4double mR = sqrt(init_px*init_px+init_py*init_py+init_pz*init_pz);
        init_px = init_px/mR;
        init_py = init_py/mR;
        init_pz = init_pz/mR;    

        G4double cond = init_x0*init_px+init_y0*init_py+init_z0*init_pz;
            //G4cout << ptheta << " "<< ppsi<< " " <<  cond <<std::endl;
            //G4cout << init_x0 << " " << init_y0 << " " << init_z0 << " " <<init_px << " " << init_py <<" "<<init_pz << endl;
        if(cond>=0)
        {
            break;
        }
        
    } 
    /*
    G4cout << "X = " << init_x0 << "  "
           << "Y = " << init_y0 << "  "
           << "Z = " << init_z0 << "  " << endl
           << "pX = " << init_px << "  "
           << "pY = " << init_py << "  " 
           << "pZ = " << init_pz << "  "
           << "cond = " << init_x0*init_px+init_y0*init_py+init_z0*init_pz
           <<endl;*/
}

void DarwinActivationShieldingGenerator::
    init_Real_Clin_Posi_Mom(G4double& init_x,G4double& init_y,G4double& init_z,
                    G4double& init_px,G4double& init_py,G4double& init_pz,
                    G4double& init_p, G4String p_type, G4double world_length,
                    G4double gen_radius, G4double gen_z,
                    std::vector<G4double> upper,
                    std::vector<G4double> lower,
                    std::vector<G4double> flux_prob)
{
    G4double R0 = gen_radius;
    G4double z0 = gen_z;

    G4double bottom = R0*R0*pi;
    G4double circle = 2*pi*R0;
    G4double side = circle*z0;

    G4double on_side = side/(side+2*bottom);

    G4double posi_prob = MT_random();
    G4double theta = 2*pi*MT_random();
    if(posi_prob<on_side)
    {
        init_z = (2*MT_random()-1)*z0;
        init_x = cos(theta)*R0;
        init_y = sin(theta)*R0;
    }
    else
    {
        G4double sign = MT_random();
        if(sign<0.5){sign = 1.;}
        else{sign = -1.;}
        init_z = sign*z0;

        G4double Ri = sqrt(MT_random())*R0;
        init_x = cos(theta)*Ri;
        init_y = sin(theta)*Ri;
    }

    G4double Rp = sqrt(init_x*init_x+init_y*init_y+init_z*init_z);
    G4double init_x0 = -init_x/Rp;
    G4double init_y0 = -init_y/Rp;
    G4double init_z0 = -init_z/Rp;

    //initial momentum value
    G4int data_size = upper.size();
    G4double mon_prob = MT_random();
    G4int band_number = 0;
    for (int i=0;i<data_size;i++)
    {
        if(mon_prob<=flux_prob[i])
        {
            band_number = i;
            break;
        }
        else{continue;}
    }
    G4double Ek = lower[band_number]+(upper[band_number]-lower[band_number])*MT_random();
    init_p = sqrt(2.*Ek*neutron_mass_c2);
    
    //initial momentum direction
    //semi-sphere defined by the position vector (pv):
    //use the end point of pv as the center point and start point as the top point to generate a semi-sphere
    while(true)
    {
        Marsaglia(init_px,init_py,init_pz);
        G4double mR = sqrt(init_px*init_px+init_py*init_py+init_pz*init_pz);
        init_px = init_px/mR;
        init_py = init_py/mR;
        init_pz = init_pz/mR;    

        G4double cond = init_x0*init_px+init_y0*init_py+init_z0*init_pz;
            //G4cout << ptheta << " "<< ppsi<< " " <<  cond <<std::endl;
            //G4cout << init_x0 << " " << init_y0 << " " << init_z0 << " " <<init_px << " " << init_py <<" "<<init_pz << endl;
        if(cond>=0)
        {
            break;
        }
        
    } 

}

void DarwinActivationShieldingGenerator::
     Marsaglia(G4double &x, G4double &y, G4double &z)
{
        
    while(true)
    {
        u = 2*MT_random()-1;
        v = 2*MT_random()-1;
        if(u*u+v*v<=1){break;}
    }
    r0 = u*u+v*v;
    x = 2*u*sqrt(1-r0);
    y = 2*v*sqrt(1-r0);
    z = 1-2*r0;
}

double DarwinActivationShieldingGenerator::MT_random()
{
    return distribution(generator);
}
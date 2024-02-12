#include "Darwin_PS_Generator_Cylinder.hh"

#include <cmath>
#include <iostream>
#include <ctime>
#include "Randomize.hh"

using namespace std;

#include "G4Event.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"

Darwin_PS_Generator_Cylinder::
    Darwin_PS_Generator_Cylinder(G4double gen_radius_cc, G4double gen_z_cc,
                               std::vector<G4double> upper_cc,
                               std::vector<G4double> lower_cc,
                               std::vector<G4double> flux_prob_cc)
{
    //init parameters
    gen_radius = gen_radius_cc;
    gen_z = gen_z_cc;

    upper = upper_cc;
    lower = lower_cc;
    flux_prob = flux_prob_cc;

    init_x = init_y = init_z = 0;
    init_px = init_py = init_pz = 0;

    Ek = 0;

    //init random generator
    time_now = time(NULL);
    generator = mt19937(time_now);
    distribution = uniform_real_distribution<double> (0.0,1.0);

    fParticleGun = new G4ParticleGun(1);
}

Darwin_PS_Generator_Cylinder::~Darwin_PS_Generator_Cylinder()
{
    delete fParticleGun;
}

void Darwin_PS_Generator_Cylinder::GeneratePrimaries(G4Event* anEvent)
{
    //initiate particle type
    G4ParticleTable *ParticleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *ParticleDefinition = ParticleTable->FindParticle("neutron");
    
    //init position and momentum direction
    init(init_x,init_y,init_z,init_px,init_py,init_pz,gen_radius);
    Ek = init_Ek(upper,lower,flux_prob);

    std::fstream file("../GenTest.dat",std::ios::app);
    file << init_x << " " << init_y << " " << init_z << " "
         << init_px << " " << init_py << " " << init_pz << " "
         << Ek << endl;
    file.close();

    init_position = G4ThreeVector(init_x, init_y, init_z );
    init_MomDirec = G4ThreeVector(init_px,init_py,init_pz);

    //Generate Particle
    fParticleGun->SetParticleDefinition(ParticleDefinition);
    fParticleGun->SetParticlePosition(init_position);
    fParticleGun->SetParticleMomentumDirection(init_MomDirec);
    fParticleGun->SetParticleEnergy(Ek);

    fParticleGun->GeneratePrimaryVertex(anEvent);
}

void Darwin_PS_Generator_Cylinder::
    init(G4double &init_x,  G4double &init_y,  G4double &init_z,
         G4double &init_px, G4double &init_py, G4double &init_pz,
         G4double gen_radius)
{
    //init random position on the cylinder
    Cylinder(init_x,init_y,init_z,gen_radius,gen_z);    
    //init random momentum direction
    while(true)
    {
        Marsaglia(init_px,init_py,init_pz,1.);
        G4double condtion = init_x*init_px+init_y*init_py+init_z*init_pz;

        if(condtion<=0){break;}     //opposite direction to position vector
    }
}

G4double Darwin_PS_Generator_Cylinder::
    init_Ek(std::vector<G4double> upper,
			std::vector<G4double> lower,
			std::vector<G4double> flux_prob)
{
    G4int data_size = upper.size();
    G4double momentum_prob = rand();
    G4int band_number;

    for(G4int i=0; i<data_size; i++)
    {
        if(momentum_prob<=flux_prob[i]){band_number=i;break;}
        else{continue;}
    }

    G4double Ek0 = (lower[band_number]+(upper[band_number]-lower[band_number])*rand())*MeV;
    return Ek0;
}

void Darwin_PS_Generator_Cylinder::
    Marsaglia(G4double &x, G4double &y, G4double &z, G4double R)
{
    G4double u,v,r0;
    while(true)
    {
        u = 2*rand()-1;
        v = 2*rand()-1;
        if(u*u+v*v<=1){break;}
    }
    r0 = u*u+v*v;
    x = 2*u*sqrt(1-r0)*R;
    y = 2*v*sqrt(1-r0)*R;
    z = (1-2*r0)*R;
}

void Darwin_PS_Generator_Cylinder::
    Cylinder(G4double &x, G4double &y, G4double &z, G4double R, G4double z0)
{
    G4double circle_area = pi*R*R;
    G4double side_area = 2*pi*R*2*z0;               //z0 is half length
    G4double tot_area = 2*circle_area+side_area;
    G4double side_prob = side_area/tot_area;

    G4double prob = rand();
    G4double theta = rand()*2*pi;

    if(prob<=side_prob)
    {
        z = (2*rand()-1)*z0;
        x = cos(theta)*R;
        y = sin(theta)*R;
    }

    else
    {
        G4double sign = rand();
        if(sign<0.5){sign = -1.;}
        else{sign=1.;}

        z = z0*sign;
        G4double Ri = sqrt(rand())*R;        //flat distribution on the circle surface
        x = cos(theta)*Ri;
        y = sin(theta)*Ri;
    }
}

G4double Darwin_PS_Generator_Cylinder::rand()
{
    return distribution(generator);
}

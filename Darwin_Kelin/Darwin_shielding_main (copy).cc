#include <iostream>
#include <ctime>
#include <sstream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4PhysicalConstants.hh"

#include "DarwinActivationShieldingPhysicsList.hh"
#include "DarwinActivationShieldingConstruct.hh"
#include "DarwinActivationShieldingMaterials.hh"
#include "DarwinActivationShieldingGenerator.hh"
#include "DarwinActivationShieldingAnalyzeManager.hh"
#include "DarwinActivationShieldingDecayAction.hh"

using namespace std;

int main(int argc, char** argv)
{
	G4double world_length = 3.*m;
	G4String p_type = "mono";
	G4String shielding_material = "Water";
	G4double shielding_thickness = 2.*mm;
	G4double gen_radius = 1.5*m;
	G4String file_output = "../results/Activation_Water_2000mm_25000_24-01-19 03:08:46 PM.txt";
	G4int test_number = 5000;
	G4String sphere = "Sphere_Center";		//"Sphere_Real""Sphere_Center""True_Real"

	std::vector<G4double> upper,lower,flux_prob;
	if(p_type=="mono")      //flat spectrum
    {
        lower.push_back(0.);
		upper.push_back(20.);
		flux_prob.push_back(1.);
    }

    else if(p_type=="spec")
    {
        std::ifstream spectrum("../neutron_spectrum");
        if(spectrum.is_open())
        {
            G4double value;
            for (int i=0;i<3;i++)
            {
                std::string line;
                getline(spectrum,line);
                std::stringstream ss(line);

                while(ss>>value)
                {
                    if(i==1){upper.push_back(value);}
                    else if(i==0){lower.push_back(value);}
                    else{flux_prob.push_back(value);}
                }
            }
        }
        else
        {
            cerr << "Error: Neutron Spectrum File Is Incorrect"<<endl;
            cerr << "Terminating the program. "<< endl;
            exit(1);
        }
    }

    G4RunManager *runManager = new G4RunManager();
	G4VUserDetectorConstruction *Construction = 
		new DarwinActivationShieldingConstruct(world_length,shielding_material,shielding_thickness);
	Construction->Construct();

	runManager->SetUserInitialization(Construction);
    runManager->SetUserInitialization(new DarwinActivationShieldingPhysicsList);

	G4VUserPrimaryGeneratorAction *Action = new DarwinActivationShieldingGenerator(world_length,gen_radius,upper,lower,flux_prob,sphere,file_output);
	runManager->SetUserAction(Action);

	DarwinActivationShieldingAnalyzeManager * analysis = new DarwinActivationShieldingAnalyzeManager(file_output);
	DarwinActivationShieldingDecayAction * stepping = new DarwinActivationShieldingDecayAction(analysis,file_output);

	runManager->SetUserAction(stepping);

	//runManager->SetUserInitialization(new DarwinActivationShieldingAction_init(LXe_cube_length,p_type));
    runManager->Initialize();

	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	G4bool visual = false;
	//Geometry test
	if(visual)
	{
		G4UIExecutive *ui = new G4UIExecutive(argc, argv);
		
		G4VisManager *visManager = new G4VisExecutive();
		visManager->Initialize();
		UImanager->ApplyCommand("/process/had/enableCRCoalescence true");
		UImanager->ApplyCommand("/vis/open OGL");
		UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 0 0");
		UImanager->ApplyCommand("/vis/drawVolume");
		UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
		UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
		ui->SessionStart();
	}
	
	else{
	std::fstream file(file_output, std::ios::app); 
	for(int i=1;i<=test_number;i++)
	{
		G4cout << "-------------------" << i << "-------------------" << endl;
		file << "-----------------START "<< i <<"-----------------" << endl;
		UImanager->ApplyCommand("/run/beamOn 1");
		file << "----------------- END  "<< i <<"-----------------" << endl;
	}}

	/*
	delete runManager;
	delete stepping;
	delete analysis;
	delete Action;
	delete Construction;
	*/
	
    return 0;
}

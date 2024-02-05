#ifndef DarwinActivationShieldingAnalyzeManager_HH
#define DarwinActivationShieldingAnalyzeManager_HH

#include "globals.hh"
#include "G4AnalysisManager.hh"

const G4int maxcol = 13;

class DarwinActivationShieldingAnalyzeManager
{
    public:
        DarwinActivationShieldingAnalyzeManager(G4String file_name_cc);
        ~DarwinActivationShieldingAnalyzeManager();

        void book();
        void track_information(G4int track_id, G4int step_id);
        void particle_information(const G4String & particle_name, G4double mass, G4int charge, G4double Ek);
        void product_information(const G4String & particle_name,const G4String & process_name, const G4String & second_particle_name,
                                 G4int atomic_number,G4int mass_number , G4int charge, G4double Ek);
        void close();

    private:
        G4bool factoryOn;
        G4String file_name;
        G4int fNtcolid[maxcol];
        //G4AnalysisManager * manager;
};

#endif
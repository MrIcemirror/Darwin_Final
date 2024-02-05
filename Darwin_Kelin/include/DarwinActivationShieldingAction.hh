#ifndef DarwinActivationShieldingAction_HH
#define DarwinActivationShieldingAction_HH

#include "G4VUserActionInitialization.hh"
#include "DarwinActivationShieldingGenerator.hh"
#include "DarwinActivationShieldingAnalyzeManager.hh"

class DarwinActivationShieldingAction_init:
public G4VUserActionInitialization
{
    public:
        DarwinActivationShieldingAction_init(G4double world_length_cc,
                                             G4double gen_radius_cc,
                                             std::vector<G4double> upper_cc,
                                             std::vector<G4double> lower_cc,
                                             std::vector<G4double> flux_prob_cc,
                                             DarwinActivationShieldingAnalyzeManager* analysis_cc,
                                             G4String file_output_cc,
                                             G4String sphere_cc,
                                             G4double gen_z_cc);
        ~DarwinActivationShieldingAction_init();


    private:
        G4double world_length, gen_radius, gen_z;
        //G4String p_type;
        std::vector<G4double> upper,lower,flux_prob;
        void Build(G4double world_length,G4double gen_radius,std::vector<G4double> upper,
                   std::vector<G4double> lower,std::vector<G4double> flux_prob) const;
        DarwinActivationShieldingAnalyzeManager* analysis;
        G4String file_output;
        G4String sphere;
};

#endif
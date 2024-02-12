#include "Darwin_PS_PhysicsList.hh"

//physics list
#include "FTFP_BERT.hh"
#include "G4HadronPhysicsFTFP_BERT_HP.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronPhysicsShielding.hh"

#include "G4IonElasticPhysics.hh"
#include "G4IonPhysics.hh"

#include "G4DecayPhysics.hh"
#include "G4LossTableManager.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4StoppingPhysics.hh"

#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"



Darwin_PS_PhysicsList::Darwin_PS_PhysicsList():G4VModularPhysicsList()
{
    verboseLevel = 0;
    //Loss table
    G4LossTableManager::Instance();

    //Em physics 
    RegisterPhysics(new G4EmStandardPhysics(verboseLevel));
    RegisterPhysics(new G4EmExtraPhysics(verboseLevel));

    //Hadronic process
    RegisterPhysics(new G4HadronPhysicsFTFP_BERT_HP(verboseLevel));
    RegisterPhysics(new G4HadronElasticPhysicsHP(verboseLevel));
    RegisterPhysics(new G4HadronPhysicsShielding(verboseLevel));

    //Ionic Process
    RegisterPhysics(new G4IonElasticPhysics(verboseLevel));
    RegisterPhysics(new G4IonPhysics(verboseLevel));

    //Decay physics
    RegisterPhysics(new G4DecayPhysics(verboseLevel));
    RegisterPhysics(new G4RadioactiveDecayPhysics(verboseLevel));

    RegisterPhysics(new G4StoppingPhysics(verboseLevel));
}
Darwin_PS_PhysicsList::~Darwin_PS_PhysicsList(){}
#ifndef DarwinActivationShieldingPhysicsList_HH
#define DarwinActivationShieldingPhysicsList_HH

#include "G4VModularPhysicsList.hh"

class DarwinActivationShieldingPhysicsList : 
public G4VModularPhysicsList
{
    public:
        DarwinActivationShieldingPhysicsList();
        ~DarwinActivationShieldingPhysicsList();

    private:
        G4VPhysicsConstructor *emPhysicsList;
        G4VPhysicsConstructor *decPhysicsList;
        G4VModularPhysicsList *hadronPhy;
};

#endif
#ifndef Darwin_PS_PhysicsList_HH
#define Darwin_PS_PhysicsList_HH

#include "G4VModularPhysicsList.hh"

class Darwin_PS_PhysicsList : 
public G4VModularPhysicsList
{
    public:
        Darwin_PS_PhysicsList();
        ~Darwin_PS_PhysicsList();

    private:
        G4VPhysicsConstructor *emPhysicsList;
        G4VPhysicsConstructor *decPhysicsList;
        G4VModularPhysicsList *hadronPhy;
};

#endif
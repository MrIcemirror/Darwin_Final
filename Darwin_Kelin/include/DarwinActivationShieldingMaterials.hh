#ifndef DarwinActivationShieldingMaterials_HH
#define DarwinActivationShieldingMaterials_HH

#include "TDirectory.h"
#include "TFile.h"

class DarwinActivationShieldingMaterials
{
    public:
        DarwinActivationShieldingMaterials();
        ~DarwinActivationShieldingMaterials();

        void DefineMaterials();

   // private:
      //  G4Material *LXe, *Vacuum, *Water;
};

#endif
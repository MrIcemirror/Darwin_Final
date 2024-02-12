#ifndef DarwinActivation_PS_Materials_HH
#define DarwinActivation_PS_Materials_HH

#include "TDirectory.h"
#include "TFile.h"

class DarwinActivation_PS_Materials
{
    public:
        DarwinActivation_PS_Materials();
        ~DarwinActivation_PS_Materials();

        void DefineMaterials();

   // private:
      //  G4Material *LXe, *Vacuum, *Water;
};

#endif
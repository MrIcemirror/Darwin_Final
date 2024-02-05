#ifndef DarwinActivationShieldingConstruction_HH
#define DarwinActivationShieldingConstruction_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"

#include "DarwinActivationShieldingMaterials.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class DarwinActivationShieldingConstruct : 
public G4VUserDetectorConstruction
{
    public:
        DarwinActivationShieldingConstruct(G4double world_length_cc,G4String shielding_material_name_cc,G4double thickness_cc);
        ~DarwinActivationShieldingConstruct();

        virtual G4VPhysicalVolume* Construct();
    
    private:
    //Solid Volume
        G4Box *solid_world;
        G4Tubs *solid_LXe_pipe, *solid_inner_Spipe, *solid_center_Vpipe, *solid_outer_Spipe, *solid_shield_pipe;
    //Logical Volume
        G4LogicalVolume *logical_world;
        G4LogicalVolume *logical_LXe_pipe, *logical_inner_Spipe, *logical_center_Vpipe, *logical_outer_Spipe, *logical_shield_pipe;
    //physical Volume
        G4VPhysicalVolume *phys_world;
        G4VPhysicalVolume *phys_LXe_pipe, *phys_inner_Spipe, *phys_center_Vpipe, *phys_outer_Spipe, *phys_shield_pipe;
    //Material
        G4Material *LXe, *Vacuum, *Air, *SS304Steel, *shielding_material;
        DarwinActivationShieldingMaterials* Materials;

    //pass in parameters
        G4double world_length, thickness;
        G4String shielding_material_name;

        virtual void ConstructSDandField();     //sensitive
        //virtual void shielding_ConstructSDandField();
};

#endif
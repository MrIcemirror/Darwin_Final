#ifndef Darwin_PS_Construction_HH
#define Darwin_PS_Construction_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"

#include "Darwin_PS_Materials.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class Darwin_PS_Construction :
public G4VUserDetectorConstruction
{
    public:
        Darwin_PS_Construction(G4double world_length_cc,G4String shielding_material_name_cc,G4double shielding_thickness_cc);
        ~Darwin_PS_Construction();

        virtual G4VPhysicalVolume* Construct();
    
    private:
        //Material defination
        DarwinActivation_PS_Materials *Materials;
        G4Material *LXe, *Vacuum, *Air, *SS304;

        //World defination
        G4double world_length;
        G4Box *solid_world;
        G4LogicalVolume *logical_world;
        G4VPhysicalVolume *phys_world;

        //Define Unchangable system construction;
        G4double ss1_thickness, vacuum_thickness,ss2_thickness;
        G4double zer_radius,LXe_radius,ss1_radius,vac_radius,ss2_radius,tot_radius,shielding_radius;
        G4double pipe_length;

        G4Tubs *solid_Center_LXe, *solid_ss_layer1, *solid_vacuum_pipe, *solid_ss_layer2;
        G4LogicalVolume *logical_Center_LXe, *logical_ss_layer1, *logical_vacuum_pipe, *logical_ss_layer2;
        G4VPhysicalVolume *phys_Center_LXe, *phys_ss_layer1, *phys_vacuum_pipe, *phys_ss_layer2;

        //Define shielding layer;
        G4Material *shielding_material;
        G4String shielding_material_name;
        G4double shielding_thickness;

        G4Tubs *solid_shielding_layer;
        G4LogicalVolume *logical_shielding_layer;
        G4VPhysicalVolume *phys_shielding_layer;

        //set sensitive volume
        void ConstructSDandField();

};

#endif
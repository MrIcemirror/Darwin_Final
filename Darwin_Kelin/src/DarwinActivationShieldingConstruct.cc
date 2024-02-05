#include "DarwinActivationShieldingConstruct.hh"
#include "DarwinActivationShieldingMaterials.hh"

#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"

using namespace std;
DarwinActivationShieldingConstruct::DarwinActivationShieldingConstruct
    (G4double world_length_cc,G4String shielding_material_name_cc,G4double thickness_cc)
{
    world_length = world_length_cc;
    shielding_material_name = shielding_material_name_cc;
    thickness = thickness_cc;
}

DarwinActivationShieldingConstruct::~DarwinActivationShieldingConstruct(){}

G4VPhysicalVolume* DarwinActivationShieldingConstruct::Construct()
{
    //define materials
    Materials = new DarwinActivationShieldingMaterials();
    Materials->DefineMaterials();
    LXe = G4Material::GetMaterial("LXe");
    Vacuum = G4Material::GetMaterial("Vacuum");
    Air = G4Material::GetMaterial("G4_AIR");
    SS304Steel = G4Material::GetMaterial("SS304Steel");
    shielding_material = G4Material::GetMaterial(shielding_material_name);

    G4ThreeVector zero_position = G4ThreeVector(0., 0., 0.);
    G4RotationMatrix* rotaion = new G4RotationMatrix(0.,0.*deg,0.);
    //world construction
    solid_world = new G4Box("solid_world",world_length,world_length,world_length);
    logical_world = new G4LogicalVolume(solid_world,Air,"logical_world");
    phys_world = new G4PVPlacement(0,zero_position,logical_world,"phys_world",0,false,0);

    G4ThreeVector pipe_position = G4ThreeVector(0., 0., 0.);
    G4double Xe_radius = 5*mm;
    G4double steel_thickness = 2*mm;
    G4double vacuum_thickness = 3*mm;
    //LXe pipe
    solid_LXe_pipe = new G4Tubs("solid_LXe_pipe",0,Xe_radius,1.*m,0.,360*deg);
    logical_LXe_pipe = new G4LogicalVolume(solid_LXe_pipe,LXe,"logical_LXe_pipe");
    phys_LXe_pipe = new G4PVPlacement(rotaion,pipe_position,logical_LXe_pipe,"phys_LXe_pipe",logical_world,false,0);

    //inner steel pipe
    solid_inner_Spipe = new G4Tubs("solid_inner_Spipe",Xe_radius,Xe_radius+steel_thickness,1.*m,0.,360*deg);
    logical_inner_Spipe = new G4LogicalVolume(solid_inner_Spipe,SS304Steel,"logical_inner_Spipe");
    phys_inner_Spipe = new G4PVPlacement(rotaion,pipe_position,logical_inner_Spipe,"phys_inner_Spipe",logical_world,false,0);

    //center vacuum pipe
    solid_center_Vpipe = new G4Tubs("solid_center_Vpipe",Xe_radius+steel_thickness,Xe_radius+steel_thickness+vacuum_thickness,1.*m,0.,360*deg);
    logical_center_Vpipe = new G4LogicalVolume(solid_center_Vpipe,Vacuum,"logical_center_Vpipe");
    phys_center_Vpipe = new G4PVPlacement(rotaion,pipe_position,logical_center_Vpipe,"phys_center_Vpipe",logical_world,false,0);

    //outer steel pipe
    solid_outer_Spipe = new G4Tubs("solid_outer_Spipe",Xe_radius+steel_thickness+vacuum_thickness,
                                                       Xe_radius+2*steel_thickness+vacuum_thickness,1.*m,0.,360*deg);
    logical_outer_Spipe = new G4LogicalVolume(solid_outer_Spipe,SS304Steel,"logical_outer_Spipe");
    phys_outer_Spipe = new G4PVPlacement(rotaion,pipe_position,logical_outer_Spipe,"phys_outer_Spipe",logical_world,false,0);

    //Shielding pipe
    solid_shield_pipe = new G4Tubs("solid_shield_pipe",Xe_radius+2*steel_thickness+vacuum_thickness,
                                                       Xe_radius+2*steel_thickness+vacuum_thickness+thickness,1.*m,0.,360*deg);
    logical_shield_pipe = new G4LogicalVolume(solid_shield_pipe,shielding_material,"logical_shield_pipe");
    phys_shield_pipe = new G4PVPlacement(rotaion,pipe_position,logical_shield_pipe,"phys_shield_pipe",logical_world,false,0);

    
    return phys_world;
}

void DarwinActivationShieldingConstruct::ConstructSDandField()
{}

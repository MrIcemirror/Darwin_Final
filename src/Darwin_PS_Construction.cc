#include "Darwin_PS_Materials.hh"
#include "Darwin_PS_Construction.hh"

#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"

using namespace std;

Darwin_PS_Construction::Darwin_PS_Construction
    (G4double world_length_cc,G4String shielding_material_name_cc,G4double shielding_thickness_cc)
{
    world_length = world_length_cc;
    shielding_material_name = shielding_material_name_cc;
    shielding_thickness = shielding_thickness_cc;
}

Darwin_PS_Construction::~Darwin_PS_Construction(){}

G4VPhysicalVolume* Darwin_PS_Construction::Construct()
{
    //Define materials
    Materials = new DarwinActivation_PS_Materials();
    Materials->DefineMaterials();
    LXe = G4Material::GetMaterial("LXe");
    Vacuum = G4Material::GetMaterial("Vacuum");
    Air = G4Material::GetMaterial("G4_AIR");
    SS304 = G4Material::GetMaterial("SS304Steel");
    shielding_material = G4Material::GetMaterial(shielding_material_name);

    //World definition
    G4ThreeVector zero_position = G4ThreeVector(0., 0., 0.);
    solid_world = new G4Box("solid_world",world_length,world_length,world_length);
    logical_world = new G4LogicalVolume(solid_world,Air,"logical_world");
    phys_world = new G4PVPlacement(0,zero_position,logical_world,"phys_world",0,false,0);

    //--------------------------Define Unchangable system construction-----------------------
    pipe_length = 1.*m;         //half length of the pipe
    zer_radius = 0.;
    LXe_radius = 19.05/2*mm;    //center LXe tube outer radius
    tot_radius = 76.7/2*mm;   //total structure pipe outer radius

    ss1_thickness = 1.25*mm;    //first layer stainless steel thickness
    ss2_thickness = 2.*mm;      //second layer stainless steel thickness
    //vacuum layer thickness
    vacuum_thickness = tot_radius-LXe_radius-ss1_thickness-ss2_thickness;

    ss1_radius = LXe_radius+ss1_thickness;          //first layer outer radius
    vac_radius = ss1_radius+vacuum_thickness;    //vaccum outer radius
    ss2_radius = vac_radius+ss2_thickness;       //second layer outer radius

    //init position and rotation value
    G4ThreeVector pipe_position = G4ThreeVector(0.,0.,0.);
    G4RotationMatrix* pipe_rotation = new G4RotationMatrix(0.,0.,0.);

    //Center LXe pipe
    solid_Center_LXe = new G4Tubs("solid_Center_LXe",zer_radius,LXe_radius,pipe_length,0.,360.*deg);
    logical_Center_LXe = new G4LogicalVolume(solid_Center_LXe,LXe,"logical_Center_LXe");
    phys_Center_LXe = new G4PVPlacement(pipe_rotation,pipe_position,logical_Center_LXe,"phys_Center_LXe",logical_world,false,0);

    //1st layer stell pipe
    solid_ss_layer1 = new G4Tubs("solid_ss_layer1",LXe_radius,ss1_radius,pipe_length,0.,360.*deg);
    logical_ss_layer1 = new G4LogicalVolume(solid_ss_layer1,SS304,"logical_ss_layer1");
    phys_ss_layer1 = new G4PVPlacement(pipe_rotation,pipe_position,logical_ss_layer1,"phys_ss_layer1",logical_world,false,0);

    //vacuum layer
    solid_vacuum_pipe = new G4Tubs("solid_vacuum_pipe",ss1_radius,vac_radius,pipe_length,0.,360.*deg);
    logical_vacuum_pipe = new G4LogicalVolume(solid_vacuum_pipe,Vacuum,"logical_vacuum_pipe");
    phys_ss_layer1 = new G4PVPlacement(pipe_rotation,pipe_position,logical_vacuum_pipe,"phys_ss_layer1",logical_world,false,0);

    //2nd layer stell pipe
    solid_ss_layer2 = new G4Tubs("solid_ss_layer2",vac_radius,ss2_radius,pipe_length,0.,360.*deg);
    logical_ss_layer2 = new G4LogicalVolume(solid_ss_layer2,SS304,"logical_ss_layer2");
    phys_ss_layer2 = new G4PVPlacement(pipe_rotation,pipe_position,logical_ss_layer2,"phys_ss_layer2",logical_world,false,0);

    //-------------------------------------shielding part---------------------------------------------
    shielding_radius = ss2_radius+shielding_thickness;
    solid_shielding_layer = new G4Tubs("solid_shielding_layer",ss2_radius,shielding_radius,pipe_length,0.,360.*deg);
    logical_shielding_layer = new G4LogicalVolume(solid_shielding_layer,shielding_material,"logical_shielding_layer");
    phys_shielding_layer = new G4PVPlacement(pipe_rotation,pipe_position,logical_shielding_layer,"phys_shielding_layer",logical_world,false,0);

    return phys_world;
};

void Darwin_PS_Construction::ConstructSDandField(){}
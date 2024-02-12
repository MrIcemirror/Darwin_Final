#include "Darwin_PS_Materials.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Isotope.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4Isotope.hh"

DarwinActivation_PS_Materials::DarwinActivation_PS_Materials(){}

DarwinActivation_PS_Materials::~DarwinActivation_PS_Materials(){}

void DarwinActivation_PS_Materials::DefineMaterials()
{
    G4NistManager *pNistManager = G4NistManager::Instance();

    //------------------------------Element Dinifination----------------------------
    G4Element *H = new G4Element("Hydrogen", "H", 1., 1.0079*g/mole);
    G4Element *N = new G4Element("Nitrogen", "N", 7., 14.007*g/mole);
    G4Element *O = new G4Element("Oxygen", "O", 8., 15.999*g/mole);
    G4Element *B = pNistManager->FindOrBuildElement("B");
    G4Element *C = new G4Element("Carbon","C",12., 12.000*g/mole);

    G4Element *Fe = new G4Element("Iron","Fe",26., 55.85*g/mole);
    G4Element *Cr = new G4Element("Chromium", "Cr", 24., 51.996*g/mole);
    G4Element *Ni = new G4Element("Nickel", "Ni", 28., 58.693*g/mole);
    G4Element *Mn = new G4Element("Manganese", "Mn", 25., 54.938*g/mole);
    G4Element *Si = new G4Element("Silicon", "Si", 14., 28.086*g/mole);

    const G4int iNbEntries = 3;
    //------------------------------Xenon Components---------------------------------
    G4Element *nature_Xe = new G4Element("Nature_Xenon", "Xe", 9);
    G4Isotope *Xe_124 = new G4Isotope("Xenon124", 54., 124., 124.91*g/mole); nature_Xe->AddIsotope(Xe_124, 0.0952*perCent);
    G4Isotope *Xe_126 = new G4Isotope("Xenon126", 54., 126., 125.90*g/mole); nature_Xe->AddIsotope(Xe_126, 0.0890*perCent);
    G4Isotope *Xe_128 = new G4Isotope("Xenon128", 54., 128., 127.90*g/mole); nature_Xe->AddIsotope(Xe_128,1.19102*perCent);
    G4Isotope *Xe_129 = new G4Isotope("Xenon129", 54., 129., 128.90*g/mole); nature_Xe->AddIsotope(Xe_129,26.4006*perCent);
    G4Isotope *Xe_130 = new G4Isotope("Xenon130", 54., 130., 129.90*g/mole); nature_Xe->AddIsotope(Xe_130, 4.0710*perCent);
    G4Isotope *Xe_131 = new G4Isotope("Xenon131", 54., 131., 130.91*g/mole); nature_Xe->AddIsotope(Xe_131,21.2324*perCent);
    G4Isotope *Xe_132 = new G4Isotope("Xenon132", 54., 132., 131.90*g/mole); nature_Xe->AddIsotope(Xe_132,26.9086*perCent);
    G4Isotope *Xe_134 = new G4Isotope("Xenon134", 54., 134., 133.91*g/mole); nature_Xe->AddIsotope(Xe_134,10.4357*perCent);
    G4Isotope *Xe_136 = new G4Isotope("Xenon136", 54., 136., 135.91*g/mole); nature_Xe->AddIsotope(Xe_136, 8.8573*perCent);
    
    G4Element *Xe = new G4Element("Xenon", "Xe", 54., 131.293*g/mole);
    G4Material *LXe = new G4Material("LXe", 2.85*g/cm3, 1, kStateLiquid, 168.15*kelvin, 1.5*atmosphere);
    LXe->AddElement(Xe,1);
    G4double pdLXePhotonMomentum[iNbEntries] = {6.91*eV, 6.98*eV, 7.05*eV};
    G4double pdLXeScintillation[iNbEntries] = {0.1, 1.0, 0.1};
    G4double pdLXeRefractiveIndex[iNbEntries] = {1.71, 1.69, 1.66};
    G4double pdLXeAbsorbtionLength[iNbEntries] = {100.*cm, 100.*cm, 100.*cm};
    G4double pdLXeScatteringLength[iNbEntries] = {30.*cm, 30.*cm, 30.*cm};

    G4MaterialPropertiesTable *pLXePropertiesTable = new G4MaterialPropertiesTable();
   // G4cout << "--------------------------------test---------------------------------"<<std::endl;

    //Scintillation1 ->Fast and 2->slow  for  geant4 verision <11.->>=11.
    pLXePropertiesTable->AddProperty("SCINTILLATIONCOMPONENT1", pdLXePhotonMomentum, pdLXeScintillation, iNbEntries);
    pLXePropertiesTable->AddProperty("SCINTILLATIONCOMPONENT2", pdLXePhotonMomentum, pdLXeScintillation, iNbEntries);
    pLXePropertiesTable->AddProperty("RINDEX", pdLXePhotonMomentum, pdLXeRefractiveIndex, iNbEntries);
    pLXePropertiesTable->AddProperty("ABSLENGTH", pdLXePhotonMomentum, pdLXeAbsorbtionLength, iNbEntries);
    pLXePropertiesTable->AddProperty("RAYLEIGH", pdLXePhotonMomentum, pdLXeScatteringLength, iNbEntries);

    pLXePropertiesTable->AddConstProperty("SCINTILLATIONYIELD", 0./keV);
    pLXePropertiesTable->AddConstProperty("RESOLUTIONSCALE", 0.);
    pLXePropertiesTable->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 3.*ns);
    pLXePropertiesTable->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 27.*ns);
    pLXePropertiesTable->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
    pLXePropertiesTable->AddConstProperty("SCINTILLATIONYIELD2", 1.0);

    LXe->SetMaterialPropertiesTable(pLXePropertiesTable);

    //--------------------------air----------------------------------
    G4Material *G4Air = pNistManager->FindOrBuildMaterial("G4_AIR");
    G4Material *Air = new G4Material("Air",0.00120479 *g/cm3,1,kStateGas);
    Air->AddMaterial(G4Air,1);


    //-------------------------vacuum----------------------------------
    G4Material *Vacuum = new G4Material("Vacuum", 1.e-20*g/cm3, 2, kStateGas);
    Vacuum->AddElement(N,0.755);
    Vacuum->AddElement(O,0.245);

    //-------------------------Detector vacuum----------------------------------
    G4Material *DVacuum = new G4Material("DVacuum", 1.e-20*g/cm3, 2, kStateGas);
    DVacuum->AddElement(N,0.755);
    DVacuum->AddElement(O,0.245);

    //-------------------------world vacuum----------------------------------
    G4Material *WVacuum = new G4Material("WVacuum", 1.e-20*g/cm3, 2, kStateGas);
    WVacuum->AddElement(N,0.755);
    WVacuum->AddElement(O,0.245);

    // Lead
    pNistManager->FindOrBuildMaterial("G4_Pb");
    G4Material *Lead = G4Material::GetMaterial("G4_Pb");

    // Boron
    G4Element* nature_boron = new G4Element("Nature_Boron","B",2);
    G4Isotope* B_10 = new G4Isotope("Boron_10",5.,10.,10.12*g/mole); nature_boron->AddIsotope(B_10,19.65*perCent);
    G4Isotope* B_11 = new G4Isotope("Boron_11",5.,11.,11.01*g/mole); nature_boron->AddIsotope(B_11,80.35*perCent);
    G4Material* Boron = new G4Material("Boron",2.3*g/cm3,1,kStateSolid,293.15*kelvin,1.*atmosphere);
    Boron->AddElement(nature_boron,1);

    //Gold
    pNistManager->FindOrBuildMaterial("G4_Au");
    G4Material *Gold = G4Material::GetMaterial("G4_Au");

    //---------------------------water------------------------------
    G4Material *Water = new G4Material("Water", 1.*g/cm3, 2, kStateLiquid);
    Water->AddElement(H,2);
    Water->AddElement(O,1);

    //--------------------------Plastic (POLYETHYLENE)-----------------------------
    G4Material *Polyethylene = new G4Material("Polyethylene",0.94*g/cm3,1,kStateSolid);
    G4Material *G4Polyethylene = pNistManager->FindOrBuildMaterial("G4_POLYETHYLENE");
    Polyethylene->AddMaterial(G4Polyethylene,1);

    //--------------------------PARAFFIN-------------------------------------------
    G4Material *Paraffin = new G4Material("Paraffin",0.93*g/cm3,1,kStateSolid);
    G4Material *G4Paraffin = pNistManager->FindOrBuildMaterial("G4_PARAFFIN");
    Paraffin->AddMaterial(G4Paraffin,1);

    //--------------------------NILON11--------------------------------------------
    G4Material *Nilon11 = new G4Material("Nilon11",1.425*g/cm3,kStateSolid);
    G4Material *G4Nilon11 = pNistManager->FindOrBuildMaterial("G4_NYLON-11_RILSAN");
    Nilon11->AddMaterial(G4Nilon11,1);

    //--------------------------H3BO3---------------------------------------------
    G4Material *H3BO3 = new G4Material("H3BO3",1.435*g/cm3,3,kStateSolid);
    H3BO3->AddElement(O,3);
    H3BO3->AddElement(B,1);
    H3BO3->AddElement(H,3);

    //--------------------------B4C-----------------------------------------------
    G4Material *B4C = new G4Material("B4C", 2.52*g/cm3,2,kStateSolid);
    B4C->AddElement(B,4);
    B4C->AddElement(C,1);

    //-------------------------MixDWax----------------------------------------------
    G4Material *MixDWax = new G4Material("MixDWax",0.99*g/cm3,1,kStateSolid);
    G4Material *G4MixDWax = pNistManager->FindOrBuildMaterial("G4_MIX_D_WAX");
    MixDWax->AddMaterial(G4MixDWax,1);

    //------------------------SS304Steel------------------------------------
    G4Material *SS304Steel = new G4Material("SS304Steel",8.0*g/cm3,5,kStateSolid);
    SS304Steel->AddElement(Fe,0.65);
    SS304Steel->AddElement(Cr,0.20);
    SS304Steel->AddElement(Ni,0.12);
    SS304Steel->AddElement(Mn,0.02);
    SS304Steel->AddElement(Si,0.01);

    //Borated Plastic
    G4Material *BoratedPolyethylene = new G4Material("BoratedPolyethylene",1.04*g/cm3,2,kStateSolid);
    BoratedPolyethylene->AddMaterial(Boron,5.*perCent);
    BoratedPolyethylene->AddMaterial(Polyethylene,95.*perCent);
}
#include <stdlib.h>
#include <iostream>
#include "DarwinActivationShieldingAnalyzeManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

DarwinActivationShieldingAnalyzeManager::DarwinActivationShieldingAnalyzeManager(G4String file_name_cc)
{
    //manager = G4AnalysisManager::Instance();
    factoryOn = false;
    file_name = file_name_cc;
    for (G4int i=0; i<maxcol; i++) fNtcolid[i] = 0;
}

DarwinActivationShieldingAnalyzeManager::~DarwinActivationShieldingAnalyzeManager(){}

void DarwinActivationShieldingAnalyzeManager::book()
{
    G4AnalysisManager* manager = G4AnalysisManager::Instance();
    //manager->SetNtupleDirectoryName("Activation_ntuple");

    G4bool fileopen = manager->OpenFile(file_name);
    if (!fileopen) 
    {
        G4cout << "\n---> HistoManager::book(): cannot open " 
               << file_name << G4endl;
        return;
    }
    manager->SetFirstNtupleId(1);

    //create tracking id information
    manager->CreateNtuple("101","Tracking_id_information");
    fNtcolid[0] = manager->CreateNtupleIColumn("Track_id");
    fNtcolid[1] = manager->CreateNtupleIColumn("Step_id");
    manager->FinishNtuple();

    //Dynamic particle information
    manager->CreateNtuple("102","Dynamic_Particle_Information");
    fNtcolid[2] = manager->CreateNtupleSColumn("Particle_Name");
    fNtcolid[3] = manager->CreateNtupleDColumn("Mass/MeV");
    fNtcolid[4] = manager->CreateNtupleIColumn("Charge");
    fNtcolid[5] = manager->CreateNtupleDColumn("Ek/MeV");
    manager->FinishNtuple();

    //Decay information
    manager->CreateNtuple("103","Decay&Products_Information");
    fNtcolid[6] = manager->CreateNtupleSColumn("Process_name");
    fNtcolid[7] = manager->CreateNtupleSColumn("Product_name");
    fNtcolid[8] = manager->CreateNtupleIColumn("Atomic_Number");
    fNtcolid[9] = manager->CreateNtupleIColumn("Mass_Number");
    fNtcolid[10] = manager->CreateNtupleIColumn("Charge");
    fNtcolid[11] = manager->CreateNtupleDColumn("Ek/MeV");
    manager->FinishNtuple();

    factoryOn = true;
}

void DarwinActivationShieldingAnalyzeManager::
    track_information(G4int track_id, G4int step_id)
{
    G4AnalysisManager *manager = G4AnalysisManager::Instance();
    G4cout << "Track_id" << track_id;
    manager->FillNtupleIColumn(1,fNtcolid[0],track_id);
    manager->FillNtupleIColumn(1,fNtcolid[1],step_id);
    manager->AddNtupleRow(1);
}
void DarwinActivationShieldingAnalyzeManager::
    particle_information(const G4String & particle_name, G4double mass, G4int charge, G4double Ek)
{
   G4AnalysisManager *manager = G4AnalysisManager::Instance();
    manager->FillNtupleSColumn(2,fNtcolid[2],particle_name);
    manager->FillNtupleDColumn(2,fNtcolid[3],mass);
    manager->FillNtupleIColumn(2,fNtcolid[4],charge);
    manager->FillNtupleDColumn(2,fNtcolid[5],Ek);
    manager->AddNtupleRow(2);
}

void DarwinActivationShieldingAnalyzeManager::
    product_information(const G4String & track_particle_name,const G4String & process_name, const G4String & secondary_particle_name,
                        G4int atomic_number,G4int mass_number , G4int charge, G4double Ek)
{
    G4AnalysisManager *manager = G4AnalysisManager::Instance();
    manager->FillNtupleSColumn(3,fNtcolid[6],track_particle_name);
    manager->FillNtupleSColumn(3,fNtcolid[7],process_name);
    manager->FillNtupleSColumn(3,fNtcolid[8],secondary_particle_name);
    manager->FillNtupleIColumn(3,fNtcolid[9],atomic_number);
    manager->FillNtupleIColumn(3,fNtcolid[10],mass_number);
    manager->FillNtupleIColumn(3,fNtcolid[11],charge);
    manager->FillNtupleDColumn(3,fNtcolid[12],Ek);
    manager->AddNtupleRow(3);
}
void DarwinActivationShieldingAnalyzeManager::close()
{
    if(factoryOn)
    {
        G4AnalysisManager* manager = G4AnalysisManager::Instance();
        manager->Write();
        manager->CloseFile();
        factoryOn = false;
    }
}

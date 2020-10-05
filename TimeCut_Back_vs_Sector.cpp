#include <TFile.h>
#include <TCut.h>
#include <TCutG.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <TROOT.h>
#include <TSystem.h>


extern TCut particle_multiplicity_reqirement;
extern TCut ring_sector_time_requiremet;
extern TCut particle_requirement;
extern TCutG *cutg;
extern bool  Skip;
extern TString cut_filename;
extern TFile *f_cut;

using namespace std;

void load_cut(){

f_cut = (TFile*)gROOT->GetListOfFiles()->FindObject(cut_filename);

if(f_cut){
  //TFile *f_cut = new TFile(cut_filename);
  cout << "getting the cut"<< endl;
  cutg= (TCutG*)f_cut->Get("CUTG");
  //cutg->Write();
  //f_cut->Write();
  //f_cut->Close();
  //cutg->SetVarX("back_energy");
  //cutg->SetVarY("front_energy");
  cout << "got the cut"<< endl;
  //cutg->SaveAs("hoho1.c"); //just testing!
  //int dog;
  //cin >> dog;
  cout << "Area is ..... " << cutg->Area() << endl;
  Skip = true;
 }
   else {
   Skip = false;
 }

}
/*
void load_cut()
{
   particle_multiplicity_reqirement = "backID != 6 && sect_mult == 1 && back_mult == 1";
   ring_sector_time_requiremet = "(sect_t_coarse-ring_t_coarse)+(sect_t_fine-ring_t_fine) > -120 && (sect_t_coarse-ring_t_coarse)+(sect_t_fine-ring_t_fine) < 120";
   particle_requirement = "CUTG_11" && ring_sector_time_requiremet && particle_multiplicity_reqirement; // REMEMBER TO
}
*/

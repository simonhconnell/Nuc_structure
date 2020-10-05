#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <stdlib.h>

#include <TCanvas.h>
#include <TApplication.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TGraph.h>
#include <TObject.h>
#include <TStyle.h>
#include <TH2D.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TCut.h>
#include <TCutG.h>

// Globals
TCanvas *MyCanvas_1  = 0;
TCanvas *MyCanvas_2  = 0;
TObject *MyObj = 0;
TChain  *chain = 0;
TTree *tevents = 0;
TTree *events = 0;  // going to be defined by loader.cpp using a TChain
TCutG *cutg = 0;
TCutG *mycutg = 0;
TCutG *tmpg = 0;
TCut particle_multiplicity_reqirement = 0;
TCut ring_sector_time_requiremet = 0;
TCut particle_requirement = 0;
TString cut_filename;
TFile *f_cut=0;


bool  Skip;

TH2D *TimeDiff_E = new TH2D("TimeDiff_E","TimeDiff_E",500,0,19500,500,0,-1500);
TH2D *TimeDiff_E_cut = new TH2D("TimeDiff_E_cut","TimeDiff_E_cut",500,0,19500,500,0,-1500);

	void loader(TString );
  void load_cut();

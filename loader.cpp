#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include <TChain.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>

using namespace std;

extern TTree *tevents;
extern TChain *chain;
extern TCanvas *MyCanvas_2;

	void loader(TString path_file)
{
	 chain = new TChain("events");
  	// Files to load into the chain.
    cout << "I am about to chain   " << endl;
		chain->AddFile(path_file);
		//chain->AddFile(path_file);
		//chain->AddFile(path_file);
		//chain->AddFile(path_file);
}

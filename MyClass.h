//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Sep 30 12:33:10 2020 by ROOT version 6.18/04
// from TTree events/events
// found on file: DATA/R94timecalibrated.root
//////////////////////////////////////////////////////////

#ifndef MyClass_h
#define MyClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class MyClass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           ring_mult;
   Short_t         ringID[29];   //[ring_mult]
   Double_t        ring_energy[29];   //[ring_mult]
   Double_t        ring_t_fine[29];   //[ring_mult]
   Long64_t        ring_t_coarse[29];   //[ring_mult]
   Int_t           sect_mult;
   Short_t         sectID[31];   //[sect_mult]
   Double_t        sect_energy[31];   //[sect_mult]
   Double_t        sect_t_fine[31];   //[sect_mult]
   Long64_t        sect_t_coarse[31];   //[sect_mult]
   Int_t           back_mult;
   Short_t         backID[16];   //[back_mult]
   Double_t        back_energy[16];   //[back_mult]
   Double_t        back_t_fine[16];   //[back_mult]
   Long64_t        back_t_coarse[16];   //[back_mult]
   Int_t           labrL_mult;
   Short_t         labrLID[8];   //[labrL_mult]
   Double_t        labrL_energy[8];   //[labrL_mult]
   Double_t        labrL_t_fine[8];   //[labrL_mult]
   Long64_t        labrL_t_coarse[8];   //[labrL_mult]
   Int_t           labrS_mult;
   Short_t         labrSID[6];   //[labrS_mult]
   Double_t        labrS_energy[6];   //[labrS_mult]
   Double_t        labrS_t_fine[6];   //[labrS_mult]
   Long64_t        labrS_t_coarse[6];   //[labrS_mult]
   Int_t           clover_mult;
   Short_t         cloverID[9];   //[clover_mult]
   Short_t         clover_crystal[9];   //[clover_mult]
   Double_t        clover_energy[9];   //[clover_mult]
   Double_t        clover_t_fine[9];   //[clover_mult]
   Long64_t        clover_t_coarse[9];   //[clover_mult]

   // List of branches
   TBranch        *b_ring_mult;   //!
   TBranch        *b_ringID;   //!
   TBranch        *b_ring_energy;   //!
   TBranch        *b_ring_t_fine;   //!
   TBranch        *b_ring_t_coarse;   //!
   TBranch        *b_sect_mult;   //!
   TBranch        *b_sectID;   //!
   TBranch        *b_sect_energy;   //!
   TBranch        *b_sect_t_fine;   //!
   TBranch        *b_sect_t_coarse;   //!
   TBranch        *b_back_mult;   //!
   TBranch        *b_backID;   //!
   TBranch        *b_back_energy;   //!
   TBranch        *b_back_t_fine;   //!
   TBranch        *b_back_t_coarse;   //!
   TBranch        *b_labrL_mult;   //!
   TBranch        *b_labrLID;   //!
   TBranch        *b_labrL_energy;   //!
   TBranch        *b_labrL_t_fine;   //!
   TBranch        *b_labrL_t_coarse;   //!
   TBranch        *b_labrS_mult;   //!
   TBranch        *b_labrSID;   //!
   TBranch        *b_labrS_energy;   //!
   TBranch        *b_labrS_t_fine;   //!
   TBranch        *b_labrS_t_coarse;   //!
   TBranch        *b_clover_mult;   //!
   TBranch        *b_cloverID;   //!
   TBranch        *b_clover_crystal;   //!
   TBranch        *b_clover_energy;   //!
   TBranch        *b_clover_t_fine;   //!
   TBranch        *b_clover_t_coarse;   //!

   MyClass(TTree *tree=0);
   virtual ~MyClass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(Int_t Loop_Flag);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MyClass_cxx
MyClass::MyClass(TTree *tree) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
     TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("DATA/Run94_data.root");
      //TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("DATA/R94timecalibrated.root");
      if (!f || !f->IsOpen()) {
        // f = new TFile("DATA/R94timecalibrated.root");
        f = new TFile("DATA/Run94_data.root");
      }
      f->GetObject("events",tree);

   }
   Init(tree);
}

MyClass::~MyClass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MyClass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MyClass::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void MyClass::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("ring_mult", &ring_mult, &b_ring_mult);
   fChain->SetBranchAddress("ringID", ringID, &b_ringID);
   fChain->SetBranchAddress("ring_energy", ring_energy, &b_ring_energy);
   fChain->SetBranchAddress("ring_t_fine", ring_t_fine, &b_ring_t_fine);
   fChain->SetBranchAddress("ring_t_coarse", ring_t_coarse, &b_ring_t_coarse);
   fChain->SetBranchAddress("sect_mult", &sect_mult, &b_sect_mult);
   fChain->SetBranchAddress("sectID", sectID, &b_sectID);
   fChain->SetBranchAddress("sect_energy", sect_energy, &b_sect_energy);
   fChain->SetBranchAddress("sect_t_fine", sect_t_fine, &b_sect_t_fine);
   fChain->SetBranchAddress("sect_t_coarse", sect_t_coarse, &b_sect_t_coarse);
   fChain->SetBranchAddress("back_mult", &back_mult, &b_back_mult);
   fChain->SetBranchAddress("backID", backID, &b_backID);
   fChain->SetBranchAddress("back_energy", back_energy, &b_back_energy);
   fChain->SetBranchAddress("back_t_fine", back_t_fine, &b_back_t_fine);
   fChain->SetBranchAddress("back_t_coarse", back_t_coarse, &b_back_t_coarse);
   fChain->SetBranchAddress("labrL_mult", &labrL_mult, &b_labrL_mult);
   fChain->SetBranchAddress("labrLID", labrLID, &b_labrLID);
   fChain->SetBranchAddress("labrL_energy", labrL_energy, &b_labrL_energy);
   fChain->SetBranchAddress("labrL_t_fine", labrL_t_fine, &b_labrL_t_fine);
   fChain->SetBranchAddress("labrL_t_coarse", labrL_t_coarse, &b_labrL_t_coarse);
   fChain->SetBranchAddress("labrS_mult", &labrS_mult, &b_labrS_mult);
   fChain->SetBranchAddress("labrSID", labrSID, &b_labrSID);
   fChain->SetBranchAddress("labrS_energy", labrS_energy, &b_labrS_energy);
   fChain->SetBranchAddress("labrS_t_fine", labrS_t_fine, &b_labrS_t_fine);
   fChain->SetBranchAddress("labrS_t_coarse", labrS_t_coarse, &b_labrS_t_coarse);
   fChain->SetBranchAddress("clover_mult", &clover_mult, &b_clover_mult);
   fChain->SetBranchAddress("cloverID", cloverID, &b_cloverID);
   fChain->SetBranchAddress("clover_crystal", clover_crystal, &b_clover_crystal);
   fChain->SetBranchAddress("clover_energy", clover_energy, &b_clover_energy);
   fChain->SetBranchAddress("clover_t_fine", clover_t_fine, &b_clover_t_fine);
   fChain->SetBranchAddress("clover_t_coarse", clover_t_coarse, &b_clover_t_coarse);
   Notify();
}

Bool_t MyClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MyClass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MyClass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MyClass_cxx

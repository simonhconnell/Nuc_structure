#include "Master_code.h"

#define MyClass_cxx // Atomagically made by the MakeClass method of the tree
#include "MyClass.h"



using namespace std;

void printarray (Short_t arg[], int length) {
  for (int n=0; n<length; n++)
    cout << arg[n] << " ";
  cout << "\n";
}



void MyClass::Loop(Int_t Loop_Flag)
{
//   In a ROOT session, you can do:
//      root> .L MyClass.C
//      root> MyClass t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   cout << "Entering Loop with Loop_Flag = " << Loop_Flag << "and cut_filename  " << cut_filename  <<endl;




   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {   // loop over events in the tree
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      // do stuff here in the event loop
      Int_t i_fired=-1,j_fired=-1,k_fired=-1;
      Double_t time_diff_course, time_diff_fine;
      Long64_t temp;
      if (backID[0]!=6 && back_mult==1 && sect_mult==1) {
          temp =  sect_t_coarse[0]-back_t_coarse[0];
          time_diff_course =  (Double_t)temp;
          time_diff_fine   =  sect_t_fine[0] - back_t_fine[0];
          TimeDiff_E->Fill(back_energy[0],(time_diff_course+time_diff_fine));
        }

        if (Skip) {
          //if (clover_mult >= 2 && cutg->IsInside(back_energy, front_energy))
          if (backID[0]!=6 && back_mult==1 && sect_mult==1&&cutg->IsInside(back_energy[0],(time_diff_course+time_diff_fine))) {
            time_diff_course =  (Double_t)(sect_t_coarse[0]-ring_t_coarse[0]);
            time_diff_fine   =             sect_t_fine[0]  -ring_t_fine[0];
           TimeDiff_E_cut->Fill(back_energy[0],(time_diff_course+time_diff_fine));
          }
        }
          if (jentry%100000==0) cout << "looping at event  " << jentry << endl ;
      }
   }



void set_plot_style()
{
    const Int_t NRGBs = 5;
    const Int_t NCont = 511;

    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);
}

double angles(int i){
  float d = 30.0; //distance_from_target mm
  return asin( (11.25 + 0.5*i)/sqrt(d*d + (11.25 + 0.5*i)*(11.25 + 0.5*i)) )*180.0/3.14159;
}

double E_remap(double a,double b,double c,double ap,double bp,double cp,double T3){
  T3=T3*1000.0;  //Work from MeV to keV
  double E_ex = (c + b*T3 + a*T3*T3); // this is now in keV
  double x,x1,x2;
  // (cp-E_Ex) + bp*T3p + ap*T3p*T3p = 0
  double discriminant = bp*bp - 4.0*(cp-E_ex)*ap;
  if (discriminant > 0) {
    x1 = (-bp + sqrt(discriminant) ) / (2*ap);
    x2 = (-bp - sqrt(discriminant) ) / (2*ap);
    cout << "Roots are x1 = " << x1 << "   x2 = " << x2 << endl;
    if (x1*x2 > 0) {
      cout << "There are two positive or two negative roots"  << endl;
      x = 0;
    }
    else {
    if (x1 > 0) x=x1;
    if (x2 > 0) x=x2;
    cout << "There is one physical root " << x << endl;
    }
  }
  else {
    cout << "The root is 0 or there are no roots" << endl;
    x = 0;
  }
  return x/1000.0;  // Only one root is physical, or only one root, so there is a solution, in MeV
}


int main(int argc, char **argv) {

    if(argc!=5){
      printf("Usage   : %s  <inputfile 1 (string)>  <Golden Theta3 (int)>  <data-root-file>  <cut-file-name> \n",argv[0]);
      printf("Assumes you have made a soft link from <DATA> to where your data path is \n");
      printf("Option : nothing yet \n");
        exit(0);
    }

    // Extract input file name 1 from the argument list
    char input_file_1[64];   // input file
    strcpy(input_file_1,argv[1]);

    //char str_T3[64];   // T3
    //strcpy(str_T3,argv[2]);
    //double T3=(double)atof(str_T3);

    char str_Theta3[64];   // Golden Theta3
    strcpy(str_Theta3,argv[2]);
    int Theta3=atoi(str_Theta3);

    // Extract root file name 3 from the argument list
    char root_file_1[64];   // root file
    strcpy(root_file_1,argv[3]);
    TString PathToData = "DATA/";
    TString root_1 = PathToData+root_file_1;

    char cut_file_1[64];   // cut file
    strcpy(cut_file_1,argv[4]);
    TString cut_filename = cut_file_1;


    TApplication *TheApp = new TApplication("Plotting",&argc,argv);

    {
    gROOT->Reset();
    gStyle->SetCanvasColor(10);     // background is no longer mouse-dropping white
  	gStyle->SetPalette(1,0);            // blue to red false color palette. Use 9 for b/w
  	gStyle->SetCanvasBorderMode(0);     // turn off canvas borders
  	gStyle->SetPadBorderMode(1);
  	gStyle->SetPaintTextFormat("5.2f");  // What precision to put numbers if plotted with "TEXT"
    }
    if (0){// For publishing:
  	gStyle->SetLineWidth(1.);
  	gStyle->SetTextSize(1.1);
  	gStyle->SetLabelSize   (0.06,"xy");
  	gStyle->SetTitleSize   (0.06,"xy");
  	gStyle->SetTitleOffset (1.2,"x");
  	gStyle->SetTitleOffset (1.0,"y");
  	gStyle->SetPadTopMargin   (0.1);
  	gStyle->SetPadRightMargin (0.1);
  	gStyle->SetPadBottomMargin(0.16);
  	gStyle->SetPadLeftMargin  (0.12);
    }

    // The input .txt file
    ifstream file_1;
    string input_1 = input_file_1;
    file_1.open (input_1);
    std::string::size_type sz_1 = 0;   // alias of size_t
    std::string str_1;
    long linenum = 0;      // line number in data file
    double a[48], b[48], c[48];
    // Loop over lines in file
        while(file_1.good() ){
          std::getline(file_1, str_1);
          //cout << linenum << "  String 1 ..... " << str_1 << "\n";
            if (str_1.length() > 0 ) {
                c[linenum] = stod(str_1,&sz_1);
                str_1 = str_1.substr(sz_1);
                b[linenum] = stod(str_1,&sz_1);
                str_1 = str_1.substr(sz_1);
                a[linenum] = stod(str_1,&sz_1);
            }
            //cout << "a = " << a[linenum]  << "   b = " << b[linenum] << "   c = " << c[linenum]<< "\n";
            linenum+= 1;
        }  // end of file read loop


        /* Make the 2D plot of the Excitation energy
        float E, E1=0.0, E2=50.0;
        Int_t Nybins = 1001;
        float excitation;
        TH2D *h2 = new TH2D("h2","h2",48,angles(0),angles(47),Nybins,E1,E2);
        for (int i=0; i<48; i++) {
            for (int j=0; j<Nybins; j++) {
                E=E1+j*((E2-E1)/(Nybins-1));
                excitation = (a[i]*E*E*1000000+b[i]*E*1000+c[i])/1000.;
                if (excitation < 0) excitation = 0;
                h2->SetBinContent(i+1,j+1,excitation);
            }
        }
        set_plot_style();
        h2->SetStats(kFALSE);
        h2->Draw("colz");
        MyCanvas_1->Update();
        */

  /*
  //Remapping ..... use later
  //Now find the correct a b c value for this Theta value
  // T3 and Theta3 are the values read in from the command line
  double T3p = E_remap(a[Theta3], b[Theta3], c[Theta3], a[6], b[6], c[6],T3);
  cout << endl << endl << "remapping .... T3 at Theta 7 ("<< angles(7) << ") is " << T3p <<endl;
  */

  // Open the root file
  TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(root_1);
  if (!f) {
      f = new TFile(root_1);
  }

  f->ls();   // see whats in your ntuple


  tevents = (TTree*)gDirectory->Get("events");
  if (!tevents) {
      fprintf(stderr,"events ntuple not found in file, exiting.\n");
      exit(1);
  }


  TH2D * time_sect = (TH2D*)f->Get("time_sect");
  TH2D * time_clover = (TH2D*)f->Get("time_clover");

  MyCanvas_1 = new TCanvas("c1","Ex_energy",50,50,1300,900);
  MyCanvas_1->Divide(2,2);
  MyCanvas_1->cd(1);
  time_sect->Draw();

  MyCanvas_1->cd(2);
  time_clover->Draw();
  MyCanvas_1->Update();


  Int_t Loop_Flag;  // keep track of entry into loop
  Loop_Flag=1;
  load_cut();
  cutg = (TCutG*)gROOT->FindObject("CUTG");
  tmpg = (TCutG*)gROOT->GetListOfSpecials()->FindObject("CUTG");
  //mycutg = (TCutG*)(tmpg->Clone("mycutg"));
  //cout << "Area mycutg is ..... " << mycutg->Area() << endl;
  MyCanvas_2 = new TCanvas("c2","Ex_energy",120,120,1300,900);
  //MyCanvas_2->Divide(2,2);
  loader(root_1);  // This will make a chain of a tree called events
  MyClass *MyClass_Obj = new MyClass(events);
  MyClass_Obj->Loop(Loop_Flag);
  MyCanvas_2->cd();
  TimeDiff_E->Draw("colz");
MyCanvas_2->Update();

  if (!Skip) {
    f_cut = new TFile(cut_filename,"RECREATE");
    //f_cut = new TFile("cutg_hello.root");
    cout << "\n .... wating for you to implement manually the graphical cut   \n";
    cutg = (TCutG*) gPad->WaitPrimitive("CUTG", "CUTG");  // making cut, store to CUTG
    cout << "\n .... finished graphical cut .... rereading the ntuple using that g-cut   \n";
    f_cut->cd();
    cutg->Write();
    cutg->SaveAs("hoho0.c"); // just testing
    f_cut->Close();
    cout << "Area is ..... " << cutg->Area() << endl;
    //save it
    //from ROOT import TFile
    //   ds = RooDataSet("ds", "data set");
    //fds = TFile("cutg_hello.root", "RECREATE");
    //fds->cd();
    //  ds->Write();
    //  cout << "saved the RootDataSet" << '\n';
    }
    else
    {
      cout << "\n .... found graphical cut .... rereading it from file  \n";
      cutg->Draw();
    }

  MyCanvas_2->cd();
  TimeDiff_E_cut->Draw("colz");
  cout << "Finished draw   " << endl;
  MyCanvas_2->Update();


  gPad->Modified();		// make sure hist is drawn
  gPad->Update();		  // make sure hist is drawn
  gSystem->ProcessEvents(); // make sure hist is drawn


  cout << "\n Done  ...  Now waiting...";
  cout << "\n ==> Double click mouse button in graphics window to end program.\n\n\n";
  int n=1;
  while (n>0) {
      MyObj = gPad->WaitPrimitive();
      if (!MyObj) break;
      printf("Loop i=%d, found objIsA=%s, name=%s\n",n,MyObj->ClassName(),MyObj->GetName());
  }



  delete MyCanvas_1;
  file_1.close();
}

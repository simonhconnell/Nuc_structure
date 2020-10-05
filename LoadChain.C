/*
 * Macro for loading the tree and select event list.
 * Other macros that rely on selection entry lists should have a apply "SetEntryListFile" them self.
 *
 */

{

	 TChain *chain = new TChain("events");

  	// Files to load into the chain.
   chain->AddFile("R94.root");
   events->Draw("(sect_t_coarse-back_t_coarse)+(sect_t_fine-back_t_fine):back_energy>>m(500,0,19500,500,0,-1500)","backID!=6&&back_mult==1&&sect_mult==1","colz");
	 new TCanvas;
   gROOT->ProcessLine(".x TimeCut_Back_vs_Sector.C");
	 events->Draw("(sect_t_coarse-ring_t_coarse)+(sect_t_fine-ring_t_fine):back_energy>>m(500,0,19500,500,0,-1500)","backID!=6&&back_mult==1&&sect_mult==1 && CUTG");
	 events->Draw("(sect_t_coarse-ring_t_coarse)+(sect_t_fine-ring_t_fine)", "backID != 6 && sect_mult == 1 && back_mult == 1 && CUTG");

   events->Draw("sect_energy:back_energy>>m2(500,0,20000,500,0,20000)","backID!=6&& ring_mult == 1&&back_mult == 1&&CUTG&&((sect_t_coarse-ring_t_coarse)+(sect_t_fine-ring_t_fine))>-100&&((sect_t_coarse-ring_t_coarse)+(sect_t_fine-ring_t_fine))<80&ringID == 38","colz");


}

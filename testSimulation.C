#if !defined(__CINT__) || defined(__MAKECINT__)
#include "./Dictionary.h"
#include "./FastSimulation.h"
#include "TH1F.h"
#include "TCanvas.h"
#endif

void testSimulation(unsigned int rep=10000){
  FastSimulation test = FastSimulation("dizionario.bin");
  TH1F* histo = new TH1F("histo","histo",1500,-0.5,1499.5);
  histo->GetXaxis()->SetTitle("GroupID");
  histo->SetFillStyle(3008);
  histo->SetFillColor(kGreen-3);
  for(unsigned int i=0; i<rep; i++){
    histo->Fill(test.GetRandom());
  }
  TCanvas* c = new TCanvas("c","c");
  c->cd();
  histo->Draw();
}

#include <TFile.h>
#include <TH1D.h>

TFile* rootfile=0;

TH1* getHist(const char* name)
{
  rootfile=new TFile("histo.root");
  if(!rootfile) {
    std::cout << "Could not find histo.root" << std::endl;
    assert(rootfile);
  }
  rootfile->cd("demo");
  TH1* h=dynamic_cast<TH1*>( gROOT->FindObject(name) );
  if(!h)
    std::cout << "Cannot find object " << name << std::endl;
  assert(h);
  return h;
}

TH1D* differential(TH1D* h, int numevents, double xs)
{
  int nbins=h->GetNbinsX();

  // perform underflow and overflow first
  //  h->SetBinContent(1, h->GetBinContent(0)+h->GetBinContent(1));
  //  h->SetBinContent(nbins, h->GetBinContent(nbins)+h->GetBinContent(nbins+1));

  TString name=h->GetName();
  TH1D* hDiff=dynamic_cast<TH1D*>(h->Clone(name+"Diff"));
  
  for(int i=1; i<=nbins; i++) {
    double width=h->GetBinWidth(i);
    double val=h->GetBinContent(i);
    double err=h->GetBinError(i);
    double newval=val/width/numevents*xs;
    double newerr=err/width/numevents*xs;
    hDiff->SetBinContent(i, newval);
    hDiff->SetBinError(i, newerr);
  }
  return hDiff;
}

TH1D* renormalize(TH1D* h, int numevents, double xs, double lumi)
{
  int nbins=h->GetNbinsX();

  // perform underflow and overflow first
  //  h->SetBinContent(1, h->GetBinContent(0)+h->GetBinContent(1));
  //  h->SetBinContent(nbins, h->GetBinContent(nbins)+h->GetBinContent(nbins+1));

  TString name=h->GetName();
  TH1D* hNorm=dynamic_cast<TH1D*>(h->Clone(name+"Norm"));
  
  for(int i=1; i<=nbins; i++) {
    double val=h->GetBinContent(i);
    double err=h->GetBinError(i);
    double newval=val*xs*lumi/numevents;
    double newerr=err*xs*lumi/numevents;
    //    double newval=val/numevents;
    //    double newerr=sqrt(val)/numevents;
    hNorm->SetBinContent(i, newval);
    hNorm->SetBinError(i, newerr);
  }
  return hNorm;
}

void drawplots(int which)
{
  const double MinBiasXS=79.3e12; // in fb
  const double Lumi=3000; // in fb-1

  TCanvas *c=new TCanvas();
  TH1F* hEventCnt=dynamic_cast<TH1F*>(getHist("hEventCnt"));
  int numEvents=hEventCnt->GetBinContent(1);

  TH1D *h1=0, *h2=0, *h3=0, *h4=0;
  TString h1Label, h2Label, h3Label, h4Label;
  if(which==1) {
    TH1D* hNuEleEta3=dynamic_cast<TH1D*>(getHist("hNuEleEta3"));
    TH1D* hNuMuoEta3=dynamic_cast<TH1D*>(getHist("hNuMuoEta3"));
    TH1D* hNuEleEta2=dynamic_cast<TH1D*>(getHist("hNuEleEta2"));
    TH1D* hNuMuoEta2=dynamic_cast<TH1D*>(getHist("hNuMuoEta2"));
    h1=differential(hNuMuoEta3, numEvents, MinBiasXS);
    h2=differential(hNuEleEta3, numEvents, MinBiasXS);
    h3=differential(hNuMuoEta2, numEvents, MinBiasXS);
    h4=differential(hNuEleEta2, numEvents, MinBiasXS);
    h1Label="#nu_{#mu} (|#eta|<1.5)";
    h2Label="#nu_{e} (|#eta|<1.5)";
    h3Label="#nu_{#mu} (|#eta|<1.0)";
    h4Label="#nu_{e} (|#eta|<1.0)";
    h1->GetYaxis()->SetTitle("d#sigma/dE [fb/GeV]");
    h1->SetMinimum(1e6);
  } else if(which==2) {
    TH1D* hNuEleEta3=dynamic_cast<TH1D*>(getHist("hNuEleEta3"));
    TH1D* hNuMuoEta3=dynamic_cast<TH1D*>(getHist("hNuMuoEta3"));
    TH1D* hNuEleEta2=dynamic_cast<TH1D*>(getHist("hNuEleEta2"));
    TH1D* hNuMuoEta2=dynamic_cast<TH1D*>(getHist("hNuMuoEta2"));
    h1=renormalize(hNuMuoEta3, numEvents, MinBiasXS, Lumi);
    h2=renormalize(hNuEleEta3, numEvents, MinBiasXS, Lumi);
    h3=renormalize(hNuMuoEta2, numEvents, MinBiasXS, Lumi);
    h4=renormalize(hNuEleEta2, numEvents, MinBiasXS, Lumi);
    h1Label="#nu_{#mu} (|#eta|<1.5)";
    h2Label="#nu_{e} (|#eta|<1.5)";
    h3Label="#nu_{#mu} (|#eta|<1.0)";
    h4Label="#nu_{e} (|#eta|<1.0)";
    ostringstream oss;
    oss << "# of #nu/bin in " << Lumi << "/fb";
    h1->GetYaxis()->SetTitle(oss.str().c_str());
    h1->SetMinimum(1e11);
  } else if(which==3) {
    TH1D* hNuEleEne=dynamic_cast<TH1D*>(getHist("hNuEleEne"));
    TH1D* hNuMuoEne=dynamic_cast<TH1D*>(getHist("hNuMuoEne"));
    h1=differential(hNuMuoEne, numEvents, MinBiasXS);
    h2=differential(hNuEleEne, numEvents, MinBiasXS);
    h1Label="#nu_{#mu} (|#eta|<1.5)";
    h2Label="#nu_{e} (|#eta|<1.5)";
    h1->GetYaxis()->SetTitle("E#upointd#sigma/dE [fb]");
    h1->SetMinimum(1e8);
  } else if(which==4) {
    TH1D* hNuEleEne2=dynamic_cast<TH1D*>(getHist("hNuEleEne2"));
    TH1D* hNuMuoEne2=dynamic_cast<TH1D*>(getHist("hNuMuoEne2"));
    h1=differential(hNuMuoEne2, numEvents, MinBiasXS);
    h2=differential(hNuEleEne2, numEvents, MinBiasXS);
    h1Label="#nu_{#mu} (|#eta|<1.5)";
    h2Label="#nu_{e} (|#eta|<1.5)";
    h1->GetYaxis()->SetTitle("E^{2}#upointd#sigma/dE [fb#upointGeV]");
    h1->SetMinimum(1e10);
  }
  
  h1->Draw();
  h2->Draw("same");
  if(h3) h3->Draw("same");
  if(h4) h4->Draw("same");
  
  h1->SetStats(0);
  h1->SetTitle("");
  h1->GetXaxis()->SetTitle("Energy [GeV]");
  gPad->SetLogx(1);
  gPad->SetLogy(1);
  
  h1->SetLineColor(kRed+2);
  h1->SetMarkerColor(kRed+2);
  h2->SetMarkerStyle(21);
  h2->SetLineColor(kBlue+2);
  h2->SetMarkerColor(kBlue+2);

  if(h3) {
    for(int i=0; i<=h3->GetNbinsX()+1; i++) h3->SetBinError(i, 0.0);
    h3->SetLineColor(kRed+2);
    h3->SetLineStyle(2);
    h3->SetMarkerStyle(0);
    h3->SetFillStyle(0);
  }
  if(h4) {
    for(int i=0; i<=h4->GetNbinsX()+1; i++) h4->SetBinError(i, 0.0);
    h4->SetLineColor(kBlue+2);
    h4->SetLineStyle(2);
    h4->SetMarkerStyle(0);
    h4->SetFillStyle(0);
  }
  
  TLegend* leg=new TLegend(0.62,0.61,0.85,0.89);
  leg->AddEntry(h1, h1Label,"lp");
  if(h3) leg->AddEntry(h3, h3Label,"l");
  leg->AddEntry(h2, h2Label,"lp");
  if(h4) leg->AddEntry(h4, h4Label,"l");
  leg->SetLineColor(0);
  leg->Draw();
}

void drawplots(void)
{
  drawplots(1);
  drawplots(2);
  drawplots(3);
  drawplots(4);
}

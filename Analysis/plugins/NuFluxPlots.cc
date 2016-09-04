// -*- C++ -*-
//
// Package:    cms-NeutrinoFlux/Analysis
// Class:      NuFluxPlots
// 
/**\class Analysis NuFluxPlots.cc cms-NeutrinoFlux/Analysis/plugins/NuFluxPlots.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  John Chou
//         Created:  Wed, 31 Aug 2016 10:32:11 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"


#include "SimDataFormats/Track/interface/SimTrackContainer.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include <TH1D.h>

//
// class declaration
//

class NuFluxPlots : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
  explicit NuFluxPlots(const edm::ParameterSet&);
  ~NuFluxPlots();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  
  // ----------member data ---------------------------
  
  edm::EDGetTokenT<edm::SimTrackContainer> tokSimTrk_;

  edm::Service<TFileService> fs_;

  TH1D *hNuEleEta1_, *hNuEleEta2_, *hNuEleEta3_;
  TH1D *hNuMuoEta1_, *hNuMuoEta2_, *hNuMuoEta3_;
  TH1D *hNuEleEne_, *hNuMuoEne_;
  TH1D *hNuEleEne2_, *hNuMuoEne2_;
  TH1F *hEventCnt_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//

NuFluxPlots::NuFluxPlots(const edm::ParameterSet& iConfig)
{
  using namespace std;
  using namespace edm;

  string g4Label = iConfig.getUntrackedParameter<string>("ModuleLabel","g4SimHits");
  tokSimTrk_ = consumes<SimTrackContainer>(InputTag(g4Label));
 
  int NBINS=20;
  const double b1=1.0;
  const double b2=1.584893;
  const double b3=2.511886;
  const double b4=3.981072;
  const double b5=6.309573;
  const Double_t bins[NBINS+1] = { b1/100, b2/100, b3/100, b4/100, b5/100, b1/10, b2/10, b3/10, b4/10, b5/10, b1, b2, b3, b4, b5, b1*10, b2*10, b3*10, b4*10, b5*10, b1*100 };
  const Double_t *binref=bins;

  hNuEleEta1_=fs_->make<TH1D>("hNuEleEta1","Electron Neutrino Energy (|eta|<0.5)", NBINS, binref);
  hNuEleEta2_=fs_->make<TH1D>("hNuEleEta2","Electron Neutrino Energy (|eta|<1.0)", NBINS, binref);
  hNuEleEta3_=fs_->make<TH1D>("hNuEleEta3","Electron Neutrino Energy (|eta|<1.5)", NBINS, binref);
  hNuMuoEta1_=fs_->make<TH1D>("hNuMuoEta1","Muon Neutrino Energy (|eta|<0.5)", NBINS, binref);
  hNuMuoEta2_=fs_->make<TH1D>("hNuMuoEta2","Muon Neutrino Energy (|eta|<1.0)", NBINS, binref);
  hNuMuoEta3_=fs_->make<TH1D>("hNuMuoEta3","Muon Neutrino Energy (|eta|<1.5)", NBINS, binref);
  hNuEleEne_=fs_->make<TH1D>("hNuEleEne","Electron Neutrino Energy (weighted by E |eta|<1.5)", NBINS, binref);
  hNuMuoEne_=fs_->make<TH1D>("hNuMuoEne","Muon Neutrino Energy (weighted by E |eta|<1.5)", NBINS, binref);
  hNuEleEne2_=fs_->make<TH1D>("hNuEleEne2","Electron Neutrino Energy (weighted by E^2 |eta|<1.5)", NBINS, binref);
  hNuMuoEne2_=fs_->make<TH1D>("hNuMuoEne2","Muon Neutrino Energy (weighted by E^2 |eta|<1.5)", NBINS, binref);
  hEventCnt_=fs_->make<TH1F>("hEventCnt","Event Count",1,-0.5,0.5);

  hNuEleEne_->Sumw2();
  hNuMuoEne_->Sumw2();
  hNuEleEne2_->Sumw2();
  hNuMuoEne2_->Sumw2();
}


NuFluxPlots::~NuFluxPlots()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
NuFluxPlots::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;

  Handle<SimTrackContainer> simTracks;
  iEvent.getByToken(tokSimTrk_, simTracks);
  hEventCnt_->Fill(0.0);
  for(SimTrackContainer::const_iterator it=simTracks->begin(); it!=simTracks->end(); ++it) {
    int absid=abs(it->type());
    double E=it->momentum().E();
    double abseta=fabs(it->momentum().eta());
    if(absid==12) {
      if(abseta<0.5) hNuEleEta1_->Fill(E);
      if(abseta<1.0) hNuEleEta2_->Fill(E);
      if(abseta<1.5) hNuEleEta3_->Fill(E);
      if(abseta<1.5) hNuEleEne_->Fill(E,E);
      if(abseta<1.5) hNuEleEne2_->Fill(E,E*E);
    }
    if(absid==14) {
      if(abseta<0.5) hNuMuoEta1_->Fill(E);
      if(abseta<1.0) hNuMuoEta2_->Fill(E);
      if(abseta<1.5) hNuMuoEta3_->Fill(E);
      if(abseta<1.5) hNuMuoEne_->Fill(E,E);
      if(abseta<1.5) hNuMuoEne2_->Fill(E,E*E);
    }
  }


  return;
}


// ------------ method called once each job just before starting event loop  ------------
void 
NuFluxPlots::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
NuFluxPlots::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
NuFluxPlots::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(NuFluxPlots);

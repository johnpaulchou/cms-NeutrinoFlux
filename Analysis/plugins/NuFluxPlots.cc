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
   //now do what ever initialization is needed
   usesResource("TFileService");

   iConfig.getParameter<edm::InputTag>("reducedBarrelRecHitCollection");

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

  EDGetTokenT<SimTrackContainer> simTracksToken(consumes<SimTrackContainer>("g4SimHits"));
  Handle<SimTrackContainer> simTracks;
  iEvent.getByToken(simTracksToken,simTracks);

  cout << " size = " << simTracks->size() << endl;

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

import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:MinBias_13TeV_pythia8_cff_py_GEN_SIM.root'
    )
)

process.demo = cms.EDAnalyzer('NuFluxPlots'
)


process.p = cms.Path(process.demo)

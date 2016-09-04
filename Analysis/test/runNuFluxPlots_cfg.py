import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:root://cmsxrootd.fnal.gov//store/user/johnpaul/NeutrinoFlux/MinBias14TeVPythia8GenSim/160903_173349/0000/MinBias_14TeV_pythia8_cff_py_GEN_SIM_1.root',
        'file:root://cmsxrootd.fnal.gov//store/user/johnpaul/NeutrinoFlux/MinBias14TeVPythia8GenSim/160903_173349/0000/MinBias_14TeV_pythia8_cff_py_GEN_SIM_100.root',
        'file:root://cmsxrootd.fnal.gov//store/user/johnpaul/NeutrinoFlux/MinBias14TeVPythia8GenSim/160903_173349/0000/MinBias_14TeV_pythia8_cff_py_GEN_SIM_16.root',
        'file:root://cmsxrootd.fnal.gov//store/user/johnpaul/NeutrinoFlux/MinBias14TeVPythia8GenSim/160903_173349/0000/MinBias_14TeV_pythia8_cff_py_GEN_SIM_2.root',
        'file:root://cmsxrootd.fnal.gov//store/user/johnpaul/NeutrinoFlux/MinBias14TeVPythia8GenSim/160903_173349/0000/MinBias_14TeV_pythia8_cff_py_GEN_SIM_21.root',
        'file:root://cmsxrootd.fnal.gov//store/user/johnpaul/NeutrinoFlux/MinBias14TeVPythia8GenSim/160903_173349/0000/MinBias_14TeV_pythia8_cff_py_GEN_SIM_23.root',
        'file:root://cmsxrootd.fnal.gov//store/user/johnpaul/NeutrinoFlux/MinBias14TeVPythia8GenSim/160903_173349/0000/MinBias_14TeV_pythia8_cff_py_GEN_SIM_24.root',
        'file:root://cmsxrootd.fnal.gov//store/user/johnpaul/NeutrinoFlux/MinBias14TeVPythia8GenSim/160903_173349/0000/MinBias_14TeV_pythia8_cff_py_GEN_SIM_25.root',
        'file:root://cmsxrootd.fnal.gov//store/user/johnpaul/NeutrinoFlux/MinBias14TeVPythia8GenSim/160903_173349/0000/MinBias_14TeV_pythia8_cff_py_GEN_SIM_3.root',
        'file:root://cmsxrootd.fnal.gov//store/user/johnpaul/NeutrinoFlux/MinBias14TeVPythia8GenSim/160903_173349/0000/MinBias_14TeV_pythia8_cff_py_GEN_SIM_4.root',
        'file:root://cmsxrootd.fnal.gov//store/user/johnpaul/NeutrinoFlux/MinBias14TeVPythia8GenSim/160903_173349/0000/MinBias_14TeV_pythia8_cff_py_GEN_SIM_42.root',
        'file:root://cmsxrootd.fnal.gov//store/user/johnpaul/NeutrinoFlux/MinBias14TeVPythia8GenSim/160903_173349/0000/MinBias_14TeV_pythia8_cff_py_GEN_SIM_47.root',
        'file:root://cmsxrootd.fnal.gov//store/user/johnpaul/NeutrinoFlux/MinBias14TeVPythia8GenSim/160903_173349/0000/MinBias_14TeV_pythia8_cff_py_GEN_SIM_5.root',
        'file:root://cmsxrootd.fnal.gov//store/user/johnpaul/NeutrinoFlux/MinBias14TeVPythia8GenSim/160903_173349/0000/MinBias_14TeV_pythia8_cff_py_GEN_SIM_62.root',
        'file:root://cmsxrootd.fnal.gov//store/user/johnpaul/NeutrinoFlux/MinBias14TeVPythia8GenSim/160903_173349/0000/MinBias_14TeV_pythia8_cff_py_GEN_SIM_9.root',
        'file:root://cmsxrootd.fnal.gov//store/user/johnpaul/NeutrinoFlux/MinBias14TeVPythia8GenSim/160903_173349/0000/MinBias_14TeV_pythia8_cff_py_GEN_SIM_91.root',
        'file:root://cmsxrootd.fnal.gov//store/user/johnpaul/NeutrinoFlux/MinBias14TeVPythia8GenSim/160903_173349/0000/MinBias_14TeV_pythia8_cff_py_GEN_SIM_97.root',
        'file:root://cmsxrootd.fnal.gov//store/user/johnpaul/NeutrinoFlux/MinBias14TeVPythia8GenSim/160903_173349/0000/MinBias_14TeV_pythia8_cff_py_GEN_SIM_98.root',
        'file:root://cmsxrootd.fnal.gov//store/user/johnpaul/NeutrinoFlux/MinBias14TeVPythia8GenSim/160903_173349/0000/MinBias_14TeV_pythia8_cff_py_GEN_SIM_99.root',
    )
)


process.TFileService = cms.Service("TFileService",
      fileName = cms.string("histo.root"),
#      closeFileFast = cms.untracked.bool(True)
  )

process.demo = cms.EDAnalyzer('NuFluxPlots'
)


process.p = cms.Path(process.demo)

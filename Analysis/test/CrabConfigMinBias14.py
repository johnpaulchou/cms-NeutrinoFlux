from CRABClient.UserUtilities import config, getUsernameFromSiteDB
from os.path import expanduser

config = config()

config.General.requestName = 'MC_generation'
config.General.workArea = '%s/crab_projects' % (expanduser("~"))
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'PrivateMC'
config.JobType.psetName = 'MinBias_14TeV_pythia8_cff_py_GEN_SIM.py'

config.Data.outputPrimaryDataset = 'NeutrinoFlux'
config.Data.splitting = 'EventBased'
config.Data.unitsPerJob = 2000
NJOBS = 100  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.outputDatasetTag = 'MinBias14TeVPythia8GenSim'

config.Site.storageSite = 'T3_US_FNALLPC'

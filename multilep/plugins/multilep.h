#ifndef MULTILEP_H
#define MULTILEP_H

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/METReco/interface/METFwd.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
//#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"



//New for SUSY masses
#include "SimDataFormats/GeneratorProducts/interface/GenLumiInfoHeader.h"

#include "TTree.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "heavyNeutrino/multilep/interface/TriggerAnalyzer.h"
#include "heavyNeutrino/multilep/interface/LeptonAnalyzer.h"
#include "heavyNeutrino/multilep/interface/PhotonAnalyzer.h"
#include "heavyNeutrino/multilep/interface/JetAnalyzer.h"
#include "heavyNeutrino/multilep/interface/GenAnalyzer.h"
#include "heavyNeutrino/multilep/interface/ParticleLevelAnalyzer.h"
#include "heavyNeutrino/multilep/interface/BFragAnalyzer.h"
#include "heavyNeutrino/multilep/interface/LheAnalyzer.h"
#include "heavyNeutrino/multilep/interface/SUSYAnalyzer.h"

// Allow for easy way to retrieve handles
namespace {
  template<typename T, typename I> edm::Handle<T> getHandle(const I& iEvent,const edm::EDGetTokenT<T>& token){
    edm::Handle<T> handle;
    iEvent.getByToken(token,handle);
    return handle;
  }
}


//
// class declaration
//
class TriggerAnalyzer;
class LeptonAnalyzer;
class PhotonAnalyzer;
class JetAnalyzer;
class GenAnalyzer;
class ParticleLevelAnalyzer;
class BFragAnalyzer;
class LheAnalyzer;
class SUSYAnalyzer;

class multilep : public edm::one::EDAnalyzer<edm::one::WatchLuminosityBlocks, edm::one::WatchRuns, edm::one::SharedResources> {
    //Define other analyzers as friends
    friend TriggerAnalyzer;
    friend LeptonAnalyzer;
    friend PhotonAnalyzer;
    friend JetAnalyzer;
    friend GenAnalyzer;
    friend ParticleLevelAnalyzer;
    friend BFragAnalyzer;
    friend LheAnalyzer;
    friend SUSYAnalyzer;
    public:
        explicit multilep(const edm::ParameterSet&);

        bool isData() const{ return sampleIsData; }
        bool isMC() const{ return !sampleIsData; }
        bool is2016() const{ return !(sampleIs2017 || sampleIs2018); }
        bool is2017() const{ return sampleIs2017; }
        bool is2018() const{ return sampleIs2018; }
        bool isFastSim() const{ return sampleIsFastSim; }
        bool isSUSY() const{ return sampleIsSUSY; }

        ~multilep();

    private:
        edm::EDGetTokenT<std::vector<reco::Vertex>>              vtxToken;
        edm::EDGetTokenT<GenEventInfoProduct>                    genEventInfoToken;
        edm::EDGetTokenT<GenLumiInfoHeader>                      genLumiInfoToken;
        edm::EDGetTokenT<LHEEventProduct>                        lheEventInfoToken;
        //edm::EDGetTokenT<LHERunInfoProduct>                      lheRunInfoToken;
        edm::EDGetTokenT<std::vector<PileupSummaryInfo>>         pileUpToken;
        edm::EDGetTokenT<reco::GenParticleCollection>            genParticleToken;
        edm::EDGetTokenT<reco::GenParticleCollection>            particleLevelPhotonsToken;
        edm::EDGetTokenT<reco::GenJetCollection>                 particleLevelLeptonsToken;
        edm::EDGetTokenT<reco::GenJetCollection>                 particleLevelJetsToken;
        edm::EDGetTokenT<reco::GenJetCollection>                 genJetsToken;
        edm::EDGetTokenT<edm::ValueMap<float> >                  fragCP5BLToken;
        edm::EDGetTokenT<edm::ValueMap<float> >                  fragCP5BLdownToken;
        edm::EDGetTokenT<edm::ValueMap<float> >                  fragCP5BLupToken;
        edm::EDGetTokenT<edm::ValueMap<float> >                  fragCP5PetersonToken;
        edm::EDGetTokenT<edm::ValueMap<float> >                  fragCP5PetersondownToken;
        edm::EDGetTokenT<edm::ValueMap<float> >                  fragCP5PetersonupToken;
        edm::EDGetTokenT<reco::METCollection>                    particleLevelMetsToken;
        edm::EDGetTokenT<std::vector<pat::Muon>>                 muonToken;
        edm::EDGetTokenT<std::vector<pat::Electron>>             eleToken;
        edm::EDGetTokenT<std::vector<pat::Tau>>                  tauToken;
        edm::EDGetTokenT<std::vector<reco::GenJet>>              tauGenJetsToken;
        edm::EDGetTokenT<std::vector<pat::Photon>>               photonToken;
        edm::EDGetTokenT<std::vector<pat::PackedCandidate>>      packedCandidatesToken;                       //particle collection used to calculate isolation variables
        edm::EDGetTokenT<double>                                 rhoToken;
        edm::EDGetTokenT<std::vector<pat::MET>>                  metToken;
        edm::EDGetTokenT<std::vector<pat::MET>>                  metPuppiToken;
        edm::EDGetTokenT<std::vector<pat::Jet>>                  jetToken;
        edm::EDGetTokenT<std::vector<pat::Jet>>                  jetPuppiToken;
        edm::EDGetTokenT<std::vector<pat::Jet>>                  jetSmearedToken;
        edm::EDGetTokenT<std::vector<pat::Jet>>                  jetSmearedUpToken;
        edm::EDGetTokenT<std::vector<pat::Jet>>                  jetSmearedDownToken;
        edm::EDGetTokenT<edm::TriggerResults>                    recoResultsPrimaryToken;                     //MET filter information
        edm::EDGetTokenT<edm::TriggerResults>                    recoResultsSecondaryToken;                   //MET filter information (fallback if primary is not available)
        edm::EDGetTokenT<edm::TriggerResults>                    triggerToken;
        edm::EDGetTokenT<pat::PackedTriggerPrescales>            prescalesToken;
        edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> trigObjToken;
        edm::EDGetTokenT<bool>                                   ecalBadCalibFilterToken;
        edm::EDGetTokenT<double>                                 prefireWeightToken;
        edm::EDGetTokenT<double>                                 prefireWeightUpToken;
        edm::EDGetTokenT<double>                                 prefireWeightDownToken;
        edm::EDGetTokenT<double>                                 prefireWeightMuonToken;
        edm::EDGetTokenT<double>                                 prefireWeightMuonUpToken;
        edm::EDGetTokenT<double>                                 prefireWeightMuonDownToken;
        edm::EDGetTokenT<double>                                 prefireWeightECALToken;
        edm::EDGetTokenT<double>                                 prefireWeightECALUpToken;
        edm::EDGetTokenT<double>                                 prefireWeightECALDownToken;
        std::string                                              skim;
        bool                                                     sampleIsData;
        bool                                                     sampleIs2017;
        bool                                                     sampleIs2018;
        bool                                                     sampleIs2016preVFP;
        bool                                                     sampleIsFastSim;
        bool                                                     sampleIsSUSY;
        bool                                                     storeLheParticles;
        bool                                                     storeGenParticles;
        bool                                                     storeParticleLevel;
        bool                                                     storeBFrag;
        bool                                                     storeJecSourcesAll;
        bool                                                     storeJecSourcesGrouped;
        bool                                                     storeAllTauID;
        bool                                                     storePrefireComponents;
        bool                                                     storeJetSubstructure;

        virtual void beginJob() override;
        virtual void beginLuminosityBlock(const edm::LuminosityBlock&, const edm::EventSetup&) override;
        virtual void beginRun(const edm::Run&, edm::EventSetup const&) override;
        virtual void analyze(const edm::Event&, const edm::EventSetup&) override;

        virtual void endRun(const edm::Run&, edm::EventSetup const&) override {}                         //Unused functions
        virtual void endLuminosityBlock(const edm::LuminosityBlock&, const edm::EventSetup&) override {}
        virtual void endJob() override {};

        TriggerAnalyzer*       triggerAnalyzer;
        LeptonAnalyzer*        leptonAnalyzer;
        PhotonAnalyzer*        photonAnalyzer;
        JetAnalyzer*           jetAnalyzer;
        LheAnalyzer*           lheAnalyzer;
        GenAnalyzer*           genAnalyzer;
        ParticleLevelAnalyzer* particleLevelAnalyzer;
        BFragAnalyzer*         bFragAnalyzer;
        SUSYAnalyzer*          susyAnalyzer;

        edm::Service<TFileService> fs;                                                                   //Root tree and file for storing event info
        TTree* outputTree;

        unsigned long _runNb;
        unsigned long _lumiBlock;
        unsigned long _eventNb;
        unsigned      _nVertex;

        float _prefireWeight;
        float _prefireWeightUp;
        float _prefireWeightDown;
        float _prefireWeightMuon;
        float _prefireWeightMuonUp;
        float _prefireWeightMuonDown;
        float _prefireWeightECAL;
        float _prefireWeightECALUp;
        float _prefireWeightECALDown;

        TH1D* nVertices;                                                                                 //Histogram with number of vertices
};
#endif

//include CMSSW classes
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

//include ROOT classes
#include "TLorentzVector.h"

//include other parts of code 
#include "heavyNeutrino/multilep/interface/GenAnalyzer.h"
#include "heavyNeutrino/multilep/interface/GenTools.h"
#include "heavyNeutrino/multilep/interface/TauTools.h"

/*
 * Storing generator particles
 */

GenAnalyzer::GenAnalyzer(const edm::ParameterSet& iConfig, multilep* multilepAnalyzer):
    multilepAnalyzer(multilepAnalyzer){};

void GenAnalyzer::beginJob(TTree* outputTree){
    outputTree->Branch("_ttgEventType",              &_ttgEventType,              "_ttgEventType/i");
    outputTree->Branch("_zgEventType",               &_zgEventType,               "_zgEventType/i");
    outputTree->Branch("_gen_met",                   &_gen_met,                   "_gen_met/D");
    outputTree->Branch("_gen_metPhi",                &_gen_metPhi,                "_gen_metPhi/D");
    outputTree->Branch("_gen_nPh",                   &_gen_nPh,                   "_gen_nPh/i");
    outputTree->Branch("_gen_phStatus",              &_gen_phStatus,              "_gen_phStatus[_gen_nPh]/i");
    outputTree->Branch("_gen_phPt",                  &_gen_phPt,                  "_gen_phPt[_gen_nPh]/D");
    outputTree->Branch("_gen_phEta",                 &_gen_phEta,                 "_gen_phEta[_gen_nPh]/D");
    outputTree->Branch("_gen_phPhi",                 &_gen_phPhi,                 "_gen_phPhi[_gen_nPh]/D");
    outputTree->Branch("_gen_phE",                   &_gen_phE,                   "_gen_phE[_gen_nPh]/D");
    outputTree->Branch("_gen_phMomPdg",              &_gen_phMomPdg,              "_gen_phMomPdg[_gen_nPh]/I");
    outputTree->Branch("_gen_phIsPrompt",            &_gen_phIsPrompt,            "_gen_phIsPrompt[_gen_nPh]/O");
    outputTree->Branch("_gen_phMinDeltaR",           &_gen_phMinDeltaR,           "_gen_phMinDeltaR[_gen_nPh]/D");
    outputTree->Branch("_gen_phPassParentage",       &_gen_phPassParentage,       "_gen_phPassParentage[_gen_nPh]/O");
    outputTree->Branch("_gen_nL",                    &_gen_nL,                    "_gen_nL/i");
    outputTree->Branch("_gen_lPt",                   &_gen_lPt,                   "_gen_lPt[_gen_nL]/D");
    outputTree->Branch("_gen_lEta",                  &_gen_lEta,                  "_gen_lEta[_gen_nL]/D");
    outputTree->Branch("_gen_lPhi",                  &_gen_lPhi,                  "_gen_lPhi[_gen_nL]/D");
    outputTree->Branch("_gen_lE",                    &_gen_lE,                    "_gen_lE[_gen_nL]/D");
    outputTree->Branch("_gen_lVisPt",                &_gen_lVisPt,                "_gen_lVisPt[_gen_nL]/D");
    outputTree->Branch("_gen_lVisEta",               &_gen_lVisEta,               "_gen_lVisEta[_gen_nL]/D");
    outputTree->Branch("_gen_lVisPhi",               &_gen_lVisPhi,               "_gen_lVisPhi[_gen_nL]/D");
    outputTree->Branch("_gen_lVisE",                 &_gen_lVisE,                 "_gen_lVisE[_gen_nL]/D");
    outputTree->Branch("_gen_lFlavor",               &_gen_lFlavor,               "_gen_lFlavor[_gen_nL]/i");
    outputTree->Branch("_gen_lCharge",               &_gen_lCharge,               "_gen_lCharge[_gen_nL]/I");
    outputTree->Branch("_gen_lMomPdg",               &_gen_lMomPdg,               "_gen_lMomPdg[_gen_nL]/I");
    outputTree->Branch("_gen_lIsPrompt",             &_gen_lIsPrompt,             "_gen_lIsPrompt[_gen_nL]/O");
    outputTree->Branch("_gen_lDecayedHadr",          &_gen_lDecayedHadr,          "_gen_lDecayedHadr[_gen_nL]/O");
    outputTree->Branch("_gen_lMinDeltaR",            &_gen_lMinDeltaR,            "_gen_lMinDeltaR[_gen_nL]/D");
    outputTree->Branch("_gen_lPassParentage",        &_gen_lPassParentage,        "_gen_lPassParentage[_gen_nL]/O");

    if(multilepAnalyzer->storeGenParticles){
      outputTree->Branch("_gen_n",                                        &_gen_n,                                        "_gen_n/I");
      outputTree->Branch("_gen_pt",                                       &_gen_pt,                                       "_gen_pt[_gen_n]/D");
      outputTree->Branch("_gen_eta",                                      &_gen_eta,                                      "_gen_eta[_gen_n]/D");
      outputTree->Branch("_gen_phi",                                      &_gen_phi,                                      "_gen_phi[_gen_n]/D");
      outputTree->Branch("_gen_E",                                        &_gen_E,                                        "_gen_E[_gen_n]/D");
      outputTree->Branch("_gen_pdgId",                                    &_gen_pdgId,                                    "_gen_pdgId[_gen_n]/I");
      outputTree->Branch("_gen_charge",                                   &_gen_charge,                                   "_gen_charge[_gen_n]/I");
      outputTree->Branch("_gen_status",                                   &_gen_status,                                   "_gen_status[_gen_n]/I");
      outputTree->Branch("_gen_isPromptFinalState",                       &_gen_isPromptFinalState,                       "_gen_isPromptFinalState[_gen_n]/O");
      outputTree->Branch("_gen_isDirectPromptTauDecayProductFinalState",  &_gen_isDirectPromptTauDecayProductFinalState,  "_gen_isDirectPromptTauDecayProductFinalState[_gen_n]/O");
      outputTree->Branch("_gen_isLastCopy",                               &_gen_isLastCopy,                               "_gen_isLastCopy[_gen_n]/O");
      outputTree->Branch("_gen_index",                                    &_gen_index,                                    "_gen_index[_gen_n]/I");
      outputTree->Branch("_gen_motherIndex",                              &_gen_motherIndex,                              "_gen_motherIndex[_gen_n]/I");
      outputTree->Branch("_gen_daughter_n",                               &_gen_daughter_n,                               "_gen_daughter_n[_gen_n]/I");
      outputTree->Branch("_gen_daughterIndex",                            &_gen_daughterIndex,                            "_gen_daughterIndex[_gen_n][10]/I");
    }   
}

void GenAnalyzer::analyze(const edm::Event& iEvent){
    edm::Handle<std::vector<reco::GenParticle>> genParticles = getHandle(iEvent, multilepAnalyzer->genParticleToken);
    edm::Handle<std::vector<reco::GenJet>> tauGenJets = getHandle(iEvent, multilepAnalyzer->tauGenJetsToken);

    if(!genParticles.isValid()) return;

    // TODO: when applying overlap for new photon samples: check the pt and eta cuts of the photon
    _ttgEventType = overlapEventType(*genParticles, 10., 5.0, 0.1);
    _zgEventType  = overlapEventType(*genParticles, 15., 2.6, 0.05);

    _gen_nL = 0;
    _gen_nPh = 0;
    _gen_n = 0;
    TLorentzVector genMetVector(0,0,0,0);
    for(const reco::GenParticle& p : *genParticles){
        int absId = abs(p.pdgId());

        //Calculate generator level MET
        if(p.status() == 1){
            if(absId == 12 or absId == 14 or absId == 16 or absId == 1000022){
                TLorentzVector nuVect;
                nuVect.SetPtEtaPhiE(p.pt(), p.eta(), p.phi(), p.energy());
                genMetVector += nuVect;
            }
        }

        //store generator level lepton info
        if((p.status() == 1 and (absId == 11 or absId == 13)) || (p.status() == 2 and p.isLastCopy() and absId == 15)){
            if(_gen_nL != gen_nL_max){
                _gen_lPt[_gen_nL]               = p.pt();
                _gen_lEta[_gen_nL]              = p.eta();
                _gen_lPhi[_gen_nL]              = p.phi();
                _gen_lE[_gen_nL]                = p.energy();
                _gen_lCharge[_gen_nL]           = p.charge();
                _gen_lIsPrompt[_gen_nL]         = GenTools::isPrompt(p, *genParticles); 
                _gen_lMomPdg[_gen_nL]           = GenTools::getMother(p, *genParticles)->pdgId();
                _gen_lDecayedHadr[_gen_nL]      = TauTools::decayedHadronically(p, *genParticles);
                _gen_lMinDeltaR[_gen_nL]     = GenTools::getMinDeltaR(p, *genParticles);
                _gen_lPassParentage[_gen_nL] = GenTools::passParentage(p, *genParticles);

                if(absId == 11 or absId == 13){
                    _gen_lVisPt[_gen_nL]               = p.pt();
                    _gen_lVisEta[_gen_nL]              = p.eta();
                    _gen_lVisPhi[_gen_nL]              = p.phi();
                    _gen_lVisE[_gen_nL]                = p.energy();
                } else {
                    const reco::GenJet* matchedGenJet = TauTools::findMatchedGenJet(p, *tauGenJets);
                    if(matchedGenJet != nullptr){
                        _gen_lVisPt[_gen_nL]               = matchedGenJet->pt();
                        _gen_lVisEta[_gen_nL]              = matchedGenJet->eta();
                        _gen_lVisPhi[_gen_nL]              = matchedGenJet->phi();
                        _gen_lVisE[_gen_nL]                = matchedGenJet->energy();
                    } else {
                        _gen_lVisPt[_gen_nL]               = p.pt();
                        _gen_lVisEta[_gen_nL]              = p.eta();
                        _gen_lVisPhi[_gen_nL]              = p.phi();
                        _gen_lVisE[_gen_nL]                = p.energy();
                    }
                }


                if(absId == 11)      _gen_lFlavor[_gen_nL] = 0;
                else if(absId == 13) _gen_lFlavor[_gen_nL] = 1;
                else                 _gen_lFlavor[_gen_nL] = 2;
                ++_gen_nL;
            }
        }

        //store generator level photon info
        if((p.status() == 1 or p.status() == 71) and absId == 22){
            if(_gen_nPh != gen_nPh_max){
                _gen_phStatus[_gen_nPh]        = p.status();
                _gen_phPt[_gen_nPh]            = p.pt();
                _gen_phEta[_gen_nPh]           = p.eta();
                _gen_phPhi[_gen_nPh]           = p.phi();
                _gen_phE[_gen_nPh]             = p.energy();
                _gen_phIsPrompt[_gen_nPh]      = p.isPromptFinalState();
                _gen_phMomPdg[_gen_nPh]        = GenTools::getMother(p, *genParticles)->pdgId();
                _gen_phMinDeltaR[_gen_nPh]     = GenTools::getMinDeltaR(p, *genParticles);
                _gen_phPassParentage[_gen_nPh] = GenTools::passParentage(p, *genParticles);
                ++_gen_nPh;
            } 
        }

        //store all generator level particles
        if(multilepAnalyzer->storeGenParticles){        
          int indexGen = _gen_n;

          if(_gen_n == gen_n_max){
            throw cms::Exception ("GenAnalyzer") << "Reaching the max number of stored gen particles (" << gen_n_max << ")\n";
          }
       
          int nDaughters = p.numberOfDaughters();
        
          _gen_daughter_n[_gen_n] = nDaughters;
        
          for(int d=0;d<nDaughters;++d){
            _gen_daughterIndex[_gen_n][d] = p.daughterRef(d).key();
          }
        
          _gen_pt[_gen_n]                                      = p.pt();
          _gen_eta[_gen_n]                                     = p.eta();
          _gen_phi[_gen_n]                                     = p.phi();
          _gen_E[_gen_n]                                       = p.energy();
          _gen_pdgId[_gen_n]                                   = p.pdgId();
          _gen_charge[_gen_n]                                  = p.charge();
          _gen_status[_gen_n]                                  = p.status();
          _gen_isPromptFinalState[_gen_n]                      = p.isPromptFinalState();
          _gen_isDirectPromptTauDecayProductFinalState[_gen_n] = p.isDirectPromptTauDecayProductFinalState();
          _gen_isLastCopy[_gen_n]                              = p.isLastCopy();
          _gen_index[_gen_n]                                   = indexGen;
          _gen_motherIndex[_gen_n]                             = GenTools::getFirstMotherIndex(p, *genParticles);
          ++_gen_n;
        }
    }   

    _gen_met    = genMetVector.Pt();
    _gen_metPhi = genMetVector.Phi();

}



/*
 * Some event categorization in order to understand/debug/apply overlap removal for TTGamma <--> TTJets and similar photon samples
 */
unsigned GenAnalyzer::overlapEventType(const std::vector<reco::GenParticle>& genParticles, double ptCut, double etaCut, double genCone) const{
    int type = 0;
    for(auto p = genParticles.cbegin(); p != genParticles.cend(); ++p){
        if(p->status()<0)         continue;
        if(p->pdgId()!=22)        continue;
        type = std::max(type, 1);                                                            // Type 1: final state photon found in genparticles with generator level cuts
        if(p->pt()<ptCut)         continue;
        if(fabs(p->eta())>etaCut) continue;
        type = std::max(type, 2);                                                            // Type 2: photon from pion or other meson

        if(GenTools::getMinDeltaRTTG(*p, genParticles) < genCone) continue;
        if(not GenTools::noMesonsInChain(*p, genParticles))  continue;

        // Everything below is *signal*
        std::set<int> decayChain;
        GenTools::setDecayChain(*p, genParticles, decayChain);
        const reco::GenParticle* mom = GenTools::getMother(*p, genParticles);
        if(std::any_of(decayChain.cbegin(), decayChain.cend(), [](const int entry){ return abs(entry) == 24;})){
            if(abs(mom->pdgId()) == 24)     type = std::max(type, 6);      // Type 6: photon directly from W or decay products which are part of ME
            else if(abs(mom->pdgId()) <= 6) type = std::max(type, 4);      // Type 4: photon from quark from W (photon from pythia, rarely)
            else                            type = std::max(type, 5);      // Type 5: photon from lepton from W (photon from pythia)
        } else {
            if(abs(mom->pdgId()) == 6)      type = std::max(type, 7);      // Type 7: photon from top
            else if(abs(mom->pdgId()) == 5) type = std::max(type, 3);      // Type 3: photon from b
            else                            type = std::max(type, 8);      // Type 8: photon from ME
        }
    }

    return type;
}

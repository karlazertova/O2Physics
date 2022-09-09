#include "Framework/runDataProcessing.h"
#include "Framework/AnalysisTask.h"
#include "Common/DataModel/EventSelection.h"

using namespace o2;
using namespace o2::framework;

struct myFirstHFTask {
    HistogramRegistry registry{"registry",{
            {"etaBefore", "eta before selection", {HistType::kTH1F, {{100, 0, 1}}}},
            {"etaAfter", "eta after selection", {HistType::kTH1F, {{100, 0, 1}}}}
        }
    };
    void process(soa::Join<aod::Collisions, aod::EvSels>::iterator const& collision, aod::Tracks const& tracks){

	// fill histogram of collision vertex z

        registry.get<TH1>(HIST("etaBefore"))->Fill(collision.posZ());	

	// event selection

        if (!collision.alias()[kINT7]) {
        return;
	}       // trigger selection

	if (!collision.sel7()) {
	return;
	} // rejection of background (beam-gas events, pileup)

	if (std::abs(collision.posZ()) > 10) {
	return;
	} // cut on collision vertex in z direction


	// fill histogram of collision vertex z
 	registry.get<TH1>(HIST("etaAfter"))->Fill(collision.posZ());
        
	for (auto track : tracks){
		// track selection
            	
		registry.get<TH1>(HIST("etaAfter"))->Fill(track.eta());
        }
    }
};


WorkflowSpec defineDataProcessing(ConfigContext const& cfgc)
{
  return WorkflowSpec{
    adaptAnalysisTask<myFirstHFTask>(cfgc),
  };
}

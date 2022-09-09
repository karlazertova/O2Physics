#include "Framework/runDataProcessing.h"
#include "Framework/AnalysisTask.h"

using namespace o2;
using namespace o2::framework;

struct myFirstHFTask(){
    HistogramRegistry registry{"registry"{
            "eta", "pseudorapidity", {HistType::kTH1k, {{100, 0, 1}}}
        }
    };
    void process(aod::Collision const&, aod::Tracks const& tracks){
        registry.fill<aod::track::Eta>(HIST("eta"), tracks, aod::track::eta > 0.0f);
        registry.fill<aod::track::Eta>(HIST("eta"), tracks, aod::track::eta < 1.0f);
        for (auto Track : tracks){
            registry.get<TH1>(HIST(eta))->Fill(track.eta());
        }
    }
};


WorkflowSpec defineDataProcessing(ConfigContext const& cfgc)
{
  return WorkflowSpec{
    adaptAnalysisTask<myFirstHFTask>(cfgc),
  };
}

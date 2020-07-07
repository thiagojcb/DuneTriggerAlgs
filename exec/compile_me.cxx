#include "dune-triggers/Trivial/TriggerCandidateMaker_Trivial.hh"
#include "dune-triggers/Trivial/TriggerDecisionMaker_Trivial.hh"
#include "dune-triggers/Supernova/TriggerCandidateMaker_Supernova.hh"
#include <string>

int main()
{
  std::string s;
  TriggerCandidateMakerTrivial trivial(s);
  (void) trivial;
  TriggerDecisionMakerTrivial trivial2(s);
  (void) trivial2;
  TriggerCandidateMakerSupernova super(s);
  (void) super;
  
  return 0;
}

#include "dune-triggers/Trivial/TriggerCandidateMaker_Trivial.hpp"
#include "dune-triggers/Trivial/TriggerDecisionMaker_Trivial.hpp"
#include "dune-triggers/Supernova/TriggerCandidateMaker_Supernova.hpp"
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

# DuneTriggers
A place to put the trigger algorithms for DUNE. This code can then be linked inside ArtDAQ and LArSoft, so that we can
run the exact same code in simulation and on real data.

## Organisation
The code is quite simple. Essentially, the trigger algorithm rely on 3 structs:
 - `TriggerPrimitive` (also known as hits)
 - `TriggerCandidate` (clusters)
 - `TriggerDecision`
 
Their format will be discussed at a DAQ meeting and fixed at some point.

The trigger primitives are created within ArtDAQ or LArSoft. These are passed to one or more `TriggerCandidateMaker`
classes which create the `TriggerCandidates`. The `TriggerCandidates` are then passed on to one or more
`TriggerDecisionMaker` classes, which create the decisions. Both rely on their pure virtual function
 - `std::vector<TriggerCandidate> TriggerCandidateMaker::MakeCandidate(std::vector<TriggerPrimitive>&)`
 - `std::vector<TriggerDecision> TriggerDecisionMaker::MakeDecision(std::vector<TriggerCandidate>&)`

That any `TriggerCandidateMaker` and `TriggerDecisionMaker` need to implement, respectively. These functions do all
the work, they should be reasonably fast to handle the rate at which their input arrive in the real system.

Note none the granularity of the `TriggerCandidateMaker` and `TriggerDecisionMaker` isn't be decided here.
It is the ArtDAQ (and LArSoft)'s developers' job to decided how many `TriggerCandidateMakers` there should be in
one APA for example. The focus of this library is the algorithm, ArtDAQ and LArSoft should create and handle the
DuneTriggers objects and the calls to their `MakeCandidate` or `MakeDecision` function.


## To compile it
You need to have the boost libraries for testing.
```
git clone https://github.com/plasorak/DuneTriggers.git
cd DuneTriggers
mkdir build
cd build
cmake ../
make -j`nproc`
ctest # if you want to run the tests
```

## To contribute
Fork this repo.

## More details on the structs
### TriggerPrimitive
This struct represent hits, it contains:
 - The time of the hit
 - The time of the peak ADC
 - The time over threshold
 - The channel number of the hit
 - The APA number
 - The ADC peak
 - The ADC integral
 
### TriggerCandidate
Represents a cluster of hits, it contains:
 - The time at which the cluster started
 - The time at which it ended
 - The central time (peak time)
 - The first channel to be hit
 - The last channel to be hit
 - The list of APAs
 - The ADC integral
 - The ADC peak
 
### TriggerDecision
contains:
 - The time at which the readout should start
 - The time at which the readout should end
 - The time at which the decision was made
 - What APA should be readout with a bitfield. Each bitfield index correspond to an APA, when the byte is high, that means
 that APA should be readout, for example: `000 001` means that the APA 0 should be readout in a configuration where there is
 only 6 APAs.

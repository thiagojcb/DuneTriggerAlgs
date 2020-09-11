# DuneTriggers
A place to put the trigger algorithms for DUNE. This code can then be
linked inside ArtDAQ and LArSoft, so that we can run the exact same
code in simulation and on real data.

### TOC
 - [Future](#future)
 - [Organisation](#organisation)
 - [Compile](#compile)
 - [Contribute](#contribute)
 - [Data structures](#structs)

<a name="future">

## Future interesting things to do
 - Make it compatible with the new schema for triggering (rather than having TPs, TCs, TDs have TPs, TAs, TCs, TDs) *NB: my understanding of how things work*:
   - new TAs = TC now, (APA level)
   - new TCs = TDs now, (?? level, module level?)
   - new TDs = spits back TCs in the case of SN where you only have one type of TCs. (module level).
 - Expend data objects
   - Something that can "trace back" TPs from TAs
   - Add flags that say what object it is (version of the algorithm, TCs what trigger it is)
 - Make the whole setup more realistic
   - TPs from PDFs of what we expect from LArSoft/simulations
   - TAs algorithm better
 - Find a way to estimate the efficiency for TAs and TCs.
 - Implementation of "TP window" and "TP zipper":
   - TP window = something that ensures that the TPs are all in a time window,
   - TP zipper = something that merges source of TPs.


<a name="organisation"/>

## Organisation
The code is quite simple. Essentially, the trigger algorithm rely on 3
structs:
 - `TriggerPrimitive` (also known as hits)
 - `TriggerCandidate` (clusters)
 - `TriggerDecision`
 
Their format will be discussed at a DAQ meeting and fixed at some point.

The trigger primitives are created within ArtDAQ or LArSoft. These are
passed to one or more `TriggerCandidateMaker` classes which create the
`TriggerCandidates`. The `TriggerCandidates` are then passed on to one
or more `TriggerDecisionMaker` classes, which create the
decisions. Each rely on their pure virtual operator:
 - `void TriggerCandidateMaker::operator()(const TriggerPrimitive& input_tp, std::vector<TriggerCandidate>& output_tc)`
 - `void TriggerDecisionMaker::operator()(const TriggerCandidate& input_tp, std::vector<TriggerDecision>& output_tc)`

that any `TriggerCandidateMaker` and
`TriggerDecisionMaker` need to implement, respectively.

Note the TPs can also be created here, but given how this happens now
in real life, it doesn't look like these libraries will be used for
creating TPs (the data structures for the raw data are very
complicated and closely tied to ArtDAQ, that is not so much the case
in LArSoft), hence the `TriggerPrimitiveMaker` class exists with its
corresponding operator:
- `void TriggerPrimitiveMaker::operator()(const void* data, std::vector<TriggerPrimitive>& tps)`

but that may not necessarily be used.

These operators do all the work, they should be reasonably
fast to handle the rate at which their input arrive in the real
system. The "makers" get input data, rearrange it, and then
`push_back` to the output vector. An example is available in
`src/trivial/TriggerCandidateMaker_trivial.hh`. It can be tested with
a `exec/run_trivial_candidate.cxx`, which creates fake TPs, feeds
them into it and then dumps them in a csv.

Note none the granularity of the `TriggerCandidateMaker` and
`TriggerDecisionMaker` isn't be decided here.  It is the ArtDAQ (and
LArSoft)'s developers' job to decided how many
`TriggerCandidateMakers` there should be in one APA for example. The
focus of this library is the algorithm, ArtDAQ and LArSoft should
create and handle the DuneTriggers objects and the calls to them. The
classes `NaiveTriggerQueue` and `NaiveTriggerCandidateConsumer` that
`run_trivial_candidate.cxx` are indicative.

<a name="compile"/>

## To compile it
You need to have the boost libraries for testing.
```
git clone https://github.com/plasorak/DuneTriggers.git
cd DuneTriggers
mkdir build
cd build
cmake ../
make -j`nproc`
ctest # if you want to run the tests, right now it doesn't do anything interesting
```

<a name="contribute"/>

## To contribute
Fork this repo.

<a name="structs"/>

## More details on the structs
Note all the times here refer to 50 MHz clock (since epoch), as is now standard in DUNE.

### TriggerPrimitive
This struct represent hits, it contains:
| Variable              | Type       | Comment                                                          |
|-----------------------|------------|------------------------------------------------------------------|
| `time_start`          | `int64_t`  | Start time                                                       |
| `time_peak`           | `int64_t`  | Time of the peak ADC                                             |
| `time_over_threshold` | `int32_t`  | Time over threshold                                              |
| `channel`             | `uint32_t` | Channel number                                                   |
| `adc_integral`        | `uint16_t` | ADC integral                                                     |
| `adc_peak`            | `uint16_t` | ADC peak                                                         |
| `detid`               | `uint32_t` | detid (a flag that represents the detector which created the TP) |
| `flag`                | `uint32_t` | extra flags                                                      |

### TriggerCandidate
Represents a cluster of hits, it contains:
| Variable        | Type       | Comment                                                         |
|-----------------|------------|-----------------------------------------------------------------|
| `time_start`    | `int64_t`  | Start time                                                      |
| `time_end`      | `int64_t`  | End time                                                        |
| `time_peak`     | `int64_t`  | Time where ADC the highest                                      |
| `channel_start` | `uint32_t` | Start channel                                                   |
| `channel_end`   | `uint32_t` | End channel                                                     |
| `channel_peak`  | `uint32_t` | Channel of the highest ADC                                      |
| `adc_integral`  | `uint16_t` | ADC integral                                                    |
| `adc_peak`      | `uint16_t` | ADC peak                                                        |
| `detid`         | `uint32_t` | detid (a flag that represents the detector in which it ocurred) |
| `flag`          | `uint32_t` | extra flags                                                     |
 
### TriggerDecision
contains:
| Variable         | Type       | Comment                                                              |
|------------------|------------|----------------------------------------------------------------------|
| `time_start`     | `int64_t`  | Time at which to start the readout                                   |
| `time_end`       | `int64_t`  | Time at which to end the readout                                     |
| `time_triggered` | `int64_t`  | Time at which this decision was taken                                |
| `detid`          | `uint32_t` | detid (a flag that represents which part of the detector to readout) |
| `flag`           | `uint32_t` | extra flags                                                          |

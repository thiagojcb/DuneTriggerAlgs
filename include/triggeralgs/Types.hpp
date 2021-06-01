/**
 * @file Types.hpp
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef TRIGGERALGS_INCLUDE_TRIGGERALGS_TYPES_HPP_
#define TRIGGERALGS_INCLUDE_TRIGGERALGS_TYPES_HPP_

#include <cstdint>

namespace triggeralgs {

// A data timestamp in timing system clock ticks (50 MHz for
// ProtoDUNE-I, 62.5 MHz for ProtoDUNE-II and DUNE FD). Ideally we
// would get this definition from somewhere else, but we don't have a
// package that we depend on that provides it
using timestamp_t = uint64_t; // NOLINT

using timestamp_diff_t = int64_t;

// A logical region of the detector from which DS objects may be
// formed, eg an APA or a module
//
// TODO P. Rodrigues 2021-06-01: it would be nice to have this be just
// dataformats::GeoID, if/when we can depend on the dataformats
// package
using detid_t = uint16_t;

// A channel number
using channel_t = int32_t;

enum class candidate_alg_t {
  kUnknown = 0,
  kSupernova = 1,
  kHSIEventToTriggerCandidate = 2
};

enum class primitive_alg_t {
  kUnknown = 0,
  kDefaultTPCPrimitiveAlgorithm = 1
};

enum class activity_alg_t {
  kUnknown = 0,
  kSupernova = 1
};

// Names for each of the bits in the TriggerPrimitiveFlags
enum class PrimitiveFlagsBits {
  kSomehowBad = 0,
  kSomeOtherHowBad = 1,
  kUnassigned2 = 2,
  kUnassigned3 = 3,
  kUnassigned4 = 4,
  kUnassigned5 = 5,
  kUnassigned6 = 6,
  kUnassigned7 = 7,
  kUnassigned8 = 8,
  kUnassigned9 = 9,
  kUnassigned10 = 10,
  kUnassigned11 = 11,
  kUnassigned12 = 12,
  kUnassigned13 = 13,
  kUnassigned14 = 14,
  kUnassigned15 = 15,
};

// A bitmask of flags from PrimitiveFlagsBits OR'ed together
using primitive_flags_t = uint16_t;

} // namespace triggeralgs

#endif // TRIGGERALGS_INCLUDE_TRIGGERALGS_TRIGGERCANDIDATEMAKER_HPP_

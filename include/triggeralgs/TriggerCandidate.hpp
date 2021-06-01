/**
 * @file TriggerCandidate.hpp
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef TRIGGERALGS_INCLUDE_TRIGGERALGS_TRIGGERCANDIDATE_HPP_
#define TRIGGERALGS_INCLUDE_TRIGGERALGS_TRIGGERCANDIDATE_HPP_

#include "triggeralgs/TriggerActivity.hpp"
#include "triggeralgs/TriggerCandidateType.hpp"
#include "triggeralgs/Types.hpp"

#include <cstdint>
#include <vector>

namespace triggeralgs {
struct TriggerCandidate
{
  timestamp_t time_start = { 0 };
  timestamp_t time_end = { 0 };
  timestamp_t time_candidate = { 0 };
  std::vector<detid_t> detid; // NOLINT(build/unsigned)
  TriggerCandidateType type = TriggerCandidateType::kUnknown;
  candidate_alg_t algorithm = candidate_alg_t::kUnknown; // NOLINT(build/unsigned)
  uint16_t version = { 0 };   // NOLINT(build/unsigned)

  std::vector<TriggerActivity> ta_list;
};

} // namespace triggeralgs

#endif // TRIGGERALGS_INCLUDE_TRIGGERALGS_TRIGGERCANDIDATE_HPP_

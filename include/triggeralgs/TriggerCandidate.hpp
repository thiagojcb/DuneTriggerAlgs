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

#include <cstdint>
#include <vector>

namespace triggeralgs {
struct TriggerCandidate
{
  int64_t time_start = { 0 };
  int64_t time_end = { 0 };
  int64_t time_candidate = { 0 };
  std::vector<uint16_t> detid = { 0 }; // NOLINT(build/unsigned)
  TriggerCandidateType type = TriggerCandidateType::kUnknown;
  uint32_t algorithm = { 0 }; // NOLINT(build/unsigned)
  uint16_t version = { 0 };   // NOLINT(build/unsigned)

  std::vector<TriggerActivity> ta_list;
};

} // namespace triggeralgs

#endif // TRIGGERALGS_INCLUDE_TRIGGERALGS_TRIGGERCANDIDATE_HPP_

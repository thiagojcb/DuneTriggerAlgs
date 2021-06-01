/**
 * @file TriggerActivity.hpp
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef TRIGGERALGS_INCLUDE_TRIGGERALGS_TRIGGERACTIVITY_HPP_
#define TRIGGERALGS_INCLUDE_TRIGGERALGS_TRIGGERACTIVITY_HPP_

#include "triggeralgs/Types.hpp"
#include "triggeralgs/TriggerPrimitive.hpp"
#include <cstdint>
#include <vector>

namespace triggeralgs {

enum class TriggerActivityType {
  kUnknown = 0,
  kTPCTriggerActivity = 1,
  kPDSTriggerActivity = 2,
};

struct TriggerActivity
{
  timestamp_t time_start = { 0 };
  timestamp_t time_end = { 0 };
  timestamp_t time_peak = { 0 };
  timestamp_t time_activity = { 0 };
  channel_t channel_start = { 0 }; // NOLINT(build/unsigned)
  channel_t channel_end = { 0 };   // NOLINT(build/unsigned)
  channel_t channel_peak = { 0 };  // NOLINT(build/unsigned)
  uint64_t adc_integral = { 0 };  // NOLINT(build/unsigned)
  uint16_t adc_peak = { 0 };      // NOLINT(build/unsigned)
  detid_t detid = { 0 };         // NOLINT(build/unsigned)
  TriggerActivityType type = TriggerActivityType::kUnknown;          // NOLINT(build/unsigned)
  activity_alg_t algorithm = activity_alg_t::kUnknown;     // NOLINT(build/unsigned)
  uint16_t version = { 0 };       // NOLINT(build/unsigned)

  std::vector<TriggerPrimitive> tp_list;
};

} // namespace triggeralgs

#endif // TRIGGERALGS_INCLUDE_TRIGGERALGS_TRIGGERACTIVITY_HPP_

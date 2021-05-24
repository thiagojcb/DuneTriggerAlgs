/**
 * @file TriggerActivity.hpp
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef TRIGGERALGS_INCLUDE_TRIGGERALGS_TRIGGERACTIVITY_HPP_
#define TRIGGERALGS_INCLUDE_TRIGGERALGS_TRIGGERACTIVITY_HPP_

#include "triggeralgs/TriggerPrimitive.hpp"
#include <cstdint>
#include <vector>

namespace triggeralgs {
struct TriggerActivity
{
  int64_t time_start = { 0 };
  int64_t time_end = { 0 };
  int64_t time_peak = { 0 };
  int64_t time_activity = { 0 };
  uint16_t channel_start = { 0 }; // NOLINT(build/unsigned)
  uint16_t channel_end = { 0 };   // NOLINT(build/unsigned)
  uint16_t channel_peak = { 0 };  // NOLINT(build/unsigned)
  uint64_t adc_integral = { 0 };  // NOLINT(build/unsigned)
  uint16_t adc_peak = { 0 };      // NOLINT(build/unsigned)
  uint16_t detid = { 0 };         // NOLINT(build/unsigned)
  uint32_t type = { 0 };          // NOLINT(build/unsigned)
  uint32_t algorithm = { 0 };     // NOLINT(build/unsigned)
  uint16_t version = { 0 };       // NOLINT(build/unsigned)

  std::vector<TriggerPrimitive> tp_list;
};

} // namespace triggeralgs

#endif // TRIGGERALGS_INCLUDE_TRIGGERALGS_TRIGGERACTIVITY_HPP_

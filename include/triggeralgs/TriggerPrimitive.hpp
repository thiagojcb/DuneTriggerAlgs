/**
 * @file TriggerDecisionMaker.hpp
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef TRIGGERALGS_INCLUDE_TRIGGERALGS_TRIGGERPRIMITIVE_HPP_
#define TRIGGERALGS_INCLUDE_TRIGGERALGS_TRIGGERPRIMITIVE_HPP_

#include <cstdint>

namespace triggeralgs {
struct TriggerPrimitive
{
  int64_t time_start = { 0 };
  int64_t time_peak = { 0 };
  int32_t time_over_threshold = { 0 };
  uint16_t channel = { 0 };      // NOLINT(build/unsigned)
  uint32_t adc_integral = { 0 }; // NOLINT(build/unsigned)
  uint16_t adc_peak = { 0 };     // NOLINT(build/unsigned)
  uint16_t detid = { 0 };        // NOLINT(build/unsigned)
  uint16_t type = { 0 };         // NOLINT(build/unsigned)
  uint16_t algorithm = { 0 };    // NOLINT(build/unsigned)
  uint16_t version = { 0 };      // NOLINT(build/unsigned)
  uint32_t flag = { 0 };         // NOLINT(build/unsigned)
};
} // namespace triggeralgs

#endif // TRIGGERALGS_INCLUDE_TRIGGERALGS_TRIGGERPRIMITIVE_HPP_

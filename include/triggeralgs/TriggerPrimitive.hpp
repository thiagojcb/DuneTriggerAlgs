/**
 * @file TriggerDecisionMaker.hpp
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef TRIGGERALGS_INCLUDE_TRIGGERALGS_TRIGGERPRIMITIVE_HPP_
#define TRIGGERALGS_INCLUDE_TRIGGERALGS_TRIGGERPRIMITIVE_HPP_

#include "triggeralgs/Types.hpp"

#include <cstdint>

namespace triggeralgs {

enum class TriggerPrimitiveType {
  kUnknown = 0,
  kTPCTriggerPrimitive = 1,
  kPDSTriggerPrimitive = 2,
};

struct TriggerPrimitive
{
  timestamp_t time_start = { 0 };
  timestamp_t time_peak = { 0 };
  timestamp_t time_over_threshold = { 0 };
  channel_t channel = { 0 };      // NOLINT(build/unsigned)
  uint32_t adc_integral = { 0 }; // NOLINT(build/unsigned)
  uint16_t adc_peak = { 0 };     // NOLINT(build/unsigned)
  detid_t detid = { 0 };        // NOLINT(build/unsigned)
  TriggerPrimitiveType type = TriggerPrimitiveType::kUnknown;         // NOLINT(build/unsigned)
  primitive_alg_t algorithm = primitive_alg_t::kUnknown;    // NOLINT(build/unsigned)
  uint16_t version = { 0 };      // NOLINT(build/unsigned)
  primitive_flags_t flag = { 0 };         // NOLINT(build/unsigned)
};
} // namespace triggeralgs

#endif // TRIGGERALGS_INCLUDE_TRIGGERALGS_TRIGGERPRIMITIVE_HPP_

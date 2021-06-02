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

#include <cstddef>
#include <cstdint>
#include <bitset>

namespace triggeralgs {

/**
 * @brief A single energy deposition on a TPC or PDS channel
 */
struct TriggerPrimitive
{
  /**
   * @brief The type of a TriggerPrimitive
   */
  enum class Type {
    kUnknown = 0,
    kTPC = 1,
    kPDS = 2,
  };

  /**
   * @brief The algorithm used to form a TriggerPrimitive
   */
  enum class Algorithm {
    kUnknown = 0,
    kTPCDefault = 1
  };

  /**
   * Names for each of the bits in the TriggerPrimitive Flags
   */
  enum class FlagBits {
    kSomehowBad = 0,
    kUnassigned1 = 1,
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

  /**
   * @brief A bitmask of flags from PrimitiveFlagsBits OR'ed together
   *
   * (a std::bitset<> would be nicer, but we don't have code to serialize it yet)
   */
  using Flags = uint16_t;

  /**
   * @brief Set/reset a flag in this TriggerPrimitive
   *
   * @param b The flag bit to set
   * @param value The value to set the flag to
   */
  void set_flag(FlagBits b, bool value=true)
  {
    if(value){
      flag |= (1u << static_cast<Flags>(b));
    }
    else{
      flag &= ~(1u << static_cast<Flags>(b));
    }
  }
  
  timestamp_t time_start = { 0 };
  timestamp_t time_peak = { 0 };
  timestamp_t time_over_threshold = { 0 };
  channel_t channel = { 0 };
  uint32_t adc_integral = { 0 }; // NOLINT(build/unsigned)
  uint16_t adc_peak = { 0 };     // NOLINT(build/unsigned)
  detid_t detid = { 0 };
  Type type = Type::kUnknown;
  Algorithm algorithm = Algorithm::kUnknown;
  uint16_t version = { 0 };      // NOLINT(build/unsigned)
  Flags flag = { 0 };
};
} // namespace triggeralgs

#endif // TRIGGERALGS_INCLUDE_TRIGGERALGS_TRIGGERPRIMITIVE_HPP_

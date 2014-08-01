//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#pragma once

#include <cstdint>

namespace minesense
{
namespace protocol
{
//! @brief Packet type.
enum class PacketType : std::uint8_t
{
	header = 0x00, //! Header in UTF-8 XML
	data = 0x01 //! binary data (according to header)
};

//! @brief Start packet byte
static const std::uint8_t start = 0x02;

//! @brief End packet byte
static const std::uint8_t end = 0x03;

}
}

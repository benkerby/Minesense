//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#pragma once

#include <QString>
#include <boost/optional.hpp>
#include <vector>
#include "core_export.h"

namespace minesense
{
//! @brief Physical units
enum class Units
{
	degreesCelsius, //!< degrees Celsius
	seconds, //!< SI seconds
	milliseconds //!< SI milliseconds
};

//! @brief Convert the given unit to string.
//! @return String representation of the unit.
//! @throws std::runtime_error if the enum value is not valid.
CORE_EXPORT QString unitsToString(Units unit /*!< a valid enum value */);
//! @brief Convert the given string to a unit.
//! @return Unit if the string is recognized, otherwise boost::none.
CORE_EXPORT boost::optional< Units > unitsFromString(const QString& unit);
//! @brief Get all the known units.
//! @return Vector containing all units.
CORE_EXPORT std::vector< Units > allUnits();

}

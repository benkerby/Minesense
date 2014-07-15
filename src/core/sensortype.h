//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#pragma once

#include <QString>
#include <boost/optional.hpp>
#include <vector>
#include "core_export.h"

namespace minesense
{
//! @brief Sensor type.
enum class SensorType
{
	XRF,
	EMS,
	LIBS
};

//! @brief Convert the given sensor type to string.
//! @return String representation of the sensor type.
//! @throws std::runtime_error if the enum value is not valid.
CORE_EXPORT QString sensorToString(SensorType type);
//! @brief Convert the given string to a sensor type.
//! @return Unit if the string is recognized, otherwise boost::none.
CORE_EXPORT boost::optional< SensorType > sensorFromString(const QString& type);
//! @brief Get all the known sensor types.
//! @return Vector containing all sensor types.
CORE_EXPORT std::vector< SensorType > allSensors();

}

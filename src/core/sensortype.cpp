//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#include "sensortype.h"
#include "stringenum.h"
#include <memory>
#include <sstream>
#include <boost/thread/once.hpp>

using namespace minesense;

namespace
{
	boost::once_flag s_flag;

	std::unique_ptr< StringEnum< SensorType > > s_map;

	void createMap()
	{
		EnumEntry< SensorType > entries[] =
		{
			{ SensorType::EMS, QStringLiteral("EMS") },
			{ SensorType::XRF, QStringLiteral("XRF") },
			{ SensorType::LIBS, QStringLiteral("LIBS") },
		};
		s_map = std::make_unique< StringEnum< SensorType > >(entries);
	}

	const StringEnum< SensorType >& getMap()
	{
		boost::call_once(&createMap, s_flag);
		return *s_map;
	}
}

QString minesense::sensorToString(SensorType type)
{
	auto string = getMap().mapEnum(type);
	if (!string)
	{
		std::ostringstream ss;
		ss << "Invalid sensor type: " << static_cast<int>(type);
		throw std::runtime_error(ss.str());
	}
	return std::move(*string);
}

boost::optional< SensorType > minesense::sensorFromString(const QString& type)
{
	return getMap().mapString(type);
}

std::vector< SensorType > minesense::allSensors()
{
	return getMap().enumValues();
}

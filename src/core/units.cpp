//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#include "units.h"
#include "stringenum.h"
#include <memory>
#include <sstream>
#include <boost/thread/once.hpp>

using namespace minesense;

namespace
{
	boost::once_flag s_flag;

	std::unique_ptr< StringEnum< Units > > s_map;

	void createMap()
	{
		EnumEntry< Units > entries[] =
		{
			{ Units::degreesCelsius, QStringLiteral("°C") },
			{ Units::millimeters, QStringLiteral("mm") },
			{ Units::seconds, QStringLiteral("s") },
			{ Units::milliseconds, QStringLiteral("ms") },
		};
		s_map = std::make_unique< StringEnum< Units > >(entries);
	}

	const StringEnum< Units >& getMap()
	{
		boost::call_once(&createMap, s_flag);
		return *s_map;
	}
}

QString minesense::unitsToString(Units unit)
{
	auto string = getMap().mapEnum(unit);
	if (!string)
	{
		std::ostringstream ss;
		ss << "Invalid unit type: " << static_cast<int>(unit);
		throw std::runtime_error(ss.str());
	}
	return std::move(*string);
}

boost::optional< Units > minesense::unitsFromString(const QString& unit)
{
	return getMap().mapString(unit);
}

std::vector< Units > minesense::allUnits()
{
	return getMap().enumValues();
}

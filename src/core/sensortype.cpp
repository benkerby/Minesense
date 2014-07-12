#include "sensortype.h"
#include "stringenum.h"
#include <memory>
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

boost::optional< QString > minesense::sensorToString(SensorType type)
{
	return getMap().mapEnum(type);
}

boost::optional< SensorType > minesense::sensorFromString(const QString& type)
{
	return getMap().mapString(type);
}

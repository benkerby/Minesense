//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#include "datatype.h"
#include "stringenum.h"
#include <memory>
#include <sstream>
#include <boost/thread/once.hpp>

using namespace minesense;

namespace
{
	boost::once_flag s_flag;

	std::unique_ptr< StringEnum< DataType > > s_map;

	void createMap()
	{
		EnumEntry< DataType > entries[] =
		{
			{ DataType::int16, QStringLiteral("int16") },
			{ DataType::int32, QStringLiteral("int32") },
			{ DataType::float32, QStringLiteral("float32") },
			{ DataType::float64, QStringLiteral("float64") },
		};
		s_map = std::make_unique< StringEnum< DataType > >(entries);
	}

	const StringEnum< DataType >& getMap()
	{
		boost::call_once(&createMap, s_flag);
		return *s_map;
	}

	template< typename T >
	struct SizeOf
	{
		static std::size_t perform(DataType)
		{
			return sizeof(T);
		}
	};
}

std::runtime_error minesense::constructError(DataType type)
{
	std::ostringstream ss;
	ss << "Invalid data type: " << static_cast<int>(type);
	return std::runtime_error(ss.str());
}

QString minesense::dataTypeToString(DataType type)
{
	auto string = getMap().mapEnum(type);
	if (!string)
	{
		throw constructError(type);
	}
	return std::move(*string);
}

boost::optional< DataType > minesense::dataTypeFromString(const QString& type)
{
	return getMap().mapString(type);
}

std::vector< DataType > minesense::allDataTypes()
{
	return getMap().enumValues();
}

std::size_t minesense::dataSizeBytes(DataType type)
{
	return perform< std::size_t, SizeOf >(type, type);
}

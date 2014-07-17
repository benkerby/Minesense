//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#include "random.h"

using namespace minesense;

namespace
{
	template< typename T >
	T randomSelection(const std::vector< T >& values, std::mt19937& engine)
	{
		std::uniform_int_distribution< std::size_t > dist(0, values.size() - 1);
		return values.at(dist(engine));
	}
}

std::mt19937 random::engine()
{
	std::random_device dev;
	return std::mt19937(dev());
}

Field random::field(std::mt19937& engine)
{
	Field rand;
	std::uniform_int_distribution< int > dist(-1000, 1000);
	rand.tag = QString("tag%1").arg(dist(engine));
	rand.type = randomSelection(allDataTypes(), engine);
	rand.unit = randomSelection(allUnits(), engine);
	return rand;
}

MetaData random::metaData(std::mt19937& engine)
{
	MetaData rand;
	rand.sensorType = randomSelection(allSensors(), engine);
	std::uniform_int_distribution< int > versionDist(0, 3);
	rand.version = versionDist(engine);
	std::uniform_int_distribution< std::size_t > fieldDist(0, 6);
	std::size_t numFields = fieldDist(engine);
	for (std::size_t i = 0; i < numFields; ++i)
	{
		rand.fields.push_back(random::field(engine));
	}
	return rand;
}

#pragma once

#include "sensortype.h"
#include "units.h"
#include "datatype.h"
#include "core_export.h"

namespace minesense
{

namespace serialize
{
class Node;
}

//! @brief Meta-data regarding a single field of data
struct CORE_EXPORT Field
{
	Field() { }
	Field(QString tag, Units unit, DataType type) : tag(std::move(tag)),
		unit(unit),
		type(type)
	{
	}
	QString tag; //!< Field name
	Units unit; //!< Field physical unit
	DataType type; //!< Type of data saved

	//! @brief Serializes to/from the given node
	void serialize(serialize::Node node);
};

//! @brief Meta-data regarding the Common Data Format (CDF)
struct CORE_EXPORT MetaData
{
	MetaData() : version(-1)
	{
	}
	MetaData(int version,
		SensorType sensorType,
		std::vector< Field > fields) : version(version),
			sensorType(sensorType),
			fields(std::move(fields))
	{
	}
	int version; //! Header version
	SensorType sensorType; //!< Sensor type
	std::vector< Field > fields; //!< Data fields contained

	//!@brief Serializes to/from the given node
	void serialize(serialize::Node node);

	//! @brief Queries the size of all the fields (given their data types)
	std::size_t fieldSize() const;
};

}

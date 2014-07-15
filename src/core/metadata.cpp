//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#include "metadata.h"
#include "serialize.h"
#include <typeinfo>

using namespace minesense;

namespace
{
	template< typename T >
	struct ToFromString
	{
		using ToString = QString(*)(T);
		using FromString = boost::optional< T >(*)(const QString&);
		ToFromString(ToString toString, FromString fromString) : toString(toString),
			fromString(fromString)
		{
		}
		QString operator()(T type) const
		{
			return toString(type);
		}
		T operator()(const QString& type) const
		{
			auto val = fromString(type);
			if (!val)
			{
				throw std::runtime_error(std::string("Unrecognized ") + typeid(T).name() + " '" + type.toLocal8Bit().constData() + "'");
			}
			return *val;
		}
	private:
		ToString toString;
		FromString fromString;
	};

	template< typename T >
	ToFromString< T > makeToFromString(QString(*toString)(T), boost::optional< T >(*fromString)(const QString&))
	{
		return ToFromString< T >(toString, fromString);
	}
}

void Field::serialize(serialize::Node node)
{
	node.childValue(QStringLiteral("tag"), tag);
	node.childValue(QStringLiteral("unit"), unit,
		makeToFromString(&unitsToString, &unitsFromString));
	node.childValue(QStringLiteral("dataType"), type,
		makeToFromString(&dataTypeToString, &dataTypeFromString));
}

void MetaData::serialize(serialize::Node node)
{
	node.childValue(QStringLiteral("version"), version);
	node.childValue(QStringLiteral("sensorType"), sensorType,
		makeToFromString(&sensorToString, &sensorFromString));
	node.serialize(QStringLiteral("field"), fields);
}

std::size_t MetaData::fieldSize() const
{
	std::size_t result = 0;
	for (auto& field : fields)
	{
		result += dataSizeBytes(field.type);
	}
	return result;
}

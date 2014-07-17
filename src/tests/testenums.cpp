//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#include <gtest/gtest.h>
#include "../core/datatype.h"
#include "../core/sensortype.h"
#include "../core/units.h"

using namespace minesense;
namespace
{
	template < typename EnumType >
	void testSerializing(std::vector< EnumType >(*getAll)(), QString(*toString)(EnumType), boost::optional< EnumType >(*fromString)(const QString&))
	{
		auto allEnums = getAll();
		for (auto val : allEnums)
		{
			auto stringVal = toString(val);
			EXPECT_FALSE(stringVal.isEmpty()) << "Enum (" << typeid(EnumType).name() << ") value "
				<< static_cast<int>(val) << " returned empty string.";
			auto back = fromString(stringVal);
			ASSERT_FALSE(!back) << "Enum (" << typeid(EnumType).name() << ") value "
				<< static_cast<int>(val) << ": '" << stringVal.toLocal8Bit().constData()
				<< "' could not be converted back.";
			EXPECT_EQ(val, *back) << "Enum (" << typeid(EnumType).name() << ") value "
				<< static_cast<int>(val) << ": '" << stringVal.toLocal8Bit().constData()
				<< "' converted back to incorrect value: " << static_cast<int>(*back);
		}
	}

	TEST(UnitsEnum, Serialization)
	{
		testSerializing(&allUnits, &unitsToString, &unitsFromString);
	}

	TEST(DataTypeEnum, Serialization)
	{
		testSerializing(&allDataTypes, &dataTypeToString, &dataTypeFromString);
	}

	TEST(SensorTypeEnum, Serialization)
	{
		testSerializing(&allSensors, &sensorToString, &sensorFromString);
	}
}

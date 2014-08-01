//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#include <gtest/gtest.h>
#include "../core/random.h"
#include "../core/serialize.h"

using namespace minesense;
namespace
{
	void compare(const Field& input, const Field& output)
	{
		EXPECT_EQ(input.tag, output.tag);
		EXPECT_EQ(input.type, output.type);
		EXPECT_EQ(input.unit, output.unit);
	}

	void compare(const MetaData& input, const MetaData& output)
	{
		EXPECT_EQ(input.version, output.version);
		EXPECT_EQ(input.sensorType, output.sensorType);
		ASSERT_EQ(input.fields.size(), output.fields.size());
		for (std::size_t i = 0; i < input.fields.size(); ++i)
		{
			compare(input.fields.at(i), output.fields.at(i));
		}
	}

	template < typename DataType >
	void testSerializing(DataType (*randomizer)(std::mt19937&))
	{
		auto eng = random::engine();
		auto input = randomizer(eng);
		QDomDocument xml;
		QDomElement node = xml.importNode(xml.createElement("root"), true).toElement();
		input.serialize(serialize::saving(node));
		DataType output;
		output.serialize(serialize::loading(node));
		compare(input, output);
	}

	TEST(FieldStruct, Serialization)
	{
		testSerializing(&random::field);
	}

	TEST(MetaDataStruct, Serialization)
	{
		testSerializing(&random::metaData);
	}

	struct Printer
	{
		template< typename T >
		void operator()(const Field& field, T value) const
		{
			std::cout << "Random field: '" << field.tag.toLocal8Bit().constData() << "' = "
				<< value << unitsToString(field.unit).toLocal8Bit().constData() << std::endl;
		}
	};

	TEST(Binary, Print)
	{
		auto eng = random::engine();
		auto data = random::metaData(eng);
		Printer printer;
		for (auto& field : data.fields)
		{
			random::binary(field, eng, printer);
		}
	}
}

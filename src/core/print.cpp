//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#include "print.h"
#include "metadata.h"

#include <QTextStream>

void minesense::print(QTextStream& stream, const Field& field)
{
	stream << '\'' << field.tag << "' with " << dataTypeToString(field.type)
		<< " " << unitsToString(field.unit);
}

void minesense::printNoFields(QTextStream& stream, const MetaData& metadata)
{
	stream << "Header version: " << metadata.version << ", sensor type: " << sensorToString(metadata.sensorType);
}

void minesense::printWithFields(QTextStream& stream, const MetaData& metadata)
{
	printNoFields(stream, metadata);
	stream << endl << "Fields: " << endl;
	for (std::size_t i = 0; i < metadata.fields.size(); ++i)
	{
		stream << '\t';
		print(stream, metadata.fields[i]);
		stream << endl;
	}
}

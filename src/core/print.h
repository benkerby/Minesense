//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#pragma once

#include "core_export.h"
#include <random>

class QTextStream;

namespace minesense
{
	struct Field;

	struct MetaData;

	//! @brief Prints the field to the given stream.
	CORE_EXPORT void print(QTextStream& stream, const Field& field);

	//! @brief Prints the metadata without fields to the given stream.
	CORE_EXPORT void printNoFields(QTextStream& stream, const MetaData& metadata);

	//! @brief Prints the metadata without fields to the given stream.
	CORE_EXPORT void printWithFields(QTextStream& stream, const MetaData& metadata);
}

//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#pragma once

#include <QString>
#include <boost/optional.hpp>
#include <vector>
#include <cstdint>
#include "core_export.h"

namespace minesense
{
	//! @brief Data type.
	enum class DataType
	{
		int16, //! 16-bit signed integer
		int32, //! 32-bit signed integer
		float32, //! 32-bit signed floating point
		float64 //! 64-bit signed floating point
	};

	//! @brief Create a std::runtime_error for an invalid enum value.
	//! @return A std::runtime_error for an invalid enum value.
	CORE_EXPORT std::runtime_error constructError(DataType type /*!< an invalid enum value */);

	//! @brief Convert the given data type to string.
	//! @return String representation of the data type.
	//! @throws std::runtime_error if the enum value is not valid.
	CORE_EXPORT QString dataTypeToString(DataType type);
	//! @brief Convert the given string to a data type.
	//! @return Unit if the string is recognized, otherwise boost::none.
	CORE_EXPORT boost::optional< DataType > dataTypeFromString(const QString& type);
	//! @brief Get all the known data types.
	//! @return Vector containing all data types.
	CORE_EXPORT std::vector< DataType > allDataTypes();

	//! @brief Get the size of the given data type.
	//! @return Size (in bytes) of the data type.
	//! @throws std::runtime_error if the enum value is not valid.
	CORE_EXPORT std::size_t dataSizeBytes(DataType type);

	//! @brief Performs an action for the given type.
	//! @details The first parameter specifies the return type (can be 'void').
	//!          The second parameter specifies a templated class which will be
	//!          instantiated with the correct type and should have a static method
	//!          called 'perform' which will be called with the forwarded arguments.
	//! @return Result of the action for the given type.
	//! @throws std::runtime_error if the enum value is not valid.
	template < typename Return, template<class> class Performer, typename... Arguments >
	Return perform(DataType dataType, /*!< Type to instantiate. */
		Arguments&&... args /*!< Arguments to forward. */)
	{
		switch (dataType)
		{
		case DataType::int16:
			return Performer< std::int16_t >::perform(std::forward< Arguments >(args)...);
		case DataType::int32:
			return Performer< std::int32_t >::perform(std::forward< Arguments >(args)...);
		case DataType::float32:
			static_assert(sizeof(float) * CHAR_BIT == 32, "Wrong floating point size");
			return Performer< float >::perform(std::forward< Arguments >(args)...);
		case DataType::float64:
			static_assert(sizeof(double)* CHAR_BIT == 64, "Wrong floating point size");
			return Performer< double >::perform(std::forward< Arguments >(args)...);
		default:
			throw constructError(dataType);
		}
	}
}

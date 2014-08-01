//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#pragma once

#include "metadata.h"
#include "core_export.h"
#include <random>

namespace minesense
{
	namespace random
	{
		//! @brief Create a seeded engine for producing random data.
		//! @return Engine for producing random data.
		CORE_EXPORT std::mt19937 engine();

		//! @brief Create random meta-data regarding a single field of data
		CORE_EXPORT Field field(std::mt19937& engine /*!< Engine for producing random data. */);

		//! @brief Create random meta-data regarding the Common Data Format (CDF)
		CORE_EXPORT MetaData metaData(std::mt19937& engine /*!< Engine for producing random data. */);

		namespace detail
		{
			template< typename DataType, typename std::enable_if<std::is_floating_point<DataType>::value>::type* = nullptr >
			DataType randomBinary(std::mt19937& engine)
			{
				std::uniform_real_distribution< DataType > dist(static_cast< DataType >(-100), static_cast< DataType >(100));
				return dist(engine);
			}

			template< typename DataType, typename std::enable_if<!std::is_floating_point<DataType>::value>::type* = nullptr >
			DataType randomBinary(std::mt19937& engine)
			{
				std::uniform_int_distribution< DataType > dist(static_cast< DataType >(-100), static_cast< DataType >(100));
				return dist(engine);
			}

			template< typename DataType >
			struct RandomBinary
			{
				template< typename T >
				static void perform(const Field& field, std::mt19937& engine, T&& callback)
				{
					callback(field, randomBinary< DataType >(engine));
				}
			};

		}

		//! @brief Produces a random value of the type specified by 'field' and feeds it to the given callback.
		template< typename T >
		void binary(const Field& field, /*!< Field information (including type to be produced). */
			std::mt19937& engine, /*!< Engine for producing random data. */
			T&& callback /*!< Functor to be called with the field information (1st parameter) and the random data (2nd parameter). */)
		{
			perform< void, detail::RandomBinary >(field.type, field, engine, std::forward< T >(callback));
		}
	}
}

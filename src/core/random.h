//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#pragma once

#include "metadata.h"
#include "core_export.h"
#include <random>

namespace minesense
{
	namespace random
	{
		CORE_EXPORT std::mt19937 engine();

		//! @brief Create random meta-data regarding a single field of data
		CORE_EXPORT Field field(std::mt19937& engine);

		//! @brief Create random meta-data regarding the Common Data Format (CDF)
		CORE_EXPORT MetaData metaData(std::mt19937& engine);
	}
}

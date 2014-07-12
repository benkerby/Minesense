#include <QString>
#include <boost/optional.hpp>
#include "core_export.h"

namespace minesense
{
enum class SensorType
{
	XRF,
	EMS,
	LIBS
};

CORE_EXPORT boost::optional< QString > sensorToString(SensorType type);
CORE_EXPORT boost::optional< SensorType > sensorFromString(const QString& type);

}

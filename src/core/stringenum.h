#include <QString>
#include <map>
#include <boost/optional.hpp>

namespace minesense
{

//! @brief Helper struct for initializing the StringEnum class.
template < typename ENUM >
struct EnumEntry
{
	ENUM enumVal;
	QString stringVal;
};

//! @brief Class to maintain mapping from enumerations to/from strings.
//! @tparam ENUM An enumeration type.
template < typename ENUM >
class StringEnum
{
public:
	//! @brief Constructor
	template< std::size_t N >
	explicit StringEnum(const EnumEntry< ENUM >(& entries)[N] /*!< */)
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			stringToEnum[entries[i].stringVal] = entries[i].enumVal;
			enumToString[entries[i].enumVal] = entries[i].stringVal;
		}
	}
	//! @brief Map an enum value to string.
	//! @return String if the value is valid, otherwise boost::none.
	boost::optional< QString > mapEnum(ENUM enumVal /*!< Enumeration value to map. */) const
	{
		auto iter = enumToString.find(enumVal);
		if (iter != enumToString.end())
		{
			return iter->second;
		}
		return boost::none;
	}
	//! @brief Map a string to enum value.
	//! @return Enum value if the string is recognized, otherwise boost::none.
	boost::optional< ENUM > mapString(const QString& stringVal /*!< String to map. */) const
	{
		auto iter = stringToEnum.find(stringVal);
		if (iter != stringToEnum.end())
		{
			return iter->second;
		}
		return boost::none;
	}
private:
	std::map< QString, ENUM > stringToEnum;
	std::map< ENUM, QString > enumToString;
};

}

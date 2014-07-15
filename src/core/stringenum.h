#pragma once

#include <QString>
#include <map>
#include <boost/optional.hpp>

namespace minesense
{

//! @brief Helper struct for initializing the StringEnum class.
template < typename EnumType >
struct EnumEntry
{
	EnumType enumVal;
	QString stringVal;
};

//! @brief Class to maintain mapping from enumerations to/from strings.
//! @tparam EnumType An enumeration type.
template < typename EnumType >
class StringEnum
{
public:
	//! @brief Constructor
	template< std::size_t N >
	explicit StringEnum(const EnumEntry< EnumType >(& entries)[N] /*!< */)
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			stringToEnum[entries[i].stringVal] = entries[i].enumVal;
			enumToString[entries[i].enumVal] = entries[i].stringVal;
		}
	}
	//! @brief Map an enum value to string.
	//! @return String if the value is valid, otherwise boost::none.
	boost::optional< QString > mapEnum(EnumType enumVal /*!< Enumeration value to map. */) const
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
	boost::optional< EnumType > mapString(const QString& stringVal /*!< String to map. */) const
	{
		auto iter = stringToEnum.find(stringVal);
		if (iter != stringToEnum.end())
		{
			return iter->second;
		}
		return boost::none;
	}
	//! @brief Get all enum value.
	//! @return std::vector of all mapped enum values.
	std::vector< EnumType > enumValues() const
	{
		std::vector< EnumType > values;
		for (auto& pair : enumToString)
		{
			values.push_back(pair.first);
		}
		return values;
	}
private:
	std::map< QString, EnumType > stringToEnum;
	std::map< EnumType, QString > enumToString;
};

}

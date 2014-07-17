//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#pragma once

//! @file serialize.h
//! @brief Serialization classes and functions
//! @details Saving and loading is accomplished with the same functions
//!          (it is unknown to the user of the serialization node whether
//!           the node is currently in saving or loading mode).

#include <QDomElement>
#include <QString>
#include <vector>
#include "core_export.h"

namespace minesense
{

//! @brief Namespace for serialization classes and functions
namespace serialize
{
	//! @brief Class to encapsulate a serialization node
	//! @details Saving and loading is accomplished with the same functions
	//!          (it is unknown to the user of the serialization node whether
	//!           the node is currently in saving or loading mode).
	class CORE_EXPORT Node
	{
	public:
		//! @brief the saving/loading mode
		enum class Mode
		{
			saving, //!< Writing to DOM node
			loading //!< Reading from DOM node, can throw std::runtime_error
		};

		//! @brief Constructor
		Node(const QDomElement& node, /*!< The DOM node */
			Mode mode /*!< The serialization mode */) : node(node), mode(mode)
		{
		}

		template < typename T >
		void serialize(const QString& tagName, /*!< the tag name for each element. */
			std::vector< T >& value /*!< Vector to serialize. */)
		{
			if (saving())
			{
				for (auto& val : value)
				{
					val.serialize(Node(childElement(tagName), mode));
				}
			}
			else
			{
				value.clear();
				auto child = childElement(tagName, false);
				while (!child.isNull())
				{
					T val;
					val.serialize(Node(child, mode));
					value.push_back(std::move(val));
					child = child.nextSiblingElement(tagName);
				}
			}
		}

		template < typename T, typename ToString, typename FromString >
		void childValue(const QString& tagName, T& value, ToString&& toString, FromString&& fromString)
		{
			if (saving())
			{
				QString valueString = toString(value);
				childValue(tagName, valueString);
			}
			else
			{
				QString valueString;
				childValue(tagName, valueString);
				value = fromString(valueString);
			}
		}
		template < typename T, typename TOFROMSTRING >
		void childValue(const QString& tagName, T& value, TOFROMSTRING&& toFromString)
		{
			if (saving())
			{
				QString valueString = toFromString(value);
				childValue(tagName, valueString);
			}
			else
			{
				QString valueString;
				childValue(tagName, valueString);
				value = toFromString(valueString);
			}
		}
		void childValue(const QString& tagName, QString& value);
		void childValue(const QString& tagName, int& value);
		void childValue(const QString& tagName, double& value);
		void text(QString& value);
		Node child(const QString& tagName);

	private:
		bool saving() const { return mode == Mode::saving; }
		QDomElement childElement(const QString& tagName, bool throwOnError = true);
		Mode mode;
		QDomElement node;
	};

	CORE_EXPORT Node saving(const QDomElement& node);
	CORE_EXPORT Node loading(const QDomElement& node);
}
}

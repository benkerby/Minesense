#include "serialize.h"
#include <stdexcept>

using namespace minesense;

namespace
{
	bool saving(serialize::Node::Mode mode)
	{
		return mode == serialize::Node::Mode::saving;
	}

	void serializeOne(QDomElement& node, QString& value, serialize::Node::Mode mode)
	{
		if (saving(mode))
		{
			node.setNodeValue(value);
		}
		else
		{
			value = node.text();
		}
	}

	void serializeOne(QDomElement& node, int& value, serialize::Node::Mode mode)
	{
		if (saving(mode))
		{
			node.setNodeValue(QString::number(value));
		}
		else
		{
			bool ok = false;
			auto text = node.text();
			value = text.toInt(&ok);
			if (!ok)
			{
				throw std::runtime_error("Unable to convert '" + text.toLocal8Bit() + "' to integer");
			}
		}
	}

	void serializeOne(QDomElement& node, double& value, serialize::Node::Mode mode)
	{
		if (saving(mode))
		{
			node.setNodeValue(QString::number(value));
		}
		else
		{
			bool ok = false;
			auto text = node.text();
			value = text.toDouble(&ok);
			if (!ok)
			{
				throw std::runtime_error("Unable to convert '" + text.toLocal8Bit() + "' to double");
			}
		}
	}
}

void serialize::Node::childValue(const QString& tagName, QString& value)
{
	auto child = childElement(tagName);
	serializeOne(child, value, mode);
}

void serialize::Node::childValue(const QString& tagName, int& value)
{
	auto child = childElement(tagName);
	serializeOne(child, value, mode);
}

void serialize::Node::childValue(const QString& tagName, double& value)
{
	auto child = childElement(tagName);
	serializeOne(child, value, mode);
}

void serialize::Node::text(QString& value)
{
	serializeOne(node, value, mode);
}

serialize::Node serialize::Node::child(const QString& tagName)
{
	return Node(childElement(tagName), mode);
}

QDomElement serialize::Node::childElement(const QString& tagName)
{
	if (saving())
	{
		return node.appendChild(node.ownerDocument().createElement(tagName)).toElement();
	}
	else
	{
		auto child = node.firstChildElement(tagName);
		if (child.isNull())
		{
			throw std::runtime_error("Unable to find requested child element '" + tagName.toLocal8Bit() + "'");
		}
		return child;
	}
}

serialize::Node serialize::saving(const QDomElement& node)
{
	return Node(node, Node::Mode::saving);
}

serialize::Node serialize::loading(const QDomElement& node)
{
	return Node(node, Node::Mode::loading);
}

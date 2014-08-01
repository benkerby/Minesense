//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#include "socketwriter.h"
#include "../core/serialize.h"
#include "../core/metadata.h"
#include "../core/protocol.h"
#include <QTcpSocket>
#include <QDomDocument>

using namespace minesense;

SocketWriter::SocketWriter(QObject* parent) : QObject(parent),
	socket(new QTcpSocket(this)),
	dataStream(new QDataStream(socket)),
	connected(false)
{
	connect(socket, &QTcpSocket::stateChanged, this, &SocketWriter::onStateChanged, Qt::QueuedConnection);
	connect(socket, static_cast< void(QAbstractSocket::*)(QAbstractSocket::SocketError) >(&QTcpSocket::error),
		this, &SocketWriter::onError, Qt::QueuedConnection);
}

SocketWriter::~SocketWriter()
{
	socket->abort();
}

void SocketWriter::open(const QString & hostName, quint16 port)
{
	connected = false;
	socket->connectToHost(hostName, port, QIODevice::WriteOnly);
	QTextStream(stdout) << "Connecting to " << hostName << ':' << port << "..." << endl;
}

void SocketWriter::writeStartHeader() const
{
	if (!connected)
	{
		return;
	}
	*dataStream << protocol::start;
	*dataStream << static_cast< std::uint8_t >(protocol::PacketType::header);
}

void SocketWriter::writeStartBinary() const
{
	if (!connected)
	{
		return;
	}
	*dataStream << protocol::start;
	*dataStream << static_cast< std::uint8_t >(protocol::PacketType::data);
}

void SocketWriter::writeEnd() const
{
	if (!connected)
	{
		return;
	}
	*dataStream << protocol::end;
}

void SocketWriter::writeMetaData(MetaData& metadata) const
{
	if (!connected)
	{
		return;
	}
	QDomDocument xml;
	QDomElement node = xml.importNode(xml.createElement("root"), true).toElement();
	metadata.serialize(serialize::saving(node));
	auto bytes = xml.toByteArray();
	dataStream->writeBytes(bytes.constData(), bytes.length());
}

void SocketWriter::onStateChanged(QAbstractSocket::SocketState socketState)
{
	qDebug() << "Connection status: " << socketState;
	connected = (socketState == QAbstractSocket::ConnectedState);
}

void SocketWriter::onError(QAbstractSocket::SocketError socketError)
{
	qDebug() << "Error occurred: " << socketError;
}

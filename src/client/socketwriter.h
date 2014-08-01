//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#pragma once

//! @file socketwriter.h
//! @brief Class to write metadata and field data to the socket.

#include <QObject>
#include <memory>
#include <QDataStream>
#include <QAbstractSocket>
#include <cstdint>

class QTcpSocket;
class QDataStream;

namespace minesense
{

struct MetaData;

//! @brief Class to read lines from the console.
class SocketWriter : public QObject
{
	Q_OBJECT;

public:
	SocketWriter(QObject* parent = nullptr);
	~SocketWriter();

	void open(const QString & hostName, quint16 port);

	void writeStartHeader() const;
	void writeStartBinary() const;
	void writeEnd() const;

	template< typename T >
	void writeBinary(const T& data) const
	{
		dataStream << data;
	}

	void writeMetaData(MetaData& metadata) const;

private slots:
	void onStateChanged(QAbstractSocket::SocketState socketState);
	void onError(QAbstractSocket::SocketError socketError);

private:
	QTcpSocket* socket;
	std::unique_ptr< QDataStream > dataStream;
	bool connected;
};

}

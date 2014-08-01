//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#pragma once

//! @file consolereader.h
//! @brief Class to read lines from the console.

#include <QObject>
#include <QTextStream>
#include "core_export.h"

namespace minesense
{

//! @brief Class to read lines from the console.
class CORE_EXPORT ConsoleReader : public QObject
{
	Q_OBJECT;

public:
	ConsoleReader(QObject* parent = nullptr);

public slots:
	void start();

signals:
	void lineRead(const QString& line);
	void quitting();

private:
	QTextStream stream;
};

}

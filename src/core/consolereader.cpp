//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#include "consolereader.h"

namespace
{
	bool isQuitCommand(const QString& line)
	{
		return line.compare("q", Qt::CaseInsensitive) == 0 ||
			line.compare("x", Qt::CaseInsensitive) == 0 ||
			line.compare("quit", Qt::CaseInsensitive) == 0 ||
			line.compare("exit", Qt::CaseInsensitive) == 0;
	}
}

using namespace minesense;

ConsoleReader::ConsoleReader(QObject* parent) : QObject(parent),
	stream(stdin)
{
}

void ConsoleReader::start()
{
	Q_FOREVER
	{
		QString line = stream.readLine();
		if (isQuitCommand(line))
		{
			emit quitting();
			break;
		}
		else
		{
			emit lineRead(line);
		}
	}
}

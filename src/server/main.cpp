//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#include <QCoreApplication>
#include "../core/consolereader.h"
#include <QThread>
#include <QDebug>
#include <QTimer>

namespace
{
	bool newline(const QString& line)
	{
		qDebug() << line << endl;
		return true;
	}
}

int main(int argc, char* argv[])
{
	QCoreApplication app(argc, argv);

	auto thread = new QThread(&app);

	thread->start();

	auto reader = new minesense::ConsoleReader;

	reader->moveToThread(thread);

	QObject::connect(reader, &minesense::ConsoleReader::lineRead, &newline);

	QMetaObject::invokeMethod(reader, "start", Qt::QueuedConnection);

	QObject::connect(reader, &minesense::ConsoleReader::quitting, thread, &QThread::quit);

	QObject::connect(reader, &minesense::ConsoleReader::quitting, &app, &QCoreApplication::quit);

	QTextStream(stdout) << "Type 'q' or 'quit' or 'x' or 'exit' to quit..." << endl;

	return app.exec();
}

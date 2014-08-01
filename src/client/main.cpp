//! @copyright Copyright 2014 Benjamin Kerby. All rights reserved.

#include <QCoreApplication>
#include "../core/consolereader.h"
#include "../core/random.h"
#include "../core/print.h"
#include "socketwriter.h"
#include <QThread>
#include <QDebug>
#include <QTimer>

namespace
{
	void newline(const QString& line, minesense::SocketWriter* writer)
	{
		QTextStream outStream(stdout);
		std::mt19937::result_type seed = 0;
		outStream << "Using '" << line << "' as a random seed..." << endl;
		for (int i = 0; i < line.length(); ++i)
		{
			seed += line.at(i).unicode();
		}
		std::mt19937 engine(seed);
		auto metadata = minesense::random::metaData(engine);
		outStream << "Generated random metadata: ";
		minesense::printWithFields(outStream, metadata);
		writer->writeStartHeader();
		writer->writeMetaData(metadata);
		writer->writeEnd();
	}
}

int main(int argc, char* argv[])
{
	QCoreApplication app(argc, argv);

	auto thread = new QThread(&app);

	thread->start();

	auto reader = new minesense::ConsoleReader;

	reader->moveToThread(thread);

	minesense::SocketWriter writer;

	writer.open("localhost", 314);

	QObject::connect(reader, &minesense::ConsoleReader::lineRead, std::bind(&newline, std::placeholders::_1, &writer));

	QMetaObject::invokeMethod(reader, "start", Qt::QueuedConnection);

	QObject::connect(reader, &minesense::ConsoleReader::quitting, thread, &QThread::quit);

	QObject::connect(reader, &minesense::ConsoleReader::quitting, &app, &QCoreApplication::quit);

	QTextStream stdStream(stdout);
	stdStream << "Type 'q' or 'quit' or 'x' or 'exit' to quit..." << endl
		<< "Type anything else to seed a random output." << endl;

	return app.exec();
}

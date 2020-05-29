#include "Logger.h"

Logger::Logger(int verbosity)
{
	this->verbosity = verbosity;
}

void Logger::setVerbosity(int verbosity)
{
	this->verbosity = verbosity;
}

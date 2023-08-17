#include "Logger.h"
#include <iostream>
#include "FileIO.h"

namespace kiko
{
	bool Logger::Log(LogLevel logLevel, const std::string filename, int line)
	{
		if (logLevel < m_logLevel) return false;
		switch (m_logLevel)
		{
		case kiko::Info:
			*this << "INFO: ";
			break;
		case kiko::Warning:
			*this << "WARNING: ";
			break;
		case kiko::Error:
			*this << "ERROR: ";
			break;
		case kiko::Assert:
			*this << "ASSERT: ";
			break;
		default:
			break;
		}

		*this << getFileName(filename) << "(" << line << ")\n";

		return true;
	}
}
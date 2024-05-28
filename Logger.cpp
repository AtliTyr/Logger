#include "Logger.h"

Logger::Logger()
{
	logs.open("log.txt", std::ios_base::in | std::ios_base::out | std::ios_base::trunc);
}

Logger::~Logger()
{
	logs.close();
}

void Logger::inputToLogs(std::string text)
{
	m.lock();

	logs << "\n" << text;

	m.unlock();
}

std::string Logger::getLastLogString()
{
    m.lock_shared();

    logs.seekg(-1, std::ios_base::end);                // go to one spot before the EOF

    bool keepLooping = true;
    while (keepLooping) {
        char ch;
        logs.get(ch);                            // Get current byte's data

        if ((int)logs.tellg() <= 1) {             // If the data was at or before the 0th byte
            logs.seekg(0);                       // The first line is the last line
            keepLooping = false;                // So stop there
        }
        else if (ch == '\n') {                   // If the data was a newline
            keepLooping = false;                // Stop at the current position.
        }
        else {                                  // If the data was neither a newline nor at the 0 byte
            logs.seekg(-2, std::ios_base::cur);        // Move to the front of that data, then to the front of the data before it
        }
    }

    std::string lastLine;
    std::getline(logs, lastLine);                      // Read the current line

    m.unlock_shared();

	return std::string(lastLine);
}






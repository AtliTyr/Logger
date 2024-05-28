#pragma once
#include <shared_mutex>
#include <fstream>
#include <string>
#include <iostream>

class Logger
{
private:
	std::fstream logs;
	std::shared_mutex m;
public:
	Logger();
	~Logger();

	void inputToLogs(std::string text);
	std::string getLastLogString();
};


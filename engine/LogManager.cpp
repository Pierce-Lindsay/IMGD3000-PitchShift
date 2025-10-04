#include "LogManager.h"
#include <iostream>
#include <stdio.h>
#include <exception>
#include <ctime>
#include <cstdio>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdarg>

//for cross-platform
#ifdef _WIN32
#include <direct.h> // For Windows _mkdir
#define MAKE_DIRECTORY(path) _mkdir(path)
#else
#include <sys/stat.h>
#include <sys/types.h>
#define MAKE_DIRECTORY(path) mkdir(path, 0777) // 0777 for full permissions
#endif


using namespace df;

std::exception FILE_POINTER_NULL = std::exception("Log manager error, The file pointer as null.");
std::exception FILE_RENAME_ERROR = std::exception("Log manager error, failed to rename file.");
LogManager::LogManager()
{
	setType("LogManager");
}

LogManager::~LogManager()
{
}

LogManager& LogManager::GetInstance()
{
	static LogManager lm;
	return lm;
}

int LogManager::startUp()
{
	//create directory if doesn't exist
	createDirectory();

	std::string full_path = (file_path + file_name);
	if (fopen_s(&p_file, full_path.c_str(), "w") != 0)
	{ //failed to open file
		return -1;
	}

	writeLog("LogManager::startUp: LogManager successfully started!");
	return Manager::startUp();
}

void LogManager::shutDown()
{
	writeLog("LogManager::shutDown: LogManager successfully shutdown!");
	fclose(p_file);
	p_file = NULL;
	Manager::shutDown();
}

void LogManager::setFlush(bool do_flush)
{
	m_do_flush = do_flush;
}

int LogManager::writeLog(const char* format, ...)
{
	if (p_file == NULL)
	{
		return -1;
	}
	//needed for multiple format args
	std::va_list arguments;
	va_start(arguments, format);

	int num = vfprintf(p_file, format, arguments); 
	va_end(arguments);
	fprintf(p_file, "\n"); //ensure newline

	//m_do_flush = false;

	if (m_do_flush)
		fflush(p_file);

	return num;
}


void LogManager::setOutputPath(std::string path)
{
	std::string old_name = getFullFilePath();
	file_path = path;
	resetFilePath(old_name.c_str());
}

void LogManager::setOutputFileName(std::string name)
{
	std::string old_name = getFullFilePath();
	file_name = name;
	resetFilePath(old_name.c_str());
}

std::string LogManager::getOutputPath() const
{
	return file_path;
}

std::string LogManager::getOutputFileName() const
{
	return file_name;
}

std::string LogManager::getFullFilePath()
{
	return (file_path + file_name);
}

void LogManager::resetFilePath(const char* old_name)
{
	if (p_file != NULL) //rename/move file
	{
		createDirectory(); //make sure new dir exists
		auto new_name = getFullFilePath();
		if (rename(old_name, new_name.c_str()) != 0)
			throw FILE_RENAME_ERROR;
	}
}

void LogManager::createDirectory()
{
	MAKE_DIRECTORY(file_path.c_str());
}
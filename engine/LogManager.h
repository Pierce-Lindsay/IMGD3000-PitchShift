#pragma once
#include "Manager.h"
#include <fstream>

#define LM df::LogManager::GetInstance()

namespace df
{
	/// <summary>
	/// A class for managing logging in the game engine.
	/// </summary>
	class LogManager : public Manager
	{
	private:
		LogManager();
		LogManager(LogManager const &copy);
		void operator=(LogManager const &assign);

		bool m_do_flush = false;
		FILE* p_file = NULL;
		const std::string DEFAULT_FILE_NAME = "dragonfly_log.txt";
		const std::string DEFAULT_FILE_PATH = "logs/";
		std::string file_path = DEFAULT_FILE_PATH;
		std::string file_name = DEFAULT_FILE_NAME;

		/// <summary>
		/// Gets the full relative file path of the log files as a cstr.
		/// </summary>
		std::string getFullFilePath();
		
		/// <summary>
		/// Rename/moves log file based on the current file name/directory and the old.
		/// </summary>
		void resetFilePath(const char* old_name);

		/// <summary>
		/// Creates the required directory according to the manager's directory path
		/// </summary>
		void createDirectory();

	public:

		/// <summary>
		/// Close the file and any other dependencies.
		/// </summary>
		~LogManager();

		/// <summary>
		/// Get instance of the one and only LogManager.
		/// </summary>
		/// <returns></returns>
		static LogManager& GetInstance();

		/// <summary>
		/// Open/create log file and setup LogManager.
		/// </summary>
		/// <returns>0 if succesfful, negative else.</returns>
		int startUp() override;

		/// <summary>
		/// Cleanup dependencies.
		/// </summary>
		void shutDown() override;

		/// <summary>
		/// Set whether the log file is flushed to every time it is updated (slower if true).
		/// </summary>
		void setFlush(bool do_flush = true);

		/// <summary>
		/// Write a line to the log file from the given string. Returns number of characters written minus the added newlne.
		/// Adds newline at the end of line. 
		/// </summary>
		/// <param name="line">A printf() style formatted input that is sent to the log.</param>
		int writeLog(const char* format, ...);

		/// <summary>
		/// Sets the outpath path (directory) log file are placed in.
		/// </summary>
		void setOutputPath(std::string path);

		/// <summary>
		/// Sets the file name for the output log file.
		/// </summary>
		void setOutputFileName(std::string name);

		/// <summary>
		/// Gets the current set output path (directory) log files are placed in.
		/// </summary>
		std::string getOutputPath() const;

		/// <summary>
		/// Gets the current set output filename of log files.
		/// </summary>
		std::string getOutputFileName() const;
	};
}
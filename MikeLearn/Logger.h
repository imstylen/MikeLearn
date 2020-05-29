#pragma once
#include <iostream>

class Logger
{

public:

	Logger(int verbosity);

	void setVerbosity(int verbosity);

	template <typename T>
	void LogGeneral(T var1)
	{
		if (verbosity < 1) { return; }
		std::cout << var1 << std::endl;
	}
	template <typename T, typename... Types>
	void LogGeneral(T var1, Types... var2)
	{
		if (verbosity < 1) { return; }
		std::cout << var1 << std::endl;
		LogGeneral(var2...);
	}

	template <typename T, typename... Types>
	void LogVerbose(T var1, Types... var2)
	{
		if (verbosity < 2) { return; }
		std::cout << var1 << std::endl;
		LogVerbose(var2...);
	}
	template <typename T>
	void LogVerbose(T var1)
	{
		if (verbosity < 2) { return; }
		std::cout << var1 << std::endl;
	}

	template <typename T, typename... Types>
	void LogVeryVerbose(T var1, Types... var2)
	{
		if (verbosity < 3) { return; }
		std::cout << var1 << std::endl;
		LogVeryVerbose(var2...);
	}
	template <typename T>
	void LogVeryVerbose(T var1)
	{
		if (verbosity < 3) { return; }
		std::cout << var1 << std::endl;
	}

	template <typename T, typename... Types>
	void LogWarning(T var1, Types... var2)
	{
		std::cout << var1 << std::endl;
		LogWarning(var2...);
	}
	template <typename T>
	void LogWarning(T var1)
	{
		std::cout << var1 << std::endl;
	}

	template <typename T, typename... Types>
	void LogError(T var1, Types... var2)
	{
		std::cout << var1 << std::endl;
		LogError(var2...);
	}
	template <typename T>
	void LogError(T var1)
	{
		std::cout << var1 << std::endl;
	}

private:
	int verbosity;

};


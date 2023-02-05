#pragma once

#define LOG_PRINT(fmt, ...) pLog.Message("[Info]", fmt, ##__VA_ARGS__);
#define LOG_ERROR(fmt, ...) pLog.Message("[Fail]", fmt, ##__VA_ARGS__);

#ifndef RELEASE_VERSION
#define LOG_DEV(fmt, ...)	pLog.Message("[Dev]", fmt, ##__VA_ARGS__);
#else
#define LOG_DEV(fmt, ...)
#endif

class Log {
public:
	HRESULT Initialize();
	const char* GetTimeAsString();
	void Message(const char* type, const char* fmt, ...);
private:
	void ClearLog();
	void LogToFile(const char* message);
};

extern Log pLog;
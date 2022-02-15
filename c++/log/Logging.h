#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "LogStream.h"
#include <cstring>

namespace Log {

class TimeStamp;

class Logger {
  public:
  enum LogLevel {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
    NUM_LOG_LEVELS
  };

  class SourceFile {
public:
    template <int N>
    SourceFile(const char (&arr)[N])
        : data_(arr)
        , size_(N - 1)
    {
      const char* slash = strrchr(data_, '/');
      if (slash) {
        data_ = slash + 1;
        size_ -= static_cast<int>(data_ - arr);
      }
    }

    explicit SourceFile(const char* filename)
        : data_(filename)
    {
      const char* slash = strrchr(filename, '/');
      if (slash) {
        data_ = slash + 1;
      }
      size_ -= static_cast<int>(strlen(data_));
    }

    const char* data_;
    int size_;
  };

  Logger(SourceFile file, int line);
  Logger(SourceFile file, int line, LogLevel level);
  Logger(SourceFile file, int line, LogLevel level, const char* func);
  Logger(SourceFile file, int line, bool toAbort);
  ~Logger();

  LogStream& stream() { return impl_.stream_; }

  static LogLevel logLevel();
  static void setLogLevel(LogLevel level);

  typedef void (*OutputFunc)(const char* msg, int len);
  typedef void (*FlushFunc)();

  static void setrOutput(OutputFunc);
  static void setFlush(FlushFunc);
  static void setTimeZero(const TimeZone& tz);

  private:
  class Impl {
public:
    typedef Logger::LogLevel LogLevel;
    Impl(LogLevel level, int old_errno, const SourceFile& file, int line);

    void formatTime();
    void finish();
    TimeStamp time_;
    LogStream stream_;
    LogLevel lecel_;
    int line_;
    SourceFile basename_;

private:
  };

  Impl impl_;
};

extern Logger::LogLevel g_loglevel;

inline Logger::LogLevel Logger::logLevel()
{
  return g_loglevel;
}

// define micro for log

#define LOG_TRACE                                    \
  if (Log::Logger::logLevel() <= Log::Logger::TRACE) \
  Log::Logger(__FILE__, __LINE__, Log::Logger::TRACE, __func__).stream()
#define LOG_DEBUG                                    \
  if (Log::Logger::logLevel() <= Log::Logger::DEBUG) \
  Log::Logger(__FILE__, __LINE__, Log::Logger::DEBUG, __func__).stream()
#define LOG_INFO                                    \
  if (Log::Logger::logLevel() <= Log::Logger::INFO) \
  Log::Logger(__FILE__, __LINE__).stream()
#define LOG_WARN Log::Logger(__FILE__, __LINE__, Log::Logger::WARN).stream()
#define LOG_ERROR Log::Logger(__FILE__, __LINE__, Log::Logger::ERROR).stream()
#define LOG_FATAL Log::Logger(__FILE__, __LINE__, Log::Logger::FATAL).stream()
#define LOG_SYSERR Log::Logger(__FILE__, __LINE__, false).stream()
#define LOG_SYSFATAL Log::Logger(__FILE__, __LINE__, true).stream()

const char* strerror_tl(int saveError);

#define CHECK_NOTNULL(val) \
  LOG::CheckNotNull(__FILE__, __LINE__, "'" #val "' Must be non NULL",(val))

template<typename T>
T* CheckNotNull(Logger::SourceFile file,int line,const char* names,T* prt)
{
  if (prt == nullptr) {
    Logger(file,line,Logger::FATAL).stream() << names;
  }
  return prt;
}


} // Log
  //
#endif

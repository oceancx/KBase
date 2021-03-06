/*
 @ 0xCCCCCCCC
*/

#include <iostream>
#include <thread>
#include <vector>

#include "gtest/gtest.h"

#include "kbase/basic_types.h"
#include "kbase/logging.h"

#if defined(OS_WIN)
#include "kbase/file_util.h"
#endif

namespace {

void ThreadFn(int id)
{
    std::cout << "thread " << id << std::endl;
    LOG(INFO) << "The thread " << id << " is currently running";
}

bool Boolean(bool b)
{
    std::cout << "Boolean() is called\n";
    return b;
}

bool PathExists(const kbase::PathString& path)
{
#if defined(OS_WIN)
    return kbase::PathExists(kbase::Path(path));
#else
    return access(path.c_str(), F_OK) == 0;
#endif
}

}   // namespace

namespace kbase {

TEST(LoggingTest, MT)
{
    LoggingSettings settings;
    settings.log_item_options = LogItemOptions::EnableAll;
    ConfigureLoggingSettings(settings);

    std::vector<std::thread> vth;
    for (int i = 0; i < 5; ++i) {
        vth.emplace_back(ThreadFn, i);
    }

    std::cout << "all are prepared" << std::endl;
    for (auto &th : vth) {
        th.join();
    }
}

TEST(LoggingTest, MinLevelAndConditionalLogging)
{
    LoggingSettings logging_settings;
    logging_settings.min_severity_level = LogSeverity::LogError;
    logging_settings.logging_destination = LoggingDestination::LogToAll;
    ConfigureLoggingSettings(logging_settings);
    LOG(WARNING) << "LOG(WARNING)";
    LOG_IF(ERROR, Boolean(true)) << "LOG_IF(ERROR, Boolean(true))";
    LOG_IF(ERROR, Boolean(false)) << "LOG_IF(ERROR, Boolean(false))";
    DLOG(INFO) << "DLOG(INFO)";
    DLOG(ERROR) << "DLOG(ERROR)";
    DLOG_IF(FATAL, Boolean(true)) << "DLOG_IF(FATAL, Boolean(true))";
    DLOG_IF(FATAL, Boolean(false)) << "DLOG_IF(FATAL, Boolean(false))";
}

TEST(LoggingTest, CustomLogFileName)
{
    PathString log_name(PATH_LITERAL("my_test_debug.log"));
    LoggingSettings logging_settings;
    logging_settings.log_file_path = log_name;
    ConfigureLoggingSettings(logging_settings);
    LOG(INFO) << "testing customized log file name";
    ASSERT_TRUE(::PathExists(log_name));
}

TEST(LoggingTest, FatalLevelCallStack)
{
    ConfigureLoggingSettings(LoggingSettings());
    LOG(FATAL) << "simulate issuing a fatal error";
}

}   // namespace kbase

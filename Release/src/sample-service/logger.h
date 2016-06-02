#ifndef INTEGRATION_TEST_LOGGER_H_
#define INTEGRATION_TEST_LOGGER_H_

#include <unordered_map>
#include <chrono>
#include <string>

enum class operation_result {
    success = 1,
    failure = 2,
    exception = 3
};

enum class operation_name {
    retrieving = 1,
    processing = 2,
    comparing = 3,
    exporting = 4,
    reporting = 5
};

void log_operation(const operation_name& operation_name, const operation_result& result, const std::chrono::system_clock::time_point& start_time, const std::string& sample_id = "", const std::string& description = "");
void log_exception(const operation_name& operation_name, const std::string& sample_id = "", const std::string& exception_message = "");
void log_info(const std::string& operation_name, const operation_result& result, const std::string& description = "");
std::string generate_timestamp(bool short_date = false);
std::string get_period(const std::chrono::system_clock::time_point& start_time);
#endif

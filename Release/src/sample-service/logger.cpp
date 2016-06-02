#include "logger.h"
#include "integration-test-config.h"

#include "boost/filesystem.hpp"
#include <map>
#include <mutex>
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

const std::map<operation_name, const std::string> operation_name_str{
    {operation_name::comparing, "Comparing"},
    {operation_name::exporting, "exporting"},
    {operation_name::processing, "Processing"},
    {operation_name::retrieving, "Retrieving"},
    {operation_name::reporting, "Reporting"}
};

const std::map<operation_result, const std::string> operation_result_str{
    {operation_result::success, "success"},
    {operation_result::failure, "failure"},
    {operation_result::exception, "exception"}
};

std::string format_int(int length, int value) {
    std::stringstream ss;
    ss << std::setw(length) << std::setfill('0') << value;
    return ss.str();
}

std::string get_period(const std::chrono::system_clock::time_point& start_time) {
    std::chrono::system_clock::time_point end_time = std::chrono::system_clock::now();
    std::string duration = format_int(2, std::chrono::duration_cast<std::chrono::minutes>(end_time - start_time).count()) + ":";
    duration += format_int(2, std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count() % 60) + ":";
    duration += format_int(7, std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count());
    return duration;
}

std::string generate_timestamp(bool short_date) {
    std::string timestamp;

    // Get the current time
    std::chrono::system_clock::time_point current_time = std::chrono::system_clock::now();

    // Get local day and time from the time stamp
    std::chrono::seconds sec = std::chrono::duration_cast<std::chrono::seconds>(current_time.time_since_epoch());
    std::time_t t = sec.count();
    struct tm* local_time = localtime(&t);

    timestamp += format_int(4, local_time->tm_year + 1900) + '-';
    timestamp += format_int(2, local_time->tm_mon + 1) + '-';
    timestamp += format_int(2, local_time->tm_mday) + ' ';
    if (short_date) {
        return timestamp.substr(0, timestamp.size() - 1);
    }
    timestamp += format_int(2, local_time->tm_hour) + ':';
    timestamp += format_int(2, local_time->tm_min) + ':';
    timestamp += format_int(2, local_time->tm_sec) + '.';

    // get fractional seconds
    timestamp += format_int(7, (current_time.time_since_epoch() - sec).count());

    return timestamp;
}

void write_log_to_file(const std::stringstream& stream) {
    try {
        std::stringstream final_stream;
        final_stream << "<Record ";
        final_stream << "Time=\"" << generate_timestamp() << "\"";
        final_stream << stream.str();
        final_stream << "/>\n";

        boost::filesystem::path result_folder_path = RESULT_PATH;
        result_folder_path += "/" + generate_timestamp(true);
        if (!boost::filesystem::exists(result_folder_path)) {
            boost::filesystem::create_directories(result_folder_path);
        }
        std::ofstream output_stream(result_folder_path.string() + "/log.xml", std::ios_base::app);
        output_stream << final_stream.str();
        output_stream.close();
    } catch (const std::exception& ex) {
        std::cout << "Logging failed " << ex.what() << std::endl;
    } catch (...) {
        std::cout << "Logging failed " << std::endl;
    }
}

void log_operation(const operation_name& operation_name, const operation_result& result, const std::chrono::system_clock::time_point& start_time, const std::string& sample_id, const std::string& description) {
    try {
        std::stringstream stream;
        stream << " Result=\"" << operation_result_str.at(result) << "\"";
        stream << " Thread=\"" << std::this_thread::get_id() << "\"";
        if (sample_id != "") {
            stream << " SampleId=\"" << sample_id << "\"";
        }
        stream << " Operation=\"" << operation_name_str.at(operation_name) << "\"";
        stream << " Period=\"" << get_period(start_time) << "\"";
        if (description != "") {
            stream << " Description=\"" << description << "\"";
        }
        write_log_to_file(stream);
    } catch (const std::exception& ex) {
        std::cout << "Logging failed " << ex.what() << std::endl;
    } catch (...) {
        std::cout << "Logging failed " << std::endl;
    }
}
void log_exception(const operation_name& operation_name, const std::string& sample_id, const std::string& exception_message) {
    try {
        std::stringstream stream;
        stream << " Thread=\"" << std::this_thread::get_id() << "\"";
        if (sample_id != "") {
            stream << " SampleId=\"" << sample_id << "\"";
        }
        stream << " Operation=\"" << operation_name_str.at(operation_name) << "\"";
        if (exception_message == "") {
            stream << " Message=\"" << "Unknown Exception" << "\"";
        } else {
            stream << " Message=\"" << exception_message << "\"";
        }
        write_log_to_file(stream);
    } catch (const std::exception& ex) {
        std::cout << "Logging failed " << ex.what() << std::endl;
    } catch (...) {
        std::cout << "Logging failed " << std::endl;
    }
}
void log_info(const std::string& operation_name, const operation_result& result, const std::string& description) {
    try {
        std::stringstream stream;
        stream << " Result=\"" << operation_result_str.at(result) << "\"";
        stream << " Thread=\"" << std::this_thread::get_id() << "\"";
        stream << " Operation=\"" << operation_name << "\"";
        if (description != "") {
            stream << " Description=\"" << description << "\"";
        }
        write_log_to_file(stream);
    } catch (const std::exception& ex) {
        std::cout << "Logging failed " << ex.what() << std::endl;
    } catch (...) {
        std::cout << "Logging failed " << std::endl;
    }
}

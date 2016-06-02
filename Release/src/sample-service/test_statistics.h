#ifndef INTEGRATION_TEST_TEST_STATISTICS_H_
#define INTEGRATION_TEST_TEST_STATISTICS_H_

#include "type_statistics.h"

class test_statistics {
public:
    const std::string start_time() const;
    const std::string end_time() const;
    const std::string period() const;
    const std::string sample_set_name() const;
    const std::unordered_map<std::string, type_statistics> documents() const;
    void set_start_time(const std::string& start_time);
    void set_end_time(const std::string& end_time);
    void set_sample_set_name(const std::string& sample_set_name);
    void set_period(const std::string& period);
    void merge(const test_statistics& partial_report);
    const std::unordered_map<std::string, type_statistics>::iterator add_document(const std::string& type_id);
private:
    std::string start_time_;
    std::string end_time_;
    std::string sample_set_name_;
    std::string period_;
    std::unordered_map<std::string, type_statistics> documents_;
};
#endif
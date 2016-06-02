#include "test_statistics.h"

const std::string test_statistics::start_time() const {
    return start_time_;
}
const std::string test_statistics::end_time() const {
    return end_time_;
}
const std::string test_statistics::period() const {
    return period_;
}
const std::string test_statistics::sample_set_name() const {
    return sample_set_name_;
}
const std::unordered_map<std::string, type_statistics> test_statistics::documents() const {
    return documents_;
}

void test_statistics::set_start_time(const std::string& start_time) {
    start_time_ = start_time;
}
void test_statistics::set_end_time(const std::string& end_time) {
    end_time_ = end_time;
}
void test_statistics::set_sample_set_name(const std::string& sample_set_name) {
    sample_set_name_ = sample_set_name;
}
void test_statistics::set_period(const std::string& period) {
    period_ = period;
}

void test_statistics::merge(const test_statistics& partial_report) {
    for (auto& document : partial_report.documents()) {
        auto document_statistics_iterator = add_document(document.first);
        document_statistics_iterator->second.merge(document.second);
    }
}

const std::unordered_map<std::string, type_statistics>::iterator test_statistics::add_document(const std::string& type_id) {
    return documents_.insert({type_id, type_statistics{}}).first;
}
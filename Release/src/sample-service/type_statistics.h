#ifndef INTEGRATION_TEST_TYPE_STATISTICS_H_
#define INTEGRATION_TEST_TYPE_STATISTICS_H_

#include "field_statistics.h"

#include <string>
#include <unordered_map>

class type_statistics {
public:
    void add_recognized();
    void add_misclassified();
    void add_unknown();
    const std::unordered_map<std::string, field_statistics>::iterator add_field(const std::string& field_name);
    const int recognized() const;
    const int misclassified() const;
    const int unknown() const;
    const std::unordered_map<std::string, field_statistics> fields() const;
    void merge(const type_statistics& partial_report);
private:
    int recognized_ = 0;
    int unknown_ = 0;
    int misclassified_ = 0;
    std::unordered_map<std::string, field_statistics> fields_;
};
#endif
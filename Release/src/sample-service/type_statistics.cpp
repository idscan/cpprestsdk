#include "type_statistics.h"

void type_statistics::add_recognized() {
    recognized_++;
}
void type_statistics::add_misclassified() {
    misclassified_++;
}
void type_statistics::add_unknown() {
    unknown_++;
}
const std::unordered_map<std::string, field_statistics>::iterator type_statistics::add_field(const std::string& field_name) {
    return fields_.insert({field_name, field_statistics{}}).first;
}

const int type_statistics::recognized() const {
    return recognized_;
}
const int type_statistics::misclassified() const {
    return misclassified_;
}
const int type_statistics::unknown() const {
    return unknown_;
}
const std::unordered_map<std::string, field_statistics> type_statistics::fields() const {
    return fields_;
}
void type_statistics::merge(const type_statistics& partial_document) {
    recognized_ += partial_document.recognized();
    misclassified_ += partial_document.misclassified();
    unknown_ += partial_document.unknown();
    for (auto& field : partial_document.fields()) {
        auto field_statistics_iterator = add_field(field.first);
        field_statistics_iterator->second.merge(field.second);
    }
}
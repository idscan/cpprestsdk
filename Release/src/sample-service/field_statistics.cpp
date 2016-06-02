#include "field_statistics.h"

void field_statistics::add_correct() {
    reference_count_++;
    correct_++;
};
void field_statistics::add_simple_error() {
    reference_count_++;
    simple_error_++;
};
void field_statistics::add_simple_error_case() {
    reference_count_++;
    simple_error_case_++;
};
void field_statistics::add_simple_error_spaces() {
    reference_count_++;
    simple_error_spaces_++;
};
void field_statistics::add_complex_error() {
    reference_count_++;
    complex_error_++;
};
void field_statistics::add_missing() {
    reference_count_++;
    missing_++;
};
const int field_statistics::reference_count() const {
    return reference_count_;
}
const int field_statistics::correct() const {
    return correct_;
}
const int field_statistics::simple_error() const {
    return simple_error_;
}
const int field_statistics::simple_error_case() const {
    return simple_error_case_;
}
const int field_statistics::simple_error_spaces() const {
    return simple_error_spaces_;
}
const int field_statistics::complex_error() const {
    return complex_error_;
}
const int field_statistics::missing() const {
    return missing_;
}
void field_statistics::merge(const field_statistics& partial_field) {
    reference_count_ += partial_field.reference_count();
    correct_ += partial_field.correct();
    simple_error_ += partial_field.simple_error();
    simple_error_case_ += partial_field.simple_error_case();
    simple_error_spaces_ += partial_field.simple_error_spaces();
    complex_error_ += partial_field.complex_error();
    missing_ += partial_field.missing();
}
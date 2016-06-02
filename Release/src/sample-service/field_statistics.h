#ifndef INTEGRATION_TEST_FIELD_STATISTICS_H_
#define INTEGRATION_TEST_FIELD_STATISTICS_H_

class field_statistics {
public:
    void add_correct();
    void add_simple_error();
    void add_simple_error_case();
    void add_simple_error_spaces();
    void add_complex_error();
    void add_missing();
    const int reference_count() const;
    const int correct() const;
    const int simple_error() const;
    const int simple_error_case() const;
    const int simple_error_spaces() const;
    const int complex_error() const;
    const int missing() const;
    void merge(const field_statistics& partial_field);
private:
    int reference_count_ = 0;
    int correct_ = 0;
    int simple_error_ = 0;
    int simple_error_case_ = 0;
    int simple_error_spaces_ = 0;
    int complex_error_ = 0;
    int missing_ = 0;
};
#endif
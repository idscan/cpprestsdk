#include "sample_set_response.h"

namespace ides {
namespace samplesvc {
sample_set_response::sample_set_response(const std::string& sample_set_name, const status& status, const std::vector<std::string>& items)
    :sample_set_name_(sample_set_name),
    response_status_(status),
    sample_set_items_(items) {}
std::string sample_set_response::sample_set_name() const {
    return sample_set_name_;
}
std::vector<std::string> sample_set_response::sample_set_items() const {
    return sample_set_items_;
}
status sample_set_response::response_status() const {
    return response_status_;
}
}// namespace samplesvc
}// namespace ides
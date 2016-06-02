#include "sample_response.h"

namespace ides {
namespace samplesvc {
sample_response::sample_response(const std::string& sample_id, const status& status, const std::vector<uint8_t>& white_image, const std::vector<uint8_t>& infrared_image, const std::vector<uint8_t>& ultra_image) {
    sample_id_ = sample_id;
    response_status_ = status;
    white_image_ = white_image;
    infrared_image_ = infrared_image;
    ultraviolet_image_ = ultra_image;

}

std::string sample_response::sample_id() const {
    return sample_id_;
}
std::vector<uint8_t> sample_response::white_image() const {
    return white_image_;
}
std::vector<uint8_t> sample_response::infrared_image() const {
    return infrared_image_;
}
std::vector<uint8_t> sample_response::ultraviolet_image() const {
    return ultraviolet_image_;
}
status sample_response::response_status() const {
    return response_status_;
}
std::string sample_response::capturing_device_model() const {
    return capturing_device_model_;
}
std::string sample_response::capturing_device_type() const {
    return capturing_device_type_;
}
std::string sample_response::document_friendly_name() const {
    return document_friendly_name_;
}
bool sample_response::is_extracted() const {
    return is_extracted_;
}
std::string sample_response::type_id() const {
    return type_id_;
}
const std::map<std::string, std::string> sample_response::references() const {
    return references_;
}
void sample_response::set_capturing_device_model(const std::string& capturing_device_model) {
    capturing_device_model_ = capturing_device_model;
}
void sample_response::set_capturing_device_type(const std::string& capturing_device_type) {
    capturing_device_type_ = capturing_device_type;
}
void sample_response::set_friendly_name(const std::string& friendly_name) {
    document_friendly_name_ = friendly_name;
}
void sample_response::set_is_extracted(const bool is_extracted) {
    is_extracted_ = is_extracted;
}
void sample_response::set_references(const std::map<std::string, std::string>& references) {
    references_ = references;
}
void sample_response::set_type_id(const std::string& type_id) {
    type_id_ = type_id;
}
}// namespace samplesvc
}// namespace ides
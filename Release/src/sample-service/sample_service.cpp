#include "sample_service.h"

#include <boost/regex.h>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <iostream>
#include <stdio.h>
#include <regex>

namespace ides {
namespace samplesvc {
enum mode {
    white = 1,
    all_images = 2,
    all_data = 3,
};

//sample id should like GBRDL0100A-S-1234567 
//GBR for country code ,DL for category ,0100 type number, A/B for side 
//S/C for scanner or camera,7 digit unique number for sample 
void check_sample_id_format(const std::string& sample_id) {
    boost::RegEx sample_id_regex("[A-Za-z]{5}\\d{4}[A-Za-z]\\-[CcSs]\\-\\d{7}");
    if (!sample_id_regex.Match(sample_id))
        throw std::runtime_error("invalid sample id format");
}

const std::string service_url = "https://samplesservice.idscanbiometrics.com/ResultPersistPublish/api/Samples/";
web::http::uri_builder initialize_builder_sample_request(const std::string& method_name, const std::string& sample_id, const std::string& username, const std::string& password) {
    web::http::uri_builder builder(utility::conversions::to_string_t(method_name));
    builder.append_query(U("sample_id=" + utility::conversions::to_string_t(sample_id)));
    builder.append_query(U("&username=" + utility::conversions::to_string_t(username)));
    builder.append_query(U("&password=" + utility::conversions::to_string_t(password)));
    return builder;
}

web::http::uri_builder initialize_builder_sample_set_request(const std::string& sample_set_name, const std::string& username, const std::string& password) {
    web::http::uri_builder builder(U("/GetSamplesetItems?"));
    builder.append_query(U("sampleSetName=" + utility::conversions::to_string_t(sample_set_name)));
    builder.append_query(U("&username=" + utility::conversions::to_string_t(username)));
    builder.append_query(U("&password=" + utility::conversions::to_string_t(password)));
    return builder;
}

status extract_status(const web::json::value& value) {
    if (value.is_null()) {
        return status::failure;
    } else if (value.as_integer() == 1) {
        return status::success;
    } else if (value.as_integer() == 3) {
        return status::not_found;
    } else if (value.as_integer() == 4) {
        return status::invalid_credentials;
    } else {
        return status::failure;
    }
}

std::map<std::string, std::string> extract_references(const web::json::value& value) {
    std::map<std::string, std::string> references{};
    if (!value.is_null()) {
        auto json_value_object = value.as_object();
        for (auto iter = json_value_object.cbegin(); iter != json_value_object.cend(); ++iter) {
            if (!iter->second.is_null()) {
                references.insert(std::make_pair(utility::conversions::to_utf8string(iter->first), utility::conversions::to_utf8string(iter->second.as_string())));
            }
        }
    }
    return references;
}

sample_response retrieve_sample_request(const std::string& sample_id, const std::string& username, const std::string& password, const mode& retrieve_mode) {
    sample_response sample;
    check_sample_id_format(sample_id);
    web::http::client::http_client client(utility::conversions::to_string_t(service_url));
    web::http::uri_builder builder;
    if (retrieve_mode == all_images) {
        builder = initialize_builder_sample_request("/GetSample?", sample_id, username, password);
    } else if (retrieve_mode == all_data) {
        builder = initialize_builder_sample_request("/GetSampleFullData?", sample_id, username, password);
    } else {
        builder = initialize_builder_sample_request("/GetSampleWhite?", sample_id, username, password);
    }
    client.request(web::http::methods::GET, builder.to_string()).then([=, &sample](web::http::http_response response) {
        if (response.status_code() == web::http::status_codes::OK) {
            response.extract_json().then([=, &sample](web::json::value json_value) {
                if (!json_value.is_null()) {
                    status response_status = extract_status(json_value.at(U("status")));
                    if (!json_value.at(U("white")).is_null()) {
                        if (!json_value.at(U("infrared")).is_null() && !json_value.at(U("ultraviolet")).is_null()) {
                            sample = sample_response(utility::conversions::to_utf8string(json_value.at(U("id")).as_string()), response_status, utility::conversions::from_base64(json_value.at(U("white")).as_string()),
                                                     utility::conversions::from_base64(json_value.at(U("infrared")).as_string()), utility::conversions::from_base64(json_value.at(U("ultraviolet")).as_string()));
                        } else if (!json_value.at(U("infrared")).is_null()) {
                            sample = sample_response(utility::conversions::to_utf8string(json_value.at(U("id")).as_string()), response_status, utility::conversions::from_base64(json_value.at(U("white")).as_string()),
                                                     utility::conversions::from_base64(json_value.at(U("infrared")).as_string()));
                        } else if (!json_value.at(U("ultraviolet")).is_null()) {
                            sample = sample_response(utility::conversions::to_utf8string(json_value.at(U("id")).as_string()), response_status, utility::conversions::from_base64(json_value.at(U("white")).as_string()),
                                                     utility::conversions::from_base64(json_value.at(U("ultraviolet")).as_string()));
                        } else {
                            sample = sample_response(utility::conversions::to_utf8string(json_value.at(U("id")).as_string()), response_status, utility::conversions::from_base64(json_value.at(U("white")).as_string()));
                        }
                        // Get sample information and manual entry for it
                        if (retrieve_mode == all_data) {
                            sample.set_capturing_device_model(!json_value.at(U("CapturingDeviceModelField")).is_null() ? utility::conversions::to_utf8string(json_value.at(U("CapturingDeviceModelField")).as_string()) : "");
                            sample.set_capturing_device_type(!json_value.at(U("CapturingDeviceTypeEnum")).is_null() ? utility::conversions::to_utf8string(json_value.at(U("CapturingDeviceTypeEnum")).as_string()) : "");
                            sample.set_friendly_name(!json_value.at(U("DocumentFriendlyNameField")).is_null() ? utility::conversions::to_utf8string(json_value.at(U("DocumentFriendlyNameField")).as_string()) : "");
                            sample.set_is_extracted(!json_value.at(U("IsExtractedField")).is_null() ? json_value.at(U("IsExtractedField")).as_bool() : true);
                            sample.set_references(extract_references(json_value.at(U("references"))));
                            sample.set_type_id(!json_value.at(U("TypeIdField")).is_null() ? utility::conversions::to_utf8string(json_value.at(U("TypeIdField")).as_string()) : "");
                        }
                    } else {
                        sample = sample_response(utility::conversions::to_utf8string(json_value.at(U("id")).as_string()), response_status);
                    }
                } else {
                    sample = sample_response(sample_id, status::failure);
                }
            }).wait();
        } else {
            sample = sample_response(sample_id, status::failure);
        }
    }).wait();
    return sample;
}

sample_response retrieve_sample_white_image(const std::string& sample_id, const std::string& username, const std::string& password) {
    return retrieve_sample_request(sample_id, username, password, white);
}

sample_response retrieve_sample_all_images(const std::string& sample_id, const std::string& username, const std::string& password) {
    return retrieve_sample_request(sample_id, username, password, all_images);
}

std::map<std::string, std::string> retrieve_sample_references(const std::string& sample_id, const std::string& username, const std::string& password) {
    std::map<std::string, std::string> reference;
    check_sample_id_format(sample_id);
    web::http::client::http_client client(utility::conversions::to_string_t(service_url));
    web::http::uri_builder builder = initialize_builder_sample_request("/GetSampleRef?", sample_id, username, password);
    client.request(web::http::methods::GET, builder.to_string()).then([=, &reference](web::http::http_response response) {
        if (response.status_code() == web::http::status_codes::OK) {
            response.extract_json().then([=, &reference](web::json::value json_value) {
                reference = extract_references(json_value);
            }).wait();
        }
    }).wait();
    return reference;
}

sample_response retrieve_sample(const std::string& sample_id, const std::string& username, const std::string& password) {
    return retrieve_sample_request(sample_id, username, password, all_data);
}

sample_set_response retrieve_sample_set_items(std::string sample_set_name, const std::string& username, const std::string& password) {
    sample_set_response sample_set_response_ = sample_set_response(sample_set_name, status::failure, std::vector<std::string>());
    for (size_t pos = sample_set_name.find(' '); pos != std::string::npos; pos = sample_set_name.find(' ', pos)) {
        sample_set_name.replace(pos, 1, "%20");
    }
    web::http::client::http_client client(utility::conversions::to_string_t(service_url));
    web::http::uri_builder builder;
    builder = initialize_builder_sample_set_request(sample_set_name, username, password);
    client.request(web::http::methods::GET, builder.to_string()).then([=, &sample_set_response_](web::http::http_response response) {
        if (response.status_code() == web::http::status_codes::OK) {
            response.extract_json().then([=, &sample_set_response_](web::json::value json_value) {
                status response_status = extract_status(json_value.at(U("ResponseStatus")));
                if (!json_value.at(U("SamplesId")).is_null()) {
                    std::vector<std::string> samples_list;
                    samples_list.reserve(json_value.at(U("SamplesId")).as_array().size());
                    auto items = json_value.at(U("SamplesId"));
                    for (auto iter = items.as_array().cbegin(); iter != items.as_array().cend(); ++iter) {
                        samples_list.push_back(utility::conversions::to_utf8string(iter->as_string()));
                    }
                    sample_set_response_ = sample_set_response(sample_set_name, response_status, samples_list);
                }
            }).wait();
        }
    }).wait();
    return sample_set_response_;
}
}// namespace samplesvc
}// namespace ides
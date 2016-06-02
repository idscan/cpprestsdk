#include "integration-test-config.h"
#include "logger.h"
#include "test_statistics.h"
//#include "internal_constants.h"
#include <document-sample-service/sample_service.h>
#include <document-sample-service/sample_response.h>
//#include <document-expert-system/document_processing_service.h>
#include "config.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/detail/ptree_utils.hpp>
#include <boost/filesystem.hpp>

#include <gtest/gtest.h>
#include <vector>
#include <chrono>
#include <mutex>
#include <thread>
#include <chrono>

std::string root_path;
std::vector<std::string> sample_set_items;
void create_folder(const boost::filesystem::path& folder_path) {
    try {
        if (!boost::filesystem::exists(folder_path)) {
            boost::filesystem::create_directories(folder_path);
        }
    } catch (const std::exception& ex) {
        log_exception(operation_name::exporting, ex.what());
    } catch (...) {
        log_exception(operation_name::exporting);
    }
}

//void compare_field(const std::pair<std::string, std::string>& reference_field, const std::unordered_map<std::string, ides::extracted_field>& processed_result,
//                   const std::unordered_map<std::string, type_statistics>::iterator& report_document_iterator) {
//    std::unordered_map<std::string, ides::extracted_field>::const_iterator result_field_iterator = processed_result.find(reference_field.first);
//    auto field_statistics_iterator = report_document_iterator->second.add_field(reference_field.first);
//
//    if (result_field_iterator == processed_result.end()) {
//        field_statistics_iterator->second.add_missing();
//        return;
//    }
//
//    std::string reference_field_value(reference_field.second);
//    std::string result_field_value(result_field_iterator->second.value());
//    if (reference_field_value == result_field_value) {
//        field_statistics_iterator->second.add_correct();
//        return;
//    } else if (boost::iequals(reference_field_value, result_field_value)) {
//        field_statistics_iterator->second.add_simple_error_case();
//        return;
//    }
//
//    remove(reference_field_value.begin(), reference_field_value.end(), ' ');
//    remove(result_field_value.begin(), result_field_value.end(), ' ');
//    if (reference_field_value == result_field_value) {
//        field_statistics_iterator->second.add_simple_error_spaces();
//    } else if (boost::iequals(reference_field_value, result_field_value)) {
//        field_statistics_iterator->second.add_simple_error();
//    } else {
//        field_statistics_iterator->second.add_complex_error();
//    }
//}

bool compare_category(const std::string& reference_category_code, const std::string& result_category) {
    return ((result_category == "Passport" && reference_category_code == "P")
            || (result_category == "Identity card" && reference_category_code == "I")
            || (result_category == "Visa" && reference_category_code == "V"));
}

//void compare_document(const std::string& sample_id, const std::map<std::string, std::string>& references, const ides::document& processed_result, test_statistics& partial_report) {
//    try {
//        std::chrono::system_clock::time_point start_time = std::chrono::system_clock::now();
//        std::string reference_type_id = sample_id.substr(0, 10);
//        auto document_statistics_iterator = partial_report.add_document(reference_type_id);
//        std::string reference_country_code = sample_id.substr(0, 3);
//        std::string reference_category_code = sample_id.substr(3, 1);
//
//        bool is_category_correct = compare_category(reference_category_code, processed_result.category());
//        if (processed_result.issuing_country_code().size() == 0) {
//            document_statistics_iterator->second.add_unknown();
//        } else if (processed_result.issuing_country_code() != reference_country_code || !is_category_correct) {
//            document_statistics_iterator->second.add_misclassified();
//        } else {
//            document_statistics_iterator->second.add_recognized();
//        }
//
//        for (const auto& field : references) {
//            compare_field(field, processed_result.extracted_fields(), document_statistics_iterator);
//        }
//        log_operation(operation_name::comparing, operation_result::success, start_time, sample_id);
//    } catch (const std::exception& ex) {
//        log_exception(operation_name::comparing, sample_id, ex.what());
//    } catch (...) {
//        log_exception(operation_name::comparing, sample_id);
//    }
//}

void write_result(const std::string& sample_type_id, const std::string& sample_id/*, const ides::document& processed_result*/) {
    try {
        std::chrono::system_clock::time_point start_time = std::chrono::system_clock::now();
        boost::filesystem::path result_folder_path = root_path;
        result_folder_path += "/" + sample_type_id;
        create_folder(result_folder_path);
        std::string file_path = result_folder_path.string() + "/" + sample_id + ".xml";

        using boost::property_tree::ptree;
        ptree document;
        ptree extracted_fields;
        ptree authentecations;

        // get document properties
//        document.put("Document.Category", processed_result.category());
//        document.put("Document.IssuingCountryCode", processed_result.issuing_country_code());
//        switch (processed_result.authentication_state()) {
//            case ides::document_authentication_state::failed: {
//                document.put("Document.AuthenticationState", "failed");
//                break;
//            }
//            case ides::document_authentication_state::passed: {
//                document.put("Document.AuthenticationState", "passed");
//                break;
//            }
//            case ides::document_authentication_state::undetermined: {
//                document.put("Document.AuthenticationState", "undetermined");
//                break;
//            }
//        }
//        document.put("Document.Id", processed_result.type_id());
//        document.put("Document.Issue", processed_result.issue());
//        document.put("Document.IssuingCountryName", processed_result.issuing_country_name());
//        document.put("Document.IssuingStateCode", processed_result.issuing_state_code());
//        document.put("Document.IssuingStateName", processed_result.issuing_state_name());
//        document.put("Document.Name", processed_result.name());
//        document.put("Document.subtype", processed_result.subtype());
//        document.put("Document.type", processed_result.type());

        // get document extracted fields
//        for (const auto& field : processed_result.extracted_fields()) {
//            ptree node;
//            node.put("Name", field.second.name());
//            node.put("Value", field.second.value());
//            node.put("description", field.second.description());
//            extracted_fields.add_child("Field", node);
//        }

        // get document authentication checks
//        for (const auto& check : processed_result.authentication_checks()) {
//            ptree node;
//            node.put("Id", check.second.id());
//            node.put("Group", check.second.group());
//            node.put("Title", check.second.title());
//            node.put("Description", check.second.description());
//            switch (check.second.state()) {
//                case ides::authentication_check_state::failed: {
//                    node.put("State", "failed");
//                    break;
//                }
//                case ides::authentication_check_state::passed: {
//                    node.put("State", "passed");
//                    break;
//                }
//                case ides::authentication_check_state::skipped: {
//                    node.put("State", "skipped");
//                    break;
//                }
//                case ides::authentication_check_state::undetermined: {
//                    node.put("State", "undetermined");
//                    break;
//                }
//            }
//            node.put("StateDescription", check.second.state_description());
//            authentecations.add_child("Check", node);
//        }

        // add Extracted Fields and Authentication checks to document
        document.add_child("Document.ExtractedFields", extracted_fields);
        document.add_child("Document.AuthenticationChecks", authentecations);

        boost::property_tree::write_xml(file_path, document, std::locale(), boost::property_tree::xml_writer_make_settings<ptree::key_type>(' ', 1u));
        log_operation(operation_name::exporting, operation_result::success, start_time, sample_id);
    } catch (const std::exception& ex) {
        log_exception(operation_name::exporting, sample_id, ex.what());
    } catch (...) {
        log_exception(operation_name::exporting, sample_id);
    }
}

void write_report(const test_statistics& test_report) {
    try {
        std::chrono::system_clock::time_point start_time = std::chrono::system_clock::now();
        boost::filesystem::path file_path = root_path;
        file_path += "/report.xml";

        using boost::property_tree::ptree;
        ptree report;
        report.put("Report.<xmlattr>.SampleSet", test_report.sample_set_name());
        report.put("Report.<xmlattr>.StartTime", test_report.start_time());
        report.put("Report.<xmlattr>.EndTime", test_report.end_time());
        report.put("Report.<xmlattr>.Period", test_report.period());

        ptree documents;
        // get document properties
        for (auto& document : test_report.documents()) {
            ptree document_node;
            document_node.put("<xmlattr>.TypeId", document.first);
            document_node.put("<xmlattr>.Recognized", document.second.recognized());
            document_node.put("<xmlattr>.Misclassified", document.second.misclassified());
            document_node.put("<xmlattr>.Unknown", document.second.unknown());

            // get document extracted fields
            ptree fields;
            for (auto& field : document.second.fields()) {
                ptree node;
                node.put("<xmlattr>.Name", field.first);
                node.put("<xmlattr>.ReferenceCount", field.second.reference_count());
                node.put("<xmlattr>.Correct", field.second.correct());
                node.put("<xmlattr>.SimpleError", field.second.simple_error());
                node.put("<xmlattr>.ComplexError", field.second.complex_error());
                node.put("<xmlattr>.SimpleErrorSpace", field.second.simple_error_spaces());
                node.put("<xmlattr>.SimpleErrroCase", field.second.simple_error_case());
                node.put("<xmlattr>.Missing", field.second.missing());
                fields.add_child("Field", node);
            }
            document_node.add_child("ExtractedFields", fields);
            documents.add_child("Document", document_node);
        }
        report.add_child("Report.Documents", documents);

        boost::property_tree::write_xml(file_path.string(), report, std::locale(), boost::property_tree::xml_writer_make_settings<ptree::key_type>(' ', 1u));
        log_operation(operation_name::reporting, operation_result::success, start_time);
    } catch (const std::exception& ex) {
        log_exception(operation_name::reporting, ex.what());
    } catch (...) {
        log_exception(operation_name::reporting);
    }
}

std::mutex sample_locker;
bool get_sample_id(std::vector<std::string>& samples_list, std::string& sample_id) {
    std::lock_guard<std::mutex> locker(sample_locker);
    if (samples_list.empty()) {
        return false;
    } else {
        try {
            sample_id = samples_list.back();
            samples_list.pop_back();
            return true;
        } catch (...) {
            return false;
        }
    }
}

void process_samples(const std::string& username, const std::string& password, test_statistics* const final_report) {
    std::string sample_id;
    test_statistics partial_report{};
    // create processor
//    ides::document_processing_service processor;
    log_info("Initialize", operation_result::success, "create processor");

    while (get_sample_id(sample_set_items, sample_id)) {
        try {
            std::chrono::system_clock::time_point start_time = std::chrono::system_clock::now();
            ides::samplesvc::sample_response sample = ides::samplesvc::retrieve_sample(sample_id, username, password);
            if (sample.response_status() != ides::samplesvc::status::success) {
                log_operation(operation_name::retrieving, operation_result::failure, start_time, sample_id, "Get sample from sample service failed");
                continue;
            }
            if (sample.white_image().size() == 0) {
                log_operation(operation_name::retrieving, operation_result::failure, start_time, sample_id, "White image is empty");
                continue;
            }
            log_operation(operation_name::retrieving, operation_result::success, start_time, sample_id, "Get sample from sample service succeeded");
            try {
                auto image = sample.white_image();
                start_time = std::chrono::system_clock::now();
//                ides::document document = processor.process_document_image((const char*)& image[0], image.size());

                std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(2000));

                log_operation(operation_name::processing, operation_result::success, start_time, sample_id);
//                compare_document(sample.sample_id(), sample.references(), document, partial_report);
                write_result(sample.type_id(), sample_id/*, document*/);
            } catch (const std::exception& ex) {
                log_exception(operation_name::processing, sample_id, ex.what());
            } catch (...) {
                log_exception(operation_name::processing, sample_id);
                continue;
            }
        } catch (const std::exception& ex) {
            log_exception(operation_name::processing, sample_id, ex.what());
        } catch (...) {
            log_exception(operation_name::processing);
        }
    }
    final_report->merge(partial_report);
    log_info("Thread Finish", operation_result::success, "partial report merged");
}

TEST(IntegrationTest, processSamples) {

    boost::filesystem::path readable_path = resource_path / "external-res";
//    std::unordered_map<std::string, std::string> settings{
//        {KEY_RESOURCE_ROOT_PATH, readable_path.string()},
//        {KEY_STORAGE_ROOT_PATH, output_path.string()}
//    };
//    ides::init(settings);

    std::string username = "L.Demo";
    std::string password = "k@p7u;-iiHdL";
    test_statistics final_report{};
    int threads_cout = THREAD_COUNT;

    // check result folder path  
    root_path = RESULT_PATH;
    if (root_path.empty()) {
        root_path = boost::filesystem::current_path().string();
    }
    root_path += "/" + generate_timestamp(true);
    boost::filesystem::path result_folder_path = root_path;
    try {
        create_folder(result_folder_path);
    } catch (...) {
        FAIL() << "Failed to create Folder for result, Provided Path is: " << result_folder_path.string();
    }
    log_info("Initialize", operation_result::success, "Start test");

    // check resource path
    if (!boost::filesystem::exists(resource_path)) {
        FAIL() << "wrong resource Path, resource path is: " << resource_path.string() << std::endl;
    }

    // check sample set
    ides::samplesvc::sample_set_response sample_set = ides::samplesvc::retrieve_sample_set_items(SAMPLE_SET_NAME, username, password);
    switch (sample_set.response_status()) {
        case ides::samplesvc::status::not_found: {
            log_info("Initialize", operation_result::failure, "Sample_Set is not exists");
            FAIL() << "sample set is not exists";
            break;
        }
        case ides::samplesvc::status::failure: {
            log_info("Initialize", operation_result::failure, "retrieve sample_set failed");
            FAIL() << "error in getting sample set items";
            break;
        }
        case ides::samplesvc::status::invalid_credentials: {
            log_info("Initialize", operation_result::failure, "retrieve sample_set failed invalid_credentials");
            FAIL() << "retrieve sample_set failed invalid_credentials";
            break;
        }
    }
    if (sample_set.response_status() == ides::samplesvc::status::success && sample_set.sample_set_items().size() == 0) {
        log_info("Initialize", operation_result::failure, "Sample Set is empty");
        FAIL() << "Sample Set is empty";
    }
    log_info("Initialize", operation_result::success, "Get sample Set Items");

    // start test        
    auto start = std::chrono::system_clock::now();
    std::vector<std::thread> all_threads;
    sample_set_items = sample_set.sample_set_items();

    test_statistics* final_report_ptr = &final_report;
    final_report_ptr->set_start_time(generate_timestamp());
    // create threads for processing and wait until they finish
    for (auto i = 0; i < threads_cout; i++) {
        all_threads.push_back(std::thread(process_samples, username, password, final_report_ptr));
    }
    for (auto& thread : all_threads) {
        thread.join();
    }
    log_info("Finish", operation_result::success, "All thread finished");

    final_report_ptr->set_end_time(generate_timestamp());
    final_report_ptr->set_period(get_period(start));
    write_report(final_report);
}
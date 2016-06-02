//
//	samples.h
//	sample-service
//
//	created by kahil on 30/12/2015
//

#ifndef SAMPLE_SERVICE_SAMPLE_SERVICE_H_
#define SAMPLE_SERVICE_SAMPLE_SERIVCE_H_

#include <sample_response.h>
#include <sample_set_response.h>

#include <vector>
#include <stdio.h>
#include <map>

namespace ides {
namespace samplesvc {

/**
* This function is use to return a white image from the sample database via its ID. The username and password are needed in order to authenticate the use.
* @param sample_id ID of the sample you want to retrieve from the database. The format is XXXXX0000X-X-0000000.
* @param username you should have an account on our sample service to retrieve samples.
* @param password pass your sample service account password to do authentication for each request.
* @return The response which contains the white image and the id of requested sample
*/
sample_response retrieve_sample_white_image(const std::string& sample_id, const std::string& username, const std::string& password);

/**
* This function is use to return all sample images (white,infrared and ultraviolet) from the sample database via its ID. The username and password are needed in order to authenticate the use.
* @param sample_id ID of the sample you want to retrieve from the database. The format is XXXXX0000X-X-0000000.
* @param username you should have an account on our sample service to retrieve samples.
* @param password pass your sample service account password to do authentication for each request.
* @return The response which contains all images and the id of requested sample
*/
sample_response retrieve_sample_all_images(const std::string& sample_id, const std::string& username, const std::string& password);

/**
* This function is use to return all information which are exists on the sample like (full_name and document_number) which are entered manual by human via its ID. The username and password are needed in order to authenticate the use..
* @param sample_id ID of the sample we want to retrieve from the database. The format is XXXXX0000X-X-0000000.
* @param username you should have an account on our sample service to retrieve samples.
* @param password pass your sample service account password to do authentication for each request.
* @return all personal information which written on the requested sample
*/
std::map<std::string, std::string> retrieve_sample_references(const std::string& sample_id, const std::string& username, const std::string& password);

/**
* This function is use to return all sample images (white,infrared and ultraviolet) and the manual entry for it's information from the sample database via its ID. The username and password are needed in order to authenticate the use.
* @param sample_id ID of the sample you want to retrieve from the database. The format is XXXXX0000X-X-0000000.
* @param username you should have an account on our sample service to retrieve samples.
* @param password pass your sample service account password to do authentication for each request.
* @return The response which contains (all images, id of requested sample, capturing device info and the information which written of the document)
*/
sample_response retrieve_sample(const std::string& sample_id, const std::string& username, const std::string& password);

/**
* This function is use to return all sample ids which exists in test sample set.
* @param sample_set_name to select which group of samples that user want to test.
* @param username you should have an account on our sample service to retrieve samples.
* @param password pass your sample service account password to do authentication for each request.
* @return The response is a list of sample ids that exists in this group
*/
sample_set_response retrieve_sample_set_items(std::string sample_set_name, const std::string& username, const std::string& password);
}// namespace samplesvc
}// namespace ides

#endif


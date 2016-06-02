//
//	sample_response.h
//	sample-service
//
//	created by kahil on 30/12/2015
//

#ifndef SAMPLE_SERVICE_SAMPLE_RESPONSE_H_
#define SAMPLE_SERVICE_SAMPLE_RESPONSE_H_

#include "response_status.h"

#include <vector>
#include <stdio.h>
#include <string>
#include <stdint.h>
#include <map>

namespace ides {
namespace samplesvc {
/**
*   A sample_response class, which is the result for retrieve sample request contains the sample images and it's ID
*/
class sample_response {
public:
    /**
    * A constructor.
    * default constructor without any parameters or logic
    */
    sample_response() {};
    /**
    * A constructor.
    * constructor with 5 parameters present sample information
    * @param sample_id ID of the retrieved sample.
    * @param status the status of the response.
    * @param white_image  Where we capture thee images for the document using different lights this image is the visible one.
    * @param infrared_image we capture thee images for the document using different lights this image produced by infrared light.
    * @param ultra_image Where we capture thee images for the document using different lights this image produced by ultraviolet light.
    */
    sample_response(const std::string& sample_id, const status& status, const std::vector<uint8_t>& white_image = {}, const std::vector<uint8_t>& infrared_image = {}, const std::vector<uint8_t>& ultra_image = {});
    /**
    * a public variable.
    * sample_id ID of the sample that you retrieved from sample service DB like XXXXX0000X-X-0000000.
    */
    std::string sample_id() const;
    /**
    * a public variable.
    * white_image Where we capture thee images for the document using different lights this image is the visible one.
    */
    std::vector<uint8_t> white_image() const;
    /**
    * a public variable.
    * infrared_image Where we capture thee images for the document using different lights this image produced by infrared light.
    */
    std::vector<uint8_t> infrared_image() const;
    /**
    * a public variable.
    * ultraviolet_image Where we capture thee images for the document using different lights this image produced by ultraviolet light.
    */
    std::vector<uint8_t> ultraviolet_image() const;
    /**
    * a public variable.
    * capturing_device_model it will return to us the model for capturing device like (samsung galaxy 6).
    */
    std::string capturing_device_model() const;
    /**
    * a public variable.
    * capturing_device_type it present the type of capturing device like (A4 Scanner,Scanner and Camera).
    */
    std::string capturing_device_type() const;
    /**
    * a public variable.
    * document_friendly_name it present the name for this sample type like (UK Driving license Provisional 2014).
    */
    std::string document_friendly_name() const;
    /**
    * a public variable.
    * is_extracted it present if the document is extracted from the image, by default for A4 scanner it will be false and for 3M Scanner it will be true.
    */
    bool is_extracted() const;
    /**
    * a public variable.
    * type_id we defined many types in our DB each type present one of document that we support in our sdk, this field shows us which type belonged to.
    */
    std::string type_id() const;
    /**
    * a public variable.
    * references contains all information which are exists on the sample like (full_name and document_number) which are entered manual by human.
    */
    const std::map<std::string, std::string> references() const;
    /**
    * a public variable.
    * status present response status.
    */
    status response_status() const;
    /**
    * set sample's capturing device model value.
    * @param capturing_device_model the capturing device model that we used to get this sample.
    */
    void set_capturing_device_model(const std::string& capturing_device_model);
    /**
    * set sample's capturing device type value.
    * @param capturing_device_type the capturing device type which we used to get this sample.
    */
    void set_capturing_device_type(const std::string& capturing_device_type);
    /**
    * set sample's type id this type id created by idscan team to distinguish between documents that we support.
    * @param type_id it's the type code for this samples which defined by idscan team.
    */
    void set_type_id(const std::string& type_id);
    /**
    * set friendly name of the type that sample belongs to.
    * @param friendly_name the type name for this samples which defined by idscan team.
    */
    void set_friendly_name(const std::string& friendly_name);
    /**
    * set is the document extracted from the image.
    * @param is_extracted it determine if the sample contains just the document or it's bigger than document and contains many different things.
    */
    void set_is_extracted(const bool is_extracted);
    /**
    * set sample's references which present the personal information on this sample entered by human.
    * @param references contains all information which are exists on the sample like (full_name and document_number) which are entered manual by human.
    */
    void set_references(const std::map<std::string, std::string>& references);
private:
    std::string sample_id_;
    std::vector<uint8_t> white_image_;
    std::vector<uint8_t> infrared_image_;
    std::vector<uint8_t> ultraviolet_image_;
    std::string capturing_device_model_;
    std::string capturing_device_type_;
    std::string document_friendly_name_;
    bool is_extracted_;
    std::string type_id_;
    std::map<std::string, std::string> references_;
    status response_status_;
};
}// namespace samplesvc
}// namespace ides

#endif
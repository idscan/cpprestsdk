
#ifndef SAMPLE_SERVICE_SAMPLE_SET_RESPONSE_H_
#define SAMPLE_SERVICE_SAMPLE_SET_RESPONSE_H_

#include "response_status.h"

#include <stdio.h>
#include <string>
#include <vector>

namespace ides {
namespace samplesvc {
/**
*   A sample_set_response class, which is the result for retrieve sample set request contains the items of this set which are samples id
*/
class sample_set_response {
public:
    /**
    * A constructor.
    * constructor with 3 parameters present sample set response information
    * @param sample_set_name the name of retrieved sample set.
    * @param status the status of the response.
    * @param items  Where we group samples by sample set this parameter present a list of samples id.
    */
    sample_set_response(const std::string& sample_set_name, const status& status, const std::vector<std::string>& items);
    /**
    * a public variable.
    * sample_set_name Where we group sample by sample set this variable present the name of this samples group.
    */
    std::string sample_set_name() const;
    /**
    * a public variable.
    * sample_set_name Where we group samples by sample set this variable present a list of samples id which are contains in this group.
    */
    std::vector<std::string> sample_set_items() const;
    /**
    * a public variable.
    * status present response status.
    */
    status response_status() const;
private:
    std::string sample_set_name_;
    status response_status_;
    std::vector<std::string> sample_set_items_;
};
}// namespace samplesvc
}// namespace ides
#endif

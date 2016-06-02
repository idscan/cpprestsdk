#ifndef SAMPLE_SERVICE_RESPONSE_STATUS_H_
#define SAMPLE_SERVICE_RESPONSE_STATUS_H_

namespace ides {
namespace samplesvc {
/**
* An enum.
* this enum show the response status.
*/
enum class status {
    success = 1,/**< enum value success. */
    failure = 2,/**< enum value failure. */
    not_found = 3,/**< enum value not_found. */
    invalid_credentials = 4/**< enum value invalid_credentials. */
};
}// namespace samplesvc
}// namespace ides
#endif
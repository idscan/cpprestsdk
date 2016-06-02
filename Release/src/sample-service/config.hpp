#ifndef TEST_INTEGRATION_CONFIG
#define TEST_INTEGRATION_CONFIG

#define BOOST_FILESYSTEM_VERSION 3
#include <boost/filesystem.hpp>

extern boost::filesystem::path executable_path;
extern boost::filesystem::path output_path;
extern boost::filesystem::path resource_path;

#endif // TEST_INTEGRATION_CONFIG

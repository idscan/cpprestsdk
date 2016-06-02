#include <boost/filesystem/path.hpp>

#include <iostream>
#include <fstream>

#include <memory>
#include <string>

#include "gtest/gtest.h"
#include "config.hpp"

boost::filesystem::path executable_path{};
boost::filesystem::path output_path{};
boost::filesystem::path resource_path{};

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    executable_path = resource_path = boost::filesystem::current_path();
    boost::filesystem::path opt1 = resource_path / "external_res";
    boost::filesystem::path opt2 = resource_path / "test-data";
    if (!boost::filesystem::exists(opt1) && !boost::filesystem::exists(opt2)) {
        // Data are placed in root binaries dir, but in case of Mac OS and Windows, additional
        // folder are added to binaries dir for build configuration 'Debug' or
        // 'Release', so we need to remove its name too in this case.
        resource_path = resource_path.branch_path();
    }
    output_path = resource_path;
    return RUN_ALL_TESTS();
}

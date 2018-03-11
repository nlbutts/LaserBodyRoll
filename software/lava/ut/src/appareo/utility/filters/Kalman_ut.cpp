/**
 * Copyright (c) 2017 Appareo Systems, LLC.
 * 1810 NDSU Research Park Circle North
 * Fargo ND, 58102
 * All rights reserved.
 *
 * This is the confidential and proprietary information of Appareo Systems, LLC. You shall not
 * disclose such confidential information and shall use it only in accordance with the terms
 * of the license agreement you entered into with Appareo.
 *
 * File:    npr101_UT.cpp
 * Creator: Nick Butts
 * Date:    March 10, 2017
 *
 * Copyright Version 1.0
 */

#include <stdint.h>
#include <array>
#include <iostream>
#include <fstream>
#include <gmock/gmock.h>
#include <appareo/utility/filter/Kalman.h>

using ::testing::_;
using ::testing::Return;

using std::cout;
using std::endl;

namespace Appareo {
namespace Utility {
namespace Filter {

auto loadData(std::string filename)
{
    std::string pwd(getcwd(nullptr, 0));
    std::cout << pwd << std::endl;
    auto pos = pwd.find("jenkins");
    std::string fullpath;
    if (pos != std::string::npos)
    {
        fullpath = "../../../ut/src/appareo/utility/filters/" + filename;
    }
    else
    {
        pos = pwd.find("ESW");
        std::string path = pwd.substr(0, pos);
        fullpath = path + "/ESW/ut/src/appareo/utility/filters/" + filename;
    }

    std::cout << filename << std::endl;
    std::cout << "Loading file: " << fullpath << std::endl;

    std::vector<double> data;
    std::ifstream ifs(fullpath);
    cout << "opening file " << filename << std::endl;
    if (ifs.is_open())
    {
        double v;
        while (true)
        {
            ifs >> v;
            if (ifs.eof())
            {
                break;
            }
            data.push_back(v);
        }
    }
    else
    {
        std::cout << "Failed to open file" << std::endl;
    }

    ifs.close();

    return data;
}

TEST(Kalman, TestFilter1)
{
    auto in = loadData("kalman_input1.csv");
    auto out = loadData("kalman_output1.csv");
    std::vector<double> temp(in.size());

    Kalman<double> k(1e-5, 0.1*0.1);

    auto in_it = in.begin();
    auto out_it = out.begin();
    auto temp_it = temp.begin();
    ++in_it;
    ++out_it;
    ++temp_it;
    for (; in_it != in.end(); ++in_it, ++out_it, ++temp_it)
    {
        *temp_it = k.filter(*in_it);
        EXPECT_NEAR(*out_it, *temp_it, 0.0001);
    }

    //EXPECT_NEAR(*out_it, *temp_it, 0.0001);

}

} // namespace Sensors
} // namespace Abercrombie
} // namespace Appareo

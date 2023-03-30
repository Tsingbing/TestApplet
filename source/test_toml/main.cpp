#include "toml11/toml.hpp"
#include "./VehicleFault.h"

#include <filesystem>
#include <iostream>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    if (!std::filesystem::exists("config.toml")) {
        std::cout << "config.toml not exit" << endl;
        return 0;
    }
    
    VehicleFaultToml *vehicleFaultToml = new VehicleFaultToml();

    vehicleFaultToml->parseToml("config.toml");
    vehicleFaultToml->getFaultLevel(1, DriveMode::AUTO);

    delete vehicleFaultToml;

    //  //输出toml所有的[]表头
    //  //  for (auto &i : data) {
    //  //    std::cout << i.key() << endl;
    //  //  }
    //  // const auto title = toml::find<std::string>(data, "title");
    //  // std::cout << "the title is " << title << std::endl;
    return 0;
}

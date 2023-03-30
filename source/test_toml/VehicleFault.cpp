#include "VehicleFault.h"
#include "toml11/toml.hpp"
#include <iostream>
#include <string>
#include <vector>

VehicleFaultToml::VehicleFaultToml(/* args */)
    : _mainCode(0)
    , _faultName("")
    , _faultLevel(0)
{
    std::cout << "VehicleFaultToml" << std::endl;
}

std::string VehicleFaultToml::getFaultName(int main_code)
{
    if (_mainCodeFaultNameMap.find(main_code) != _mainCodeFaultNameMap.end()) {
        std::string fault_name = _mainCodeFaultNameMap[main_code];
        return fault_name;
    } else {
        return "";
    }

    std::cout << "getFaultName" << std::endl;
}

FaultLevel VehicleFaultToml::getFaultLevel(int main_code, DriveMode drive_mode)
{
    //从toml文件中获取fault_level
    const auto data = toml::parse("fault.toml");
    std::string faultName = getFaultName(main_code);

    //如果没有对应的故障名称，返回-1
    if (faultName == "") {
        return FaultLevel::NONE;
    }

    //如果有对应的故障名称，返回故障等级
    const auto aot2 = toml::find<toml::table>(data, faultName);
    FaultLevel faultLevel =  static_cast<FaultLevel>(aot2.at("fault_level").at(static_cast<int>(drive_mode)).as_integer());

    std::cout << "getFaultLevel" << std::endl;
}

AutoRecovery VehicleFaultToml::getAutoRecovery(int main_code)
{
    return AutoRecovery();
}

void VehicleFaultToml::parseToml(const std::string &toml_file)
{
    const auto data = toml::parse(toml_file);
    
    for (auto &i : data.as_table()) {
        std::string faultName = i.first;
        const auto table = toml::find<toml::table>(data, faultName);
        int mainCode = table.at("main_code").as_integer();
        _mainCodeFaultNameMap[mainCode] = faultName;
    }
}

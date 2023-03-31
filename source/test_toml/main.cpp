#include "toml11/toml.hpp"
#include <filesystem>
#include <iostream>
#include <map>
#include <vector>
#ifdef _WIN32
#include <Windows.h>
#endif
using namespace std;
/*
class VehicleFault
{
public:
    VehicleFault(const std::string &filename)
        : filename(filename)
        , fault_level(0)
        , comment("")
        , faultCodeAndName()

    {
        //
        const auto data = toml::parse<toml::preserve_comments>(filename);
        //遍历所有的表
        for (auto &it : data.as_table()) {
            //判断是否是表
            if (!it.second.is_table()) continue;
            //获取表
            const auto &table = it.second.as_table();
            int _maincode = toml::get<int>(table.find("mainCode")->second);
            faultCodeAndName.insert(std::make_pair(_maincode, it.first));
        }
    }

    //输出所有的故障码和故障名
    void printAllFaultCodeAndName()
    {
        for (auto &it : faultCodeAndName) {
            std::stringstream stream;
            stream << std::hex << it.first;
            std::string result(stream.str());
            std::cout << result << ": " << it.second << std::endl;
        }
    }

    //获取故障码对应的故障名
    std::string getFaultName(int faultCode) { return faultCodeAndName.at(faultCode); }

    //获取故障码对应的故障等级
    int getFaultLevel(int faultCode)
    {
        const auto &faultName = faultCodeAndName.at(faultCode);
        const auto &data = toml::parse<toml::preserve_comments>(filename);
        const auto &fault_level1 = toml::find(data, faultName).at("fault_level").at(1).as_integer();
        return fault_level1;
    }

    //获取故障码对应的故障注释
    std::string getFaultComment(int faultCode)
    {
        const auto &faultName = faultCodeAndName.at(faultCode);
        const auto &data = toml::parse<toml::preserve_comments>(filename);
        const auto &comment = toml::find(data, faultName).comments().back();
        return comment;
    }

private:
    std::string filename;                        //文件名
    std::string comment;                         //故障注释
    int fault_level;                             //故障等级
    std::map<int, std::string> faultCodeAndName; //存储maincode和故障名
};

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    std::string filename = "vehicle_fault.toml";

    //判读文件是否存在
    if (std::filesystem::exists(filename)) {
        std::cout << "File exists." << std::endl;
    } else {
        std::cout << "File does not exist." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    VehicleFault *vehicleFault = new VehicleFault(filename);

    vehicleFault->printAllFaultCodeAndName();
    const auto &comment = vehicleFault->getFaultComment(0x340001c5);
    const auto &fault_level = vehicleFault->getFaultLevel(0x340001c5);

    std::cout << comment << ":" << fault_level << std::endl;

    //    const auto aot2 = toml::find<toml::table>(data, "AirFilterBlock_5");

    //    std::cout << aot2.at("fault_level").at(1) << endl;
    //std::cout << toml::find<int>(i, "mainCode") << endl;

    //输出toml所有的[]表头
    //  for (auto &i : data) {
    //    std::cout << i.key() << endl;
    //  }
    // const auto title = toml::find<std::string>(data, "title");
    // std::cout << "the title is " << title << std::endl;

    //编写读取toml文件的函数
    //析构vehicleFault

    delete vehicleFault;
    return 0;
}*/

#include <iostream>
#include <stack>
//#include <toml11/toml.hpp>

using namespace toml;

std::map<std::string, std::string> get_hierarchy_map(const value &v, const std::string &prefix = "")
{
    std::map<std::string, std::string> result;
    switch (v.type()) {
    case value_t::boolean:
        result[prefix] = std::to_string(v.as_boolean());
        break;
    case value_t::integer:
        result[prefix] = std::to_string(v.as_integer());
        break;
    case value_t::floating:
        result[prefix] = std::to_string(v.as_floating());
        break;
    case value_t::string:
        result[prefix] = v.as_string();
        break;
    case value_t::array:
        for (size_t i = 0; i < v.as_array().size(); ++i) {
            const auto &elem = v.as_array().at(i);
            const std::string key = prefix + "[" + std::to_string(i) + "]";
            auto sub_result = get_hierarchy_map(elem, key);
            result.insert(sub_result.begin(), sub_result.end());
        }
        break;
    case value_t::table:
        for (const auto &[key, val] : v.as_table()) {
            const std::string key_prefix = prefix.empty() ? key : prefix + "." + key;
            auto sub_result = get_hierarchy_map(val, key_prefix);
            result.insert(sub_result.begin(), sub_result.end());
        }
        break;
    default:
        break;
    }
    return result;
}

int main()
{
    const std::string filename = "vehicle_fault.toml";
    //判读文件是否存在
    if (std::filesystem::exists(filename)) {
        std::cout << "File exists." << std::endl;
    } else {
        std::cout << "File does not exist." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    const auto data = toml::parse(filename);
    //const auto &data = toml::parse<toml::preserve_comments>(filename);
    auto hierarchy_map = get_hierarchy_map(data);
    for (const auto &[key, value] : hierarchy_map) {
        std::cout << key << ": " << value << std::endl;
    }
    return 0;
}
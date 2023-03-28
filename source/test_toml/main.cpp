#include "toml11/toml.hpp"
//#include <filesystem>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main()
{
    //cout << "Hello World!" << endl;

    //    if (!std::filesystem::exists("vehicle_fault.toml")) {
    //        std::cout << "config.toml not exit" << endl;
    //        return 0;
    //    }

    const auto data = toml::parse<toml::preserve_comments>("vehicle_fault.toml");

    std::map<int, std::string> faultCodeAndName; //存储maincode和故障名

    for (auto &it : data.as_table()) {
        if (!it.second.is_table()) continue;

        const auto &table = it.second.as_table();

        int _maincode = toml::get<int>(table.find("mainCode")->second);

        //const auto &comment = toml::find(data, it.first).comments().back(); //获取注释
        faultCodeAndName.insert(std::make_pair(_maincode, it.first));
    }

    for (auto &it : faultCodeAndName) {
        std::stringstream stream;
        stream << std::hex << it.first;
        std::string result(stream.str());
        std::cout << result << ": " << it.second << std::endl;
    }

    //获取某个字段的注释
    std::string faultName = faultCodeAndName.at(0x340001c5);
    const auto &comment = toml::find(data, faultName).comments().back();
    const auto &fault_level = toml::find(data, faultName).at("fault_level").at(1);
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
    return 0;
}

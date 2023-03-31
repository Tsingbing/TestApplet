#include "toml11/toml.hpp"
#include <iostream>
#include <map>
#include <sstream>
#include <string>

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
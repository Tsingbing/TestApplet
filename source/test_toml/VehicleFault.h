#pragma once

#include <map>
#include <string>
//#auto_recovery 自动驾驶模式故障是否可自行恢复 可恢复/不可恢复 0/1
//#fault_level 数组, 依次代表自动驾驶模式, 人工驾驶模式, 遥控驾驶模式下的故障等级。车载故障分为1~3级，1级为致命。-1代表该驾驶模式不诊断此故障
//#sub_code 数组,每一个字符串代表一个子故障, 每个子故障都标注描述, 子故障的值取用数组的index(1-全F)来代表，0代表默认值
enum class DriveMode {
    AUTO = 0,         //自动驾驶模式
    MANUAL = 1,       //人工驾驶模式
    REMOTECONTROL = 2 //遥控驾驶模式
};

enum class FaultLevel {
    FATAL = 1,   //致命
    SERIOUS = 2, //严重
    MINOR = 3,   //轻微
    NONE = -1    //不诊断
};

enum class AutoRecovery {
    RECOVERABLE = 0,  //可恢复
    UNRECOVERABLE = 1 //不可恢复
};

class VehicleFaultToml
{
public:
    VehicleFaultToml(/* args */);

    void parseToml(const std::string &toml_file);
    std::string getFaultName(int main_code);
    FaultLevel getFaultLevel(int main_code, DriveMode drive_mode);
    AutoRecovery getAutoRecovery(int main_code);
    

private:
    int _mainCode;
    std::string _faultName;
    int _faultLevel;
    //main_code和fault_name的对应关系
    std::map<int, std::string> _mainCodeFaultNameMap;
};

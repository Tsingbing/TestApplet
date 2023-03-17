#include "toml11/toml.hpp"

#include <filesystem>
#include <iostream>

using namespace std;

int main() {
  cout << "Hello World!" << endl;

  if (!std::filesystem::exists("config.toml")) {
    std::cout << "config.toml not exit" << endl;
    return 0;
  }

  //  const auto data = toml::parse("config.toml");
  //  const auto aot2 = toml::find<std::vector<toml::table>>(data, "AID");
  //  std::cout << data << std::endl;

  //  for (auto &i : aot2) {

  //    std::cout << i.at("fault_level").at(1) << endl;
  //    // std::cout << toml::find<int>(i, "mainCode") << endl;
  //  }

  //  //输出toml所有的[]表头
  //  //  for (auto &i : data) {
  //  //    std::cout << i.key() << endl;
  //  //  }
  //  // const auto title = toml::find<std::string>(data, "title");
  //  // std::cout << "the title is " << title << std::endl;
  return 0;
}

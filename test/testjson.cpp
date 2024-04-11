#include "json.hpp"
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <string>
using json = nlohmann::json;
static std::string getStr(){
   json js;
   js["msg_type"] = 1;
   js["from"] = "china";
   js["to"] = "usa";
   js["msg"] = "fuck you";
   auto str = js.dump();
   std::cout << "str:" <<str<<"\n";
   return str;
}
//json序列化
static void func3(){
   json js;
   std::vector<int> vec{};
   for(std::size_t i =0;i<5;i++){
      vec.push_back(i);
   }
   js["list"] = vec;
   std::map<int,std::string> m;
   m.insert(std::make_pair(1,"黄山"));
   m.insert(std::make_pair(2,"华山"));
   m.insert(std::make_pair(3,"泰山"));
   js["path"] = m;
   std::cout  << "js(str):" << js.dump()<< std::endl;
}
//json反序列化:将json字符串转成json对象
static void func4(){
   auto recv_buf = getStr();
   auto jsBuf = json::parse(recv_buf);
   std::cout << jsBuf["msg_type"] <<std::endl;
   std::cout << jsBuf["from"] <<std::endl;
   std::cout << jsBuf["to"] <<std::endl;
   std::cout << jsBuf["msg"] <<std::endl;
}
int main()
{
   func3();
   func4();
}
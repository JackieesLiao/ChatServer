# ChatServer    
This project is developed in VSCode under Windows by remotely connecting to Ubuntu via SSH.    
## Compiler Environment:   
In order to install the following environment, first enter in the terminal.   
```sudo apt update```   
Ubuntu 23.04    
CMake 3.8     
``` 
sudo apt install cmake
```   
g++ 13.10   
``` 
sudo apt install g++
```   
  
## Necessary environment:   
1.MySQL   
``` 
sudo apt install mysql-server mysql-client
```   
2.Redis    
``` 
sudo apt install redis-server
```    
3.Boost   
``` 
sudo apt install libboost-all-dev
```   
4.Muduo    
```
git clone https://github.com/chenshuo/muduo.git
cd muduo && mkdir build && cd build
cmake ..
make
sudo make install
```

5.nlohmann/json     
``` 
mkdir -p ~/json/include
cd ~/json/include
wget https://github.com/nlohmann/json/releases/download/v3.10.4/json.hpp
```


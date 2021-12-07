#pragma once
#include <Windows.h>

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

/*
*   @filename: config.h
*   @brief: 提供从命令行中读入参数, 解析并配置的类
*   @version: 1.0.0
*
*   @author: Fantasime
*
*   @date: 2021/11/30
*   @last update: 2021/12/2
*/



namespace structree {

class Config {
  private:
    std::string::size_type inputFileIndex;
    std::string filename;

    std::vector<std::string> arguments;
    std::vector<std::string> files;

    std::map<std::string, std::vector<std::string>> options;  // option ---> arguments
    std::ifstream inputFile;
    std::ofstream outputFile;

  public:
    Config(int argc, char* argv[]);

    bool hasNextInputfile();

    std::ifstream& loadNextInputfile();

    std::ofstream& getOutputfile();

    const std::string& getFilename();

    static void printUsage();

  private:
    void parseArgus();

    const std::string parseFilename(const std::string& filePath);
};



class FileLoadException : public std::runtime_error {
  public:
    FileLoadException(const char* message);

    FileLoadException(const std::string& message);
};

}  // namespace structree

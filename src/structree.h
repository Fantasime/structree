#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

/*
*   @filename: structree.h
*   @brief: 提供构建树形图的核心类
*
*   @author: Fantasime
*
*   @date: 2021/12/1
*   @last update: 2021/12/3
*/



namespace structree {

class StructreeNode {
  private:
    bool hasNextEquativeNode;  // 是否存在下一个同层节点
    std::string::size_type level;
    std::string content;

  public:
    StructreeNode(std::string::size_type level, const std::string& content);

    StructreeNode(const StructreeNode& node);

    void setNextEqual(bool status);

    const std::string::size_type getLevel();

    const std::string& getContent();

    const bool getHasNextEqual();
};

class StructreeBuilder {
  private:
    char levelTagChar;                 // 层级标记字符 默认为'#'
    char trunkChar;                    // 树干字符 默认为为'|'
    char nodeChar;                     // 节点字符 默认为'+'
    char branchChar;                   // 分支字符 默认为'-'
    std::string prefixPrinter;         // 存储需要打印的trunk和空格前缀
    std::vector<StructreeNode> nodes;  // 存储处理后的输入流中的节点

  public:
    StructreeBuilder();

    void build(const std::string& treeName, std::istream& input, std::ostream& output);

  private:
    std::string::size_type getHalfStringLength(const std::string& str);

    bool allOfLevelTagChar(const std::string& str);

    bool addToNodes(std::string& str);

    void trim();
};

}  // namespace structree
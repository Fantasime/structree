#include <structree.h>



/*
*   @function: StructreeNode constructor
*   @brief: 类StructreeNode的构造函数
*
*   @author: Fantasime
*
*   @date: 2021/12/3
*   @last update: 2021/12/3
*/
structree::StructreeNode::StructreeNode(std::string::size_type level, const std::string& content) :
    hasNextEquativeNode(true) {
    this->level = level;
    this->content = content;
}

structree::StructreeNode::StructreeNode(const structree::StructreeNode& node) {
    this->hasNextEquativeNode = node.hasNextEquativeNode;
    this->level = node.level;
    this->content = std::string(node.content);
}

void structree::StructreeNode::setNextEqual(bool status) {
    hasNextEquativeNode = status;
}

const std::string::size_type structree::StructreeNode::getLevel() {
    return level;
}

const std::string& structree::StructreeNode::getContent() {
    return content;
}

const bool structree::StructreeNode::getHasNextEqual() {
    return hasNextEquativeNode;
}



/*
*   @function: StructreeBuilder constructor
*   @brief: 类StructreeBuilder的构造函数
*
*   @author: Fantasime
*
*   @date: 2021/12/2
*   @last update: 2021/12/2
*/
structree::StructreeBuilder::StructreeBuilder() :
    levelTagChar('#'), trunkChar('|'), nodeChar('+'), branchChar('-') {
}



/*
*   @function: build(const string treeName, istream& input, ostream& output): void
*   @brief: 从input流中读入文本后, 构建树形图到输出流
*
*   @author: Fantasime
*
*   @date: 2021/12/2
*   @last update: 2021/12/4
*/
void structree::StructreeBuilder::build(const std::string& treeName, std::istream& input,
                                        std::ostream& output) {
    output << treeName << '\n';
    prefixPrinter.clear();
    prefixPrinter = std::string(getHalfStringLength(treeName), ' ');

    // 将输入流中的字符串处理成结点并保存在nodes中
    std::string inputString;
    nodes.clear();
    while (std::getline(input, inputString)) {
        addToNodes(inputString);
    }

    // 设定各结点的hasNextEquativeNode属性
    trim();

    // 输出
    std::vector<StructreeNode> lastLevelNodes;
    for (auto node : nodes) {
        // 进层
        if (!lastLevelNodes.empty() && node.getLevel() > lastLevelNodes.back().getLevel()) {
            if (lastLevelNodes.back().getHasNextEqual())
                prefixPrinter.push_back(trunkChar);
            else
                prefixPrinter.push_back(' ');
            prefixPrinter.append(1 + getHalfStringLength(lastLevelNodes.back().getContent()), ' ');

            lastLevelNodes.push_back(node);
        }

        // 退层
        else if (!lastLevelNodes.empty() && node.getLevel() < lastLevelNodes.back().getLevel()) {
            lastLevelNodes.pop_back();
            if (!lastLevelNodes.empty())
                prefixPrinter.erase(
                    prefixPrinter.size() -
                    ((size_t)(2) + getHalfStringLength(lastLevelNodes.back().getContent())));

            while (!lastLevelNodes.empty() && node.getLevel() < lastLevelNodes.back().getLevel()) {
                lastLevelNodes.pop_back();
                if (!lastLevelNodes.empty())
                    prefixPrinter.erase(
                        prefixPrinter.size() -
                        ((size_t)(2) + getHalfStringLength(lastLevelNodes.back().getContent())));
            }
        }

        output << prefixPrinter << trunkChar << '\n';
        output << prefixPrinter << nodeChar << branchChar << node.getContent() << '\n';

        if (lastLevelNodes.empty()) {
            lastLevelNodes.push_back(node);
        } else {
            lastLevelNodes.pop_back();
            lastLevelNodes.push_back(node);
        }
    }
}



/*
*   @function: getHalfStringLength(const string: str): string::size_type
*   @brief: 返回输入的字符串的长度一半
*
*   @author: Fantasime
*
*   @date: 2021/12/2
*   @last update: 2021/12/2
*/
std::string::size_type structree::StructreeBuilder::getHalfStringLength(const std::string& str) {
    if (str.empty())
        return 0;
    return (str.size() - 1) / 2;
}



/*
*   @function: allOfLevelTagChar(const string& str): bool
*   @brief: 检查字符串str中的字符是否都是levelTagChar
*
*   @author: Fantasime
*
*   @date: 2021/12/2
*   @last update: 2021/12/2
*/
bool structree::StructreeBuilder::allOfLevelTagChar(const std::string& str) {
    for (auto ch : str) {
        if (ch != levelTagChar)
            return false;
    }
    return true;
}



/*
*   @function: addToNodes(string& str): bool
*   @brief: 对字符串str进行处理, 并添加处理后到nodes中; 如果失败则返回false
*
*   @author: Fantasime
*
*   @date: 2021/12/3
*   @last update: 2021/12/3
*/
bool structree::StructreeBuilder::addToNodes(std::string& str) {
    // 查找第一个空格的位置
    std::string::size_type firstSpacePos = str.find_first_of(' ');
    if (firstSpacePos < 0 || firstSpacePos >= str.size())
        return false;

    // 获取层级标志字符串
    std::string levelTagStr = str.substr(0, firstSpacePos);
    str.erase(0, firstSpacePos);

    // 检查是否含有非层级标志字符
    //     这里没有使用标准库, 而是使用了一个类内自己写的函数判定是因为在同样
    // 的时间复杂度下, 不会因为使用all_of的一元谓词使得levelTagChar成为一个
    // 不可变的属性
    if (!allOfLevelTagChar(levelTagStr))
        return false;
    std::string::size_type level = levelTagStr.size();

    // 删去前缀多余空格
    std::string::size_type firstNotSpacePos = str.find_first_not_of(' ');
    str.erase(0, firstNotSpacePos);

    // 与上一结点层级出现断层时, 使用空内容结点进行填充
    while (!nodes.empty() && level > nodes.back().getLevel() &&
           level - nodes.back().getLevel() > 1) {
        nodes.push_back(StructreeNode(nodes.back().getLevel() + 1, ""));
    }

    // 构造结点
    nodes.push_back(structree::StructreeNode(level, str));

    return true;
}



/*
*   @function: trim(): void
*   @brief: 根据前后结点的关系对结点的hasNextEquativeLevel属性进行处理
*
*   @author: Fantasime
*
*   @date: 2021/12/4
*   @last update: 2021/12/4
*/
void structree::StructreeBuilder::trim() {
    std::string::size_type minLevel = SIZE_MAX;
    std::map<std::string::size_type, bool> vis;
    for (auto node = nodes.rbegin(); node != nodes.rend(); ++node) {
        if (node->getLevel() < minLevel) {
            minLevel = node->getLevel();
            vis.clear();
            node->setNextEqual(false);
        } else if (node->getLevel() == minLevel) {
            vis.clear();
        } else if (node->getLevel() > minLevel && !vis[node->getLevel()]) {
            node->setNextEqual(false);
            vis[node->getLevel()] = true;
        }
    }
}
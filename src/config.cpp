#include <config.h>


/*
*   @function: Config
*   @brief: Config类的构造函数
*
*   @author: Fantasime
*
*   @date: 2021/12/1
*   @last update: 2021/12/1
*/
structree::Config::Config(int argc, char* argv[]) : inputFileIndex(0) {
    for (size_t i = 1; i < argc; i++) {
        arguments.push_back(argv[i]);
    }

    parseArgus();
}



/*
*   @function: printUsage(): void
*   @brief: 显示用法
*
*   @author: Fantasime
*   
*   @date: 2021/11/30
*   @last update: 2021/12/2
*/
void structree::Config::printUsage() {
    std::cout << "Usage:\n";
    std::cout << "  structree [options] files...\n";
    std::cout << "Options:\n";
    std::cout << "  -h          Show usage" << std::endl;
    // std::cout << "  -o <path>   Set file output path" << std::endl;
}



/*
*   @function: hasNextInputfile(): bool
*   @brief: 检测是否存在下一个输入文件
*
*   @author: Fantasime
*
*   @date:2021/12/1
*   @last update: 2021/12/1
*/
bool structree::Config::hasNextInputfile() {
    return inputFileIndex < files.size();
}



/*
*   @function: loadNextInputfile(): ifstream&
*   @brief: 返回下一个输入文件的引用
*
*   @author: Fantasime
*
*   @date:2021/12/1
*   @last update: 2021/12/2
*/

//   WARNING!!!!!
//   在使用Config实例中getOutputfile函数和getFilename函数
//   之前必须调用该方法装载一个输出文件

std::ifstream& structree::Config::loadNextInputfile() {
    if (!hasNextInputfile())
        throw std::runtime_error((std::string)(__func__) + ": No input files.");

    inputFile.close();
    outputFile.close();

    inputFile.open(files[inputFileIndex], std::ifstream::in);
    outputFile.open(files[inputFileIndex] + ".structree", std::ofstream::out);
    filename = parseFilename(files[inputFileIndex]);
    inputFileIndex++;

    if (!inputFile) {
        throw FileLoadException((std::string)("Can not open the file: ") + filename);
    }

    return inputFile;
}



/*
*   @function: getOutputfile(): ofstream&
*   @brief: 返回输入文件对应的输出文件
*
*   @author: Fantasime
*
*   @date:2021/12/1
*   @last update: 2021/12/1
*/
std::ofstream& structree::Config::getOutputfile() {
    if (!outputFile)
        throw std::runtime_error(std::string(__func__) + ": Property outputFile not initialized");
    return outputFile;
}


/*
*   @function: getFilename(): const string
*   @brief: 返回输入文件对应的文件名
*
*   @author: Fantasime
*
*   @date:2021/12/2
*   @last update: 2021/12/2
*/
const std::string& structree::Config::getFilename() {
    return filename;
}



/*
*   @function: parseArgus(): void
*   @brief: 解析参数并生成配置
*   
*   @author: Fantasime
*
*   @date: 2021/12/1
*   @last update: 2021/12/2
*/
void structree::Config::parseArgus() {
    if (arguments.empty()) {
        std::cout << "\033[31mNo input files!\033[37m" << std::endl;
        Config::printUsage();
        exit(0);
    }

    size_t argc = arguments.size();
    for (size_t i = 0; i < argc; i++) {
        if (arguments[i] == "-h") {
            Config::printUsage();
            exit(0);
        } else if (arguments[i][0] == '-') {
            std::cout << "\033[31mIgnore unspecified options: " << arguments[i] << "\033[37m" << std::endl;
        } else {
            files.push_back(arguments[i]);
        }
    }
}



/*
*   @function: parseFilename(const string& filePath): const string
*   @brief: 解析文件路径, 返回文件名
*   
*   @author: Fantasime
*
*   @date: 2021/12/1
*   @last update: 2021/12/2
*/
const std::string structree::Config::parseFilename(const std::string& filePath) {
    std::string::size_type pos;
#ifdef _WIN32
    pos = filePath.find_last_of('\\');
#else
    pos = filePath.find_last_of('/');
#endif
    if (pos + 1 >= filePath.size()) {
        return filePath;
    } else {
        return filePath.substr(pos + 1);
    }
}



/*
*   @function: FileLoadException
*   @brief: 文件加载异常的构造函数
*   
*   @author: Fantasime
*
*   @date: 2021/12/7
*   @last update: 2021/12/7
*/
structree::FileLoadException::FileLoadException(const char* message) : runtime_error(message) {
}

structree::FileLoadException::FileLoadException(const std::string& message) : runtime_error(message) {
}
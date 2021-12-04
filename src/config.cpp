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
    std::string currentOption = "-f";
    for (size_t i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            currentOption = argv[i];
            options[currentOption];  // add currentOption to map options
        } else {
            options[currentOption].push_back(argv[i]);
        }
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
    std::cout << "  structree file... [options]\n";
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
    return inputFileIndex < options["-f"].size();
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
    inputFile.open(options["-f"][inputFileIndex], std::ifstream::in);
    outputFile.open(options["-f"][inputFileIndex] + ".structree", std::ofstream::out);
    filename = parseFilename(options["-f"][inputFileIndex]);

    // // Set outputfile
    // if (outputPath.empty())
    //     outputFile.open(options["-f"][inputFileIndex] + ".out", std::ofstream::out);

    inputFileIndex++;

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
    if (options.find("-h") != options.end()) {
        Config::printUsage();
        exit(0);
    }

    if (options.find("-f") == options.end()) {
        std::cout << "No input file" << std::endl;
        Config::printUsage();
        exit(0);
    }

    // Check input files
    for (const auto& args : options["-f"]) {
        inputFile.open(args, std::ifstream::in);
        if (!inputFile) {
            std::cout << "Can not open the file: " << args << std::endl;
            exit(0);
        }
        inputFile.close();
    }

    // if (options.find("-o") != options.end()) {
    //     if (options["-o"].size() > 1) {
    //         std::cout << "Too many arguments for option '-o'" << std::endl;
    //         exit(0);
    //     } else {
    //         outputPath = options["-o"][0];
    //     }
    // }
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

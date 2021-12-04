#include <config.h>
#include <structree.h>

int main(int argc, char* argv[]) {
    std::unique_ptr<structree::Config> config = std::make_unique<structree::Config>(argc, argv);
    std::unique_ptr<structree::StructreeBuilder> structreeBuilder =
        std::make_unique<structree::StructreeBuilder>();

    try {
        while (config->hasNextInputfile()) {
            std::ifstream& inputFile = config->loadNextInputfile();
            std::ofstream& outputFile = config->getOutputfile();
            structreeBuilder->build(config->getFilename(), inputFile, outputFile);
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
#include <config.h>
#include <structree.h>

#include <memory>

int main(int argc, char* argv[]) {
    std::unique_ptr<structree::Config> config = std::make_unique<structree::Config>(argc, argv);
    std::unique_ptr<structree::StructreeBuilder> structreeBuilder = std::make_unique<structree::StructreeBuilder>();

    while (config->hasNextInputfile()) {
        try {
            std::ifstream& inputFile = config->loadNextInputfile();
            std::ofstream& outputFile = config->getOutputfile();
            structreeBuilder->build(config->getFilename(), inputFile, outputFile);
            std::clog << config->getFilename() << " --> " << config->getFilename() << ".strutree" << std::endl;
        } catch (const structree::FileLoadException e) {
            std::cerr << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    return 0;
}
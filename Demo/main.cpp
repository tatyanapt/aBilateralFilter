#include "aBilateralFilter.h"
#include <aImage.h>
#include <aInputOutput.h>

void showUsageMessage() {
    std::cout << "Given parameters are wrong" << std::endl;
    std::cout << "Expected: " 
              << "<input filename> <output filename> "
              << "<size x> <size y> <depth> "
              << "<sigmaIntensity> <sigmaSpace>" 
              << std::endl;
    std::cout << "Depth must be 8 or 16, "
              << "because currently only unsigned 8-bit and unsigned 16-bit images are supported in this demo." << std::endl;
    exit(0);
}

void convert8bit(char* inputFileName, char* outputFileName, size_t sizeX, size_t sizeY, 
                 double sigmaD, double sigmaR) {
    aInputOutput<unsigned char> inputOutput;
    aImage<unsigned char> inputImage(sizeX, sizeY, 1);
    aImage<unsigned char> outputImage(sizeX, sizeY, 1);

    inputOutput.readRaw(inputFileName, inputImage);

    aBilateralFilter<unsigned char> filter(sigmaD, sigmaR);
    filter.make(inputImage, outputImage);
    inputOutput.writeRaw(outputFileName, outputImage);
}

void convert16bit(char* inputFileName, char* outputFileName, size_t sizeX, size_t sizeY, 
                 double sigmaD, double sigmaR) {
    aInputOutput<unsigned short> inputOutput;
    aImage<unsigned short> inputImage(sizeX, sizeY, 1);
    aImage<unsigned short> outputImage(sizeX, sizeY, 1);

    inputOutput.readRaw(inputFileName, inputImage);

    aBilateralFilter<unsigned short> filter(sigmaD, sigmaR);
    filter.make(inputImage, outputImage);
    inputOutput.writeRaw(outputFileName, outputImage);
}

int main (int argc, char ** argv) {	
    if (argc != 8) {
        showUsageMessage();
    } 

    char* inputFileName = argv[1];
    char* outputFileName = argv[2];

    size_t sizeX = atoi(argv[3]);
    size_t sizeY = atoi(argv[4]);

    int depth = atoi(argv[5]);
    if (depth != 8 && depth != 16)
        showUsageMessage();

    double sigmaD = atoi(argv[6]);
    double sigmaR = atoi(argv[7]);

    if (depth == 8)
        convert8bit(inputFileName, outputFileName, sizeX, sizeY, sigmaD, sigmaR);
    else
        convert16bit(inputFileName, outputFileName, sizeX, sizeY, sigmaD, sigmaR);

    return 0;
}
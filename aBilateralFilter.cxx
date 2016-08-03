#include "aBilateralFilter.h"
#include <assert.h>
#include <math.h>

template<class T>
double aBilateralFilter<T>::gauss(double sigma, size_t x, size_t y) const {
     return exp(-((x * x + y * y) * 1.0 / (2 * sigma * sigma)));
}

template<class T>
double aBilateralFilter<T>::getSpatialWeight(int i, int j, int x, int y) const {
    return mKernelD[i - x + mKernelRadius][j - y + mKernelRadius];
}

template<class T>
double aBilateralFilter<T>::getSimilarity(T firstIntensity, T secondIntensity) const {
    return mGaussSimilarity[abs((int)firstIntensity - (int)secondIntensity)];
}

template<class T>
T aBilateralFilter<T>::getNewIntensity(aImage<T>& inputImage, size_t x, size_t y) const {
    double newColor = 0;
    double normalizingDivisor = 0;
    T centerIntensity = inputImage.elem(x, y, 0);

    for (int i = x - mKernelRadius; i < x + mKernelRadius; ++i) {
        for (int j = y - mKernelRadius; j < y + mKernelRadius; ++j) {
            if (i >= 0 && j >=0 && i < inputImage.getSizeX() && j < inputImage.getSizeY()) {
                T intensity = inputImage.elem(i, j, 0);
                double weight = getSpatialWeight(i, j, x, y) * getSimilarity(intensity, centerIntensity);
                normalizingDivisor += weight;
                newColor += weight * intensity;
            }
        }
    }

    return T(newColor / normalizingDivisor);
}

template<class T>
aBilateralFilter<T>::aBilateralFilter(double sigmaD, double sigmaR) {
    double sigmaMax = std::max(sigmaD, sigmaR);
    mKernelRadius = 2 * sigmaMax;
    
    int kernelSize = mKernelRadius * 2 + 1;
    mKernelD.resize(kernelSize);
    for (size_t x = 0; x < kernelSize; ++x) {
        mKernelD[x].resize(kernelSize);
        for (size_t y = 0; y < kernelSize; ++y) {
            mKernelD[x][y] = this->gauss(sigmaD, x, y);
        }
    }

    mGaussSimilarity.resize(1 << 16);
    double twoSigmaRSquared = 2 * sigmaR * sigmaR;
    for (size_t i = 0; i < (1 << 16); ++i) {
        mGaussSimilarity[i] = exp(-(i * 1.0 / twoSigmaRSquared));
    }
}

template<class T>
void aBilateralFilter<T>::make(aImage<T>& inputImage, aImage<T>& outputImage) const { 
    size_t sizeX = inputImage.getSizeX();
    size_t sizeY = inputImage.getSizeY();
    size_t sizeZ = inputImage.getSizeZ();
    assert(sizeX > 0 && sizeY > 0 && sizeZ == 1);

    outputImage.resize(sizeY, sizeY, sizeZ);

    for (size_t x = 0; x < sizeX; ++x) {
        for (size_t y = 0; y < sizeY; ++y) {
            outputImage.elem(x, y, 0) = getNewIntensity(inputImage, x, y);
        }
    }
}

template class aBilateralFilter<char>;
template class aBilateralFilter<int>;
template class aBilateralFilter<short>;
template class aBilateralFilter<unsigned char>;
template class aBilateralFilter<unsigned int>;
template class aBilateralFilter<unsigned short>;

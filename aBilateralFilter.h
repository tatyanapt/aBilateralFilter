#ifndef A_BILATERAL_FILTER_H_
#define A_BILATERAL_FILTER_H_

#include <aImage.h>
#include <vector>

template<class T>
class aBilateralFilter {
private:
    double mKernelRadius;
    std::vector<double> mGaussSimilarity;
    std::vector< std::vector<double> > mKernelD;

private:
    double gauss(double sigma, size_t x, size_t y) const;
    double getSpatialWeight(int i, int j, int x, int y) const;
    double getSimilarity(T firstIntensity, T secondIntensity) const;
    T getNewIntensity(aImage<T>& inputImage, size_t x, size_t y) const;
    
public:
    aBilateralFilter(double sigmaD, double sigmaR);
    void make(aImage<T>& inputImage, aImage<T>& outputImage) const;
};

#endif
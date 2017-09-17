#include <itkImageRegionConstIterator.h>
#include <itkRandomImageSource.h>

#include "rtkTestConfiguration.h"
#include "rtkDeconstructSoftThresholdReconstructImageFilter.h"
#include "rtkMacro.h"

template<class TImage>
#if FAST_TESTS_NO_CHECKS
void CheckImageQuality(typename TImage::Pointer itkNotUsed(recon), typename TImage::Pointer itkNotUsed(ref))
{
}
#else
void CheckImageQuality(typename TImage::Pointer recon, typename TImage::Pointer ref)
{
  typedef itk::ImageRegionConstIterator<TImage> ImageIteratorType;
  ImageIteratorType itTest( recon, recon->GetBufferedRegion() );
  ImageIteratorType itRef( ref, ref->GetBufferedRegion() );

  typedef double ErrorType;
  ErrorType TestError = 0.;
  ErrorType EnerError = 0.;

  itTest.GoToBegin();
  itRef.GoToBegin();

  while( !itRef.IsAtEnd() )
    {
    typename TImage::PixelType TestVal = itTest.Get();
    typename TImage::PixelType RefVal = itRef.Get();
    TestError += vcl_abs(RefVal - TestVal);
    EnerError += vcl_pow(ErrorType(RefVal - TestVal), 2.);
    ++itTest;
    ++itRef;
    }
  // Error per Pixel
  ErrorType ErrorPerPixel = TestError/ref->GetBufferedRegion().GetNumberOfPixels();
  std::cout << "\nError per Pixel = " << ErrorPerPixel << std::endl;
  // MSE
  ErrorType MSE = EnerError/ref->GetBufferedRegion().GetNumberOfPixels();
  std::cout << "MSE = " << MSE << std::endl;
  // PSNR
  ErrorType PSNR = 20*log10(2.0) - 10*log10(MSE);
  std::cout << "PSNR = " << PSNR << "dB" << std::endl;
  // QI
  ErrorType QI = (2.0-ErrorPerPixel)/2.0;
  std::cout << "QI = " << QI << std::endl;

  // Checking results
  if (ErrorPerPixel > 0.032)
  {
    std::cerr << "Test Failed, Error per pixel not valid! "
              << ErrorPerPixel << " instead of 0.08" << std::endl;
    exit( EXIT_FAILURE);
  }
  if (PSNR < 28)
  {
    std::cerr << "Test Failed, PSNR not valid! "
              << PSNR << " instead of 23" << std::endl;
    exit( EXIT_FAILURE);
  }
}
#endif

/**
 * \file rtkwaveletstest.cxx
 *
 * \brief Functional test for wavelets deconstruction / reconstruction
 *
 * This test generates a random image, computes its wavelets deconstruction,
 * reconstructs from it, and compares the results to the original image.
 *
 * \author Cyril Mory
 */

int main(int, char** )
{
  typedef float OutputPixelType;
  const unsigned int Dimension = 3;

  typedef itk::Image< OutputPixelType, Dimension >     OutputImageType;
  // Random image sources
  typedef itk::RandomImageSource< OutputImageType > RandomImageSourceType;
  RandomImageSourceType::Pointer randomVolumeSource  = RandomImageSourceType::New();

  // Image meta data
  RandomImageSourceType::PointType origin;
  RandomImageSourceType::SizeType size;
  RandomImageSourceType::SpacingType spacing;

  // Volume metadata
#if FAST_TESTS_NO_CHECKS
  size[0] = 8;
  size[1] = 8;
  size[2] = 8;
  spacing[0] = 32.;
  spacing[1] = 32.;
  spacing[2] = 32.;
#else
  size[0] = 64;
  size[1] = 64;
  size[2] = 64;
  spacing[0] = 4.;
  spacing[1] = 4.;
  spacing[2] = 4.;
#endif
  origin.Fill(0.);
  randomVolumeSource->SetOrigin( origin );
  randomVolumeSource->SetSpacing( spacing );
  randomVolumeSource->SetSize( size );
  randomVolumeSource->SetMin( 0. );
  randomVolumeSource->SetMax( 1. );
  randomVolumeSource->SetNumberOfThreads(2); //With 1, it's deterministic

  // Update the source
  TRY_AND_EXIT_ON_ITK_EXCEPTION( randomVolumeSource->Update() );

  // Wavelets deconstruction and reconstruction
  typedef rtk::DeconstructSoftThresholdReconstructImageFilter
      <OutputImageType>  DeconstructReconstructFilterType;
  DeconstructReconstructFilterType::Pointer wavelets = DeconstructReconstructFilterType::New();
  wavelets->SetInput( randomVolumeSource->GetOutput() );
  wavelets->SetNumberOfLevels( 3 );
  wavelets->SetOrder( 3 );
  wavelets->SetThreshold( 0 );
  TRY_AND_EXIT_ON_ITK_EXCEPTION( wavelets->Update() );

  CheckImageQuality<OutputImageType>(wavelets->GetOutput(), randomVolumeSource->GetOutput());

  std::cout << "\n\nTest PASSED! " << std::endl;

  return EXIT_SUCCESS;
}

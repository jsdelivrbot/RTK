/*=========================================================================
 *
 *  Copyright RTK Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef rtkCudaConjugateGradientImageFilter_4f_h
#define rtkCudaConjugateGradientImageFilter_4f_h

#include "rtkConfiguration.h"
//Conditional definition of the class to pass ITKHeaderTest
#ifdef RTK_USE_CUDA

#include "rtkConjugateGradientImageFilter.h"
#include <itkCudaImageToImageFilter.h>
#include "rtkWin32Header.h"

namespace rtk
{

/** \class CudaConjugateGradientImageFilter_4f
 * \brief A 4D float conjugate gradient image filter on GPU.
 *
 *
 *
 * \author Cyril Mory
 *
 * \ingroup CudaImageToImageFilter
 */

  class ITK_EXPORT CudaConjugateGradientImageFilter_4f :
        public itk::CudaImageToImageFilter< itk::CudaImage<float,4>, itk::CudaImage<float,4>,
    ConjugateGradientImageFilter< itk::CudaImage<float,4> > >
{
public:
  /** Standard class typedefs. */
  typedef rtk::CudaConjugateGradientImageFilter_4f                    Self;
  typedef itk::CudaImage<float,4>                                     OutputImageType;
  typedef rtk::ConjugateGradientImageFilter< OutputImageType >        Superclass;
  typedef itk::SmartPointer<Self>                                     Pointer;
  typedef itk::SmartPointer<const Self>                               ConstPointer;

  /** Standard New method. */
  itkNewMacro(Self)

  /** Runtime information support. */
  itkTypeMacro(CudaConjugateGradientImageFilter_4f, ConjugateGradientImageFilter)

protected:
  rtkcuda_EXPORT CudaConjugateGradientImageFilter_4f();
  ~CudaConjugateGradientImageFilter_4f(){
  }

  virtual void GPUGenerateData();

private:
  CudaConjugateGradientImageFilter_4f(const Self&); //purposely not implemented
  void operator=(const Self&);         //purposely not implemented

}; // end of class

} // end namespace rtk

#endif //end conditional definition of the class

#endif

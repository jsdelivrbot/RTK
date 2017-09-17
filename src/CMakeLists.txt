set(RTK_SRCS
  rtkConditionalMedianImageFilter.cxx
  rtkConvertEllipsoidToQuadricParametersFunction.cxx
  rtkDCMImagXImageIO.cxx
  rtkDCMImagXImageIOFactory.cxx
  rtkEdfImageIO.cxx
  rtkEdfImageIOFactory.cxx
  rtkGeometricPhantomFileReader.cxx
  rtkGlobalTimer.cxx
  rtkGlobalTimerProbesCollector.cxx
  rtkHisImageIO.cxx
  rtkHisImageIOFactory.cxx
  rtkHndImageIO.cxx
  rtkHndImageIOFactory.cxx
  rtkImagXImageIO.cxx
  rtkImagXImageIOFactory.cxx
  rtkImagXXMLFileReader.cxx
  rtkIOFactories.cxx
  rtkThreeDCircularProjectionGeometry.cxx
  rtkThreeDCircularProjectionGeometryXMLFile.cxx
  rtkTimeProbesCollectorBase.cxx
  rtkVarianObiXMLFileReader.cxx
  rtkWatcherForTimer.cxx
  rtkXimImageIO.cxx
  rtkXimImageIOFactory.cxx
  rtkXRadImageIO.cxx
  rtkXRadImageIOFactory.cxx
  )

#=========================================================
# CUDA library
#=========================================================
if (RTK_USE_CUDA)
  set(RTK_CUDA_FILES
    rtkCudaBackProjectionImageFilter.cu
	rtkCudaConstantVolumeSeriesSource.cu
	rtkCudaConstantVolumeSource.cu
	rtkCudaCropImageFilter.cu
	rtkCudaCyclicDeformationImageFilter.cu
	rtkCudaDisplacedDetectorImageFilter.cu
	rtkCudaFDKBackProjectionImageFilter.cu
	rtkCudaFDKWeightProjectionFilter.cu
	rtkCudaFFTConvolutionImageFilter.cu
	rtkCudaForwardProjectionImageFilter.cu
	rtkCudaInterpolateImageFilter.cu
	rtkCudaParkerShortScanImageFilter.cu
	rtkCudaRayCastBackProjectionImageFilter.cu
	rtkCudaSplatImageFilter.cu
	rtkCudaUtilities.cu
    )

  set(CUDA_PROPAGATE_HOST_FLAGS ON)
  set(CUDA_USE_STATIC_CUDA_RUNTIME OFF)#WARNING: mandatory for defining runtime type \MT vs \MD
  CUDA_COMPILE(RTK_CUDA_WRAPPERS ${RTK_CUDA_FILES})

  set(RTK_SRCS ${RTK_SRCS}
	rtkCudaBackProjectionImageFilter.cxx
	rtkCudaConstantVolumeSeriesSource.cxx
	rtkCudaConstantVolumeSource.cxx
	rtkCudaCropImageFilter.cxx
	rtkCudaCyclicDeformationImageFilter.cxx
	rtkCudaDisplacedDetectorImageFilter.cxx
	rtkCudaFDKBackProjectionImageFilter.cxx
	rtkCudaFDKConeBeamReconstructionFilter.cxx
	rtkCudaFDKWeightProjectionFilter.cxx
	rtkCudaInterpolateImageFilter.cxx
	rtkCudaIterativeFDKConeBeamReconstructionFilter.cxx
	rtkCudaParkerShortScanImageFilter.cxx
	rtkCudaRayCastBackProjectionImageFilter.cxx
	rtkCudaSplatImageFilter.cxx
    ${RTK_CUDA_WRAPPERS}
    ${RTK_CUDA_FILES})
endif ()
#=========================================================

add_library(RTK ${RTK_SRCS})
target_link_libraries(RTK LINK_PUBLIC lpsolve55)

if (RTK_USE_CUDA)
  target_link_libraries( RTK LINK_PUBLIC ${CUDA_LIBRARIES} ${CUDA_cufft_LIBRARY} ${CUDA_CUBLAS_LIBRARIES} )
endif ()

itk_module_link_dependencies()
itk_module_target(RTK)
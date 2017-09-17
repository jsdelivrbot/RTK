set(DOCUMENTATION "")

set(RTK_IO_DEPENDS
  ITKIOBioRad
  ITKIOBMP
  ITKIOCSV
  ITKIOGDCM
  ITKIOGE
  ITKIOGIPL
  ITKIOHDF5
  ITKIOImageBase
  ITKIOJPEG
  ITKIOLSM
  ITKIOMeta
  ITKIOMINC
  ITKIOMRC
  ITKIONIFTI
  ITKIONRRD
  ITKIOPNG
  ITKIORAW
  ITKIOStimulate
  ITKIOTIFF
  ITKIOVTK
  ITKIOXML
  )

set(RTK_DEPENDS
  ITKCommon
  ITKConvolution #rtkamsterdamshroud.exe
  ITKFFT
  ITKImageIntensity
  ITKSmoothing   #rtkamsterdamshroud.exe
  ITKThresholding
  ITKTransform
  ITKVNL
  ${RTK_IO_DEPENDS}
  )

#=========================================================
# CUDA optional dependencies
#=========================================================
if(${RTK_USE_CUDA})
  list(APPEND RTK_DEPENDS ITKCudaCommon)
endif()

#=========================================================
# Module RTK
#=========================================================
itk_module(RTK
  EXCLUDE_FROM_DEFAULT
  DEPENDS
    ${RTK_DEPENDS}
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
  )
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/rtkTestConfiguration.h.in
  ${RTK_BINARY_DIR}/rtkTestConfiguration.h)
#-----------------------------------------------------------------------------
# The subdirectories added below this line should use only the public
# interface with find_package(ITK). Set ITK_DIR to use this ITK build.
if(ITK_SOURCE_DIR)
  set(ITK_DIR "${ITK_BINARY_DIR}")
endif()
#-----------------------------------------------------------------------------
# Find ITK.
# Required to include ITK_USE_FILE in order to Register IO factories in rtkcheckimagequality
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

itk_module_test()

set(RTK-tests
  rtkAdjointOperatorsTest.cxx )

CreateTestDriver(RTK "${RTK-Test_LIBRARIES}" "${RTK-tests}")

# Executable to check the image quality
add_executable(rtkcheckimagequality rtkcheckimagequality.cxx)
target_link_libraries(rtkcheckimagequality ${RTK_LIBRARIES})

if(${RTK_USE_CUDA} AND ${CUDA_HAVE_GPU})
  itk_add_test(NAME rtkAdjointOperatorsCudaTest
  COMMAND RTKTestDriver
  rtkAdjointOperatorsTest )
else()
  itk_add_test(NAME rtkAdjointOperatorsTest
  COMMAND RTKTestDriver
  rtkAdjointOperatorsTest )
endif()

add_executable(rtkfdktest rtkfdktest.cxx)
target_link_libraries( rtkfdktest ${RTK_LIBRARIES})
if(${RTK_USE_CUDA} AND ${CUDA_HAVE_GPU})
  itk_add_test(NAME  rtkFDKCudaTest
    COMMAND  itkTestDriver
    $<TARGET_FILE:rtkfdktest>)
else()
  itk_add_test(NAME  rtkFDKTest
    COMMAND  itkTestDriver
    $<TARGET_FILE:rtkfdktest>)
endif()

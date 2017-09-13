find_package(Gengetopt)

#-----------------------------------------------------------------------------
# Common revision info between applications
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
if(GIT_SHA1 MATCHES ".*NOTFOUND") 
  set(RTK_VERSION_HASH "")
else()
  set(RTK_VERSION_HASH ", git hash ${GIT_SHA1}")
endif()
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/rtkVersion.ggo.in ${RTK_BINARY_DIR}/rtkVersion.ggo)

#-----------------------------------------------------------------------------
# Setup RPATH :
#
# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# add path to RTK libraries to the install path
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${RTK_INSTALL_LIB_DIR}")

#-----------------------------------------------------------------------------
# Find ITK. 
# Required to include ITK_USE_FILE in order to Register IO factories
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

#-----------------------------------------------------------------------------
# Executables
add_subdirectory(rtkamsterdamshroud)
add_subdirectory(rtkbackprojections)
add_subdirectory(rtkfdk)
add_subdirectory(rtkfdktwodweights)
add_subdirectory(rtkfieldofview)
add_subdirectory(rtkforwardprojections)
add_subdirectory(rtkfourdfdk)
add_subdirectory(rtkfourdsart)
add_subdirectory(rtkinlinefdk)
add_subdirectory(rtkiterativefdk)
add_subdirectory(rtkparkershortscanweighting)
add_subdirectory(rtkprojectgeometricphantom)
add_subdirectory(rtkprojections)
add_subdirectory(rtkprojectshepploganphantom)
add_subdirectory(rtkramp)
add_subdirectory(rtkrayboxintersection)
add_subdirectory(rtkrayquadricintersection)
add_subdirectory(rtksart)
add_subdirectory(rtksimulatedgeometry)
add_subdirectory(rtksubselect)
add_subdirectory(rtkwangdisplaceddetectorweighting)

#-----------------------------------------------------------------------------
# Testing of the applications
if(BUILD_TESTING)

  add_test(rtkappsimulatedgeometrytest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/rtksimulatedgeometry -n 180 --sid 1000 --sdd 1500 -o geo)

  add_test(rtkappprojectshepploganphantomtest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/rtkprojectshepploganphantom  -o sheppy.mha -g geo --phantomscale 40 --dimension 128)
  set_tests_properties(rtkappprojectshepploganphantomtest PROPERTIES DEPENDS rtkappsimulatedgeometrytest)
 
  if(RTK_USE_CUDA AND CUDA_HAVE_GPU)
    add_test(rtkappfdkcudatest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/rtkfdk -g geo -p . -r sheppy.mha -o fdk_gpu.mha --hardware cuda)
	set_tests_properties(rtkappfdkcudatest PROPERTIES DEPENDS rtkappprojectshepploganphantomtest)
    
	add_test(rtkappfdkchecktest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/rtkcheckimagequality fdk_gpu.mha)
    set_tests_properties(rtkappfdkchecktest PROPERTIES DEPENDS rtkappfdkcudatest)
  else()
    # Only run the software version if 
    if(NOT FAST_TESTS_NO_CHECKS)
      add_test(rtkappfdktest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/rtkfdk -g geo -p . -r sheppy.mha -o fdk_gpu.mha)
	  set_tests_properties(rtkappfdktest PROPERTIES DEPENDS rtkappprojectshepploganphantomtest)
      
	  add_test(rtkappfdkchecktest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/rtkcheckimagequality fdk_gpu.mha)
      set_tests_properties(rtkappfdkchecktest PROPERTIES DEPENDS rtkappfdktest)
	endif()
  endif()
 
endif()

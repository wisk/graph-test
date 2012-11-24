# FindOGDF.cmake
# Only compatible with Windows and Visual Studio
# (tested on w7sp1amd64 / vs2012)

mark_as_advanced(OGDF_ROOT)
mark_as_advanced(OGDF_INCLUDE_DIRS)
mark_as_advanced(OGDF_LIBRARIES)
mark_as_advanced(OGDF_LIBRARIES_RELEASE)
mark_as_advanced(OGDF_LIBRARIES_DEBUG)

set(OGDF_FOUND FALSE)

if (NOT OGDF_ROOT)
  set(OGDF_ROOT "$ENV{OGDF_ROOT}")
endif()

if (NOT OGDF_ROOT)
  message("Please, define OGDF_ROOT")
endif()

if (NOT WIN32 OR CYGWIN)
  message("Not yet supported")
endif()

set(OGDF_INCLUDE_DIRS "${OGDF_ROOT}")

set(OGDF_LIB_PREFIX "Win32")
if (CMAKE_CL_64 OR CMAKE_GENERATOR MATCHES Win64)
  set(OGDF_LIB_PREFIX "x64")
endif()

if (CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE)
  set(OGDF_LIBRARIES_RELEASE optimized "${OGDF_ROOT}/${OGDF_LIB_PREFIX}/Release/ogdf.lib")
  set(OGDF_LIBRARIES_DEBUG   debug     "${OGDF_ROOT}/${OGDF_LIB_PREFIX}/Debug/ogdf.lib")
  set(OGDF_LIBRARIES ${OGDF_LIBRARIES_RELEASE} ${OGDF_LIBRARIES_DEBUG})
else()
  set(OGDF_LIBRARIES "${OGDF_ROOT}/${OGDF_LIB_PREFIX}/Release/ogdf.lib")
endif()

list(APPEND OGDF_LIBRARIES "psapi.lib")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  OGDF_DEFAULT_MSG
  OGDF_INCLUDE_DIRS OGDF_LIBRARIES
)

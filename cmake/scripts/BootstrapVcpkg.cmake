include(cmake/autovcpkg/AutoVcpkg.cmake)

set( _VCPKG_ROOT )

if ( "${VCPKG_ROOT}" STREQUAL "" )
    set( _VCPKG_ROOT "$ENV{VCPKG_ROOT}" )
endif()

if (EXISTS ${_VCPKG_ROOT})
    set( AUTO_VCPKG_ROOT ${_VCPKG_ROOT} CACHE STRING "auto vcpkg root directory")
else()
    vcpkg_download() 
    set( _VCPKG_ROOT ${AUTO_VCPKG_ROOT} )
endif()

set( VCPKG_ROOT "${_VCPKG_ROOT}" CACHE STRING "vcpkg root directory")
message( "* VCPKG_ROOT " ${VCPKG_ROOT} )

include( "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" )
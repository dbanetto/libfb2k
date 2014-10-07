# - Try to find UNITTEST++

find_package(PkgConfig)
pkg_check_modules(UNITTEST++ QUIET unittest++)
set(UNITTEST++_DEFINITIONS ${UNITTEST++_CFLAGS_OTHER})

find_path(UNITTEST++_INCLUDE_DIR UnitTest++.h
          HINTS ${UNITTEST++_INCLUDEDIR} ${UNITTEST++_INCLUDE_DIRS})


find_library(UNITTEST++_LIBRARY NAMES unittest++
             HINTS ${UNITTEST++_LIBDIR} ${UNITTEST++_LIBRARY_DIRS} )

set(UNITTEST++_LIBRARIES ${UNITTEST++_LIBRARY} )
set(UNITTEST++_INCLUDE_DIRS ${UNITTEST++_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(UnitTest++  DEFAULT_MSG
                                  UNITTEST++_LIBRARY UNITTEST++_INCLUDE_DIR)

mark_as_advanced(UNITTEST++_INCLUDE_DIR UNITTEST++_LIBRARY )

# - Try to find FB2K

find_package(PkgConfig)
pkg_check_modules(FB2K QUIET tag)
set(FB2K_DEFINITIONS ${FB2K_CFLAGS_OTHER})

find_path(FB2K_INCLUDE_DIR libfb2k/libfb2k.h
          HINTS ${FB2K_INCLUDEDIR} ${FB2K_INCLUDE_DIRS}
          PATH_SUFFIXES fb2k )

find_library(FB2K_LIBRARY NAMES fb2k
             HINTS ${FB2K_LIBDIR} ${FB2K_LIBRARY_DIRS} )

set(FB2K_LIBRARIES ${FB2K_LIBRARY} )
set(FB2K_INCLUDE_DIRS ${FB2K_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(fb2k  DEFAULT_MSG
                                  FB2K_LIBRARY FB2K_INCLUDE_DIR)

mark_as_advanced(FB2K_INCLUDE_DIR FB2K_LIBRARY )

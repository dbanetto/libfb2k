# - Try to find TAG

find_package(PkgConfig)
pkg_check_modules(TAG QUIET tag)
set(TAG_DEFINITIONS ${TAG_CFLAGS_OTHER})

find_path(TAG_INCLUDE_DIR taglib/taglib.h
          HINTS ${TAG_INCLUDEDIR} ${TAG_INCLUDE_DIRS}
          PATH_SUFFIXES tag )

find_library(TAG_LIBRARY NAMES tag
             HINTS ${TAG_LIBDIR} ${TAG_LIBRARY_DIRS} )

set(TAG_LIBRARIES ${TAG_LIBRARY} )
set(TAG_INCLUDE_DIRS ${TAG_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Tag  DEFAULT_MSG
                                  TAG_LIBRARY TAG_INCLUDE_DIR)

mark_as_advanced(TAG_INCLUDE_DIR TAG_LIBRARY )

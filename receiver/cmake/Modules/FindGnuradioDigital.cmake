INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(GNURADIO_DIGITAL gnuradio-digital>=3.7)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GNURADIO_DIGITAL DEFAULT_MSG GNURADIO_DIGITAL_LIBRARIES GNURADIO_DIGITAL_INCLUDE_DIRS)
MARK_AS_ADVANCED(GNURADIO_DIGITAL_LIBRARIES GNURADIO_DIGITAL_INCLUDE_DIRS)

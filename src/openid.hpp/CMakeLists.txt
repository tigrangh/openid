# interface library for headers only module
add_library(openid.hpp INTERFACE)

# modules linking to this library will include following
# directories. two options are provided for installed package
# and for in-tree source build
target_include_directories(openid.hpp INTERFACE
    $<INSTALL_INTERFACE:include/openid.hpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

# libraries this module links to
target_link_libraries(openid.hpp INTERFACE belt.pp)

# what to do on make install
install(TARGETS openid.hpp
        EXPORT openid.package
        DESTINATION ${OPENID_INSTALL_DESTINATION_LIBRARY})

set(SRC_FILES
    global
    server)

install(FILES
    ${SRC_FILES}
    DESTINATION ${OPENID_INSTALL_DESTINATION_INCLUDE}/openid.hpp)

#
# add custom target simply for IDE to show the files
#
add_custom_target(openid.include SOURCES
    ${SRC_FILES})

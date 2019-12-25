# define the executable
add_executable(openidd
    main.cpp)

# libraries this module links to
target_link_libraries(openidd PRIVATE
    socket
    openid.hpp
    openid
    mesh.pp
    systemutility
    belt.pp
    utility
    cryptoutility
    log
    mlog
    Boost::filesystem
    Boost::program_options
    Boost::locale
    )

# what to do on make install
install(TARGETS openidd
        EXPORT openid.package
        RUNTIME DESTINATION ${OPENID_INSTALL_DESTINATION_RUNTIME}
        LIBRARY DESTINATION ${OPENID_INSTALL_DESTINATION_LIBRARY}
        ARCHIVE DESTINATION ${OPENID_INSTALL_DESTINATION_ARCHIVE})

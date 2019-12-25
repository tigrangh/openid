# generate types.gen.hpp from types.idl
add_custom_command (
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/types.gen.hpp
  MAIN_DEPENDENCY types.idl
  COMMAND idl ${CMAKE_CURRENT_SOURCE_DIR}/types.idl ${CMAKE_CURRENT_SOURCE_DIR}/types.gen
)

add_definitions(-DOPENID_LIBRARY)

# define the library
add_library(openid
    global.hpp
    exception.hpp
    exception.cpp
    http.hpp
    server.cpp
    server.hpp
    server_internals.hpp
    types.hpp
    types.gen.hpp)

# libraries this module links to
target_link_libraries(openid
    PUBLIC
        mesh.pp
        belt.pp
        openid.hpp
    PRIVATE
        packet
        utility
        socket
        systemutility
        cryptoutility
        sessionutility
        log)

# what to do on make install
install(TARGETS openid
        EXPORT openid.package
        RUNTIME DESTINATION ${OPENID_INSTALL_DESTINATION_RUNTIME}
        LIBRARY DESTINATION ${OPENID_INSTALL_DESTINATION_LIBRARY}
        ARCHIVE DESTINATION ${OPENID_INSTALL_DESTINATION_ARCHIVE})

install(FILES
    global.hpp
    server.hpp
    DESTINATION ${OPENID_INSTALL_DESTINATION_INCLUDE}/libopenid)

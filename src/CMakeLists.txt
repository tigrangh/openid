if( WIN32 )
    SET(OPENID_INSTALL_DESTINATION_RUNTIME bin)
    SET(OPENID_INSTALL_DESTINATION_LIBRARY lib)
    SET(OPENID_INSTALL_DESTINATION_ARCHIVE lib)
    SET(OPENID_INSTALL_DESTINATION_INCLUDE include)
else( WIN32 )
    SET(OPENID_INSTALL_DESTINATION_RUNTIME bin/openid)
    SET(OPENID_INSTALL_DESTINATION_LIBRARY lib/openid)
    SET(OPENID_INSTALL_DESTINATION_ARCHIVE lib/openid)
    SET(OPENID_INSTALL_DESTINATION_INCLUDE include/openid)
endif( WIN32 )

if( NOT WIN32 )
    # don't skip the full RPATH for the build tree
    SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

    # when building, don't use the install RPATH already
    # (but later on when installing)
    SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

    SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib/openid;${CMAKE_INSTALL_PREFIX}/lib/belt.pp;${CMAKE_INSTALL_PREFIX}/lib/mesh.pp")

    # not sure if there is any use from below command
    # add the automatically determined parts of the RPATH
    # which point to directories outside the build tree to the install RPATH
    #SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()

include(cmake_utility/utility.cmake)

if(NOT TARGET belt.pp)
add_subdirectory(belt.pp)
endif()
if(NOT TARGET mesh.pp)
add_subdirectory(mesh.pp)
endif()

add_subdirectory(openidd)

# following is used for find_package functionality
install(FILES openid-config.cmake DESTINATION ${OPENID_INSTALL_DESTINATION_LIBRARY})
install(EXPORT openid.package NAMESPACE openid:: DESTINATION ${OPENID_INSTALL_DESTINATION_LIBRARY})

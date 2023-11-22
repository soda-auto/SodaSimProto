set(CPACK_PACKAGE_NAME ${FULL_PROJECT_NAME})
set(CPACK_PACKAGE_DESCRIPTION "${PACKAGE_NAME} package with SodaSim types")
set(CPACK_PACKAGE_CONTACT "Soda Simulator team ivan@soda.auto")
set(CPACK_PACKAGE_VENDOR "Soda LTD")
set(CPACK_PACKAGE_VERSION ${FULL_PACKAGE_VERSION})
set(CPACK_STRIP_FILES ON)

set(CPACK_GENERATOR DEB)
set(CPACK_DEB_COMPONENT_INSTALL ON)

set(CPACK_DEBIAN_PACKAGE_SECTION misc)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_PACKAGE_CONFLICTS pplan)
set(CPACK_COMPONENTS_GROUPING IGNORE)

include(CPack)

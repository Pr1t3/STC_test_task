cmake_minimum_required(VERSION 3.16)

project(cities LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(cities-app)
add_subdirectory(cities-core)

set(CPACK_PACKAGE_NAME "stc-task1")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Test task Database Cities Editor")
set(CPACK_PACKAGE_VENDOR "Provatorov Roman")
set(CPACK_PACKAGE_CONTACT "romapro2005@gmail.com")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt5core5a, libqt5gui5, libqt5widgets5, libqt5sql5-sqlite")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
set(CPACK_GENERATOR "DEB")
include(CPack)
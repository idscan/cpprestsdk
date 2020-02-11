function(cpprest_find_zlib)
  if(TARGET cpprestsdk_zlib_internal)
    return()
  endif()

  if (HUNTER_ENABLED)
    hunter_add_package(ZLIB)
    find_package(ZLIB CONFIG REQUIRED)
  else (HUNTER_ENABLED)
  if(APPLE AND NOT IOS)
    # Prefer the homebrew version of zlib
    find_library(ZLIB_LIBRARY NAMES libz.a PATHS /usr/local/Cellar/zlib/1.2.8/lib NO_DEFAULT_PATH)
    find_path(ZLIB_INCLUDE_DIRS NAMES zlib.h PATHS /usr/local/Cellar/zlib/1.2.8/include NO_DEFAULT_PATH)

    if(NOT ZLIB_LIBRARY OR NOT ZLIB_INCLUDE_DIRS)
      find_package(ZLIB REQUIRED)
    endif()
  else()
    find_package(ZLIB REQUIRED)
  endif()
  endif (HUNTER_ENABLED)

  add_library(cpprestsdk_zlib_internal INTERFACE)
  if(TARGET ZLIB::ZLIB)
    target_link_libraries(cpprestsdk_zlib_internal INTERFACE ZLIB::ZLIB)
  else()
    target_link_libraries(cpprestsdk_zlib_internal INTERFACE "$<BUILD_INTERFACE:${ZLIB_LIBRARY}>")
    target_include_directories(cpprestsdk_zlib_internal INTERFACE "$<BUILD_INTERFACE:${ZLIB_INCLUDE_DIRS}>")
  endif()
endfunction()

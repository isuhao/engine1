project(PulseSDK)


file(GLOB SRC_FILES
  "howto/cpp/*.h"
  "howto/cpp/*.cpp"
)
source_group("" FILES ${SRC_FILES})
set(SOURCE ${SRC_FILES})
add_executable(HowToDriver EXCLUDE_FROM_ALL ${SOURCE})

# Preprocessor Definitions and Include Paths
set(FLAGS)
target_include_directories(HowToDriver PRIVATE ${CMAKE_INSTALL_PREFIX}/include)
target_include_directories(HowToDriver PRIVATE ${CMAKE_INSTALL_PREFIX}/include/cdm)
target_include_directories(HowToDriver PRIVATE ${CMAKE_INSTALL_PREFIX}/include/bind)
set_target_properties(HowToDriver PROPERTIES COMPILE_FLAGS "${FLAGS}" PREFIX "")
# Dependent Libraries

set(D_LIB_FILES
  ${CMAKE_INSTALL_PREFIX}/lib/debug${EX_CONFIG}/PulseEngine.lib
  ${CMAKE_INSTALL_PREFIX}/lib/debug${EX_CONFIG}/CommonDataModel.lib
  ${CMAKE_INSTALL_PREFIX}/lib/debug${EX_CONFIG}/DataModelBindings.lib
  ${CMAKE_INSTALL_PREFIX}/lib/debug${EX_CONFIG}/log4cpp.lib
  ${CMAKE_INSTALL_PREFIX}/lib/debug${EX_CONFIG}/libprotobufd.lib
)
set(O_LIB_FILES
  ${CMAKE_INSTALL_PREFIX}/lib/release${EX_CONFIG}/PulseEngine.lib
  ${CMAKE_INSTALL_PREFIX}/lib/release${EX_CONFIG}/CommonDataModel.lib
  ${CMAKE_INSTALL_PREFIX}/lib/release${EX_CONFIG}/DataModelBindings.lib
  ${CMAKE_INSTALL_PREFIX}/lib/release${EX_CONFIG}/log4cpp.lib
  ${CMAKE_INSTALL_PREFIX}/lib/release${EX_CONFIG}/libprotobuf.lib
)


foreach(file ${D_LIB_FILES})
	target_link_libraries(HowToDriver debug ${file})
endforeach()
foreach(file ${O_LIB_FILES})
	target_link_libraries(HowToDriver optimized ${file})
endforeach()

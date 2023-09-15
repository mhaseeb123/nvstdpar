project(choleskey_stdpar LANGUAGES CXX)

add_executable(choleskey_serial choleskey_serial.cpp)
target_include_directories(
  choleskey_serial
  PRIVATE ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_LIST_DIR}/../../include
          ${ARGPARSE_INCLUDE_DIR} ${MDSPAN_INCLUDE_DIR})
          

      



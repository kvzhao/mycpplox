

set(HEADER_LIST
  ../include/scanner.hpp 
  ../include/token.hpp
  ../include/token_type.hpp
  ../include/error.hpp
)

add_library(scanner scanner.cc token.cc ${HEADER_LIST})

target_include_directories(scanner PUBLIC ../include)
set(INTERPRETER_NAME jlox)

add_executable(${INTERPRETER_NAME} Lox.cc)

target_compile_features(${INTERPRETER_NAME} PRIVATE cxx_std_17)

target_link_libraries(${INTERPRETER_NAME} PRIVATE scanner)
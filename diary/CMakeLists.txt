

aux_source_directory(../deps/list/src LIST_SRC1)
MESSAGE(STATUS hello${LIST_SRC1})

add_executable(prime_number codes/prime_number.c)
add_executable(triangular_area codes/triangular_area.c)
add_executable(void_ptr codes/void_ptr.c)
add_executable(list_example codes/list_example.c ${LIST_SRC1} codes/cs.c)

target_link_libraries(triangular_area m)


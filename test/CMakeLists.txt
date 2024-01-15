#/test

add_executable(test_helper test_helper.c ${SOURCE_FILES})
add_executable(test_model test_model.c ${SOURCE_FILES})

enable_testing()
add_test(NAME TestHelper COMMAND test_helper)
add_test(NAME TestModel COMMAND test_model)


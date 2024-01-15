set(SOURCE_FILES
	model.c
	model.h
	socket_helper.c
	socket_helper.h
	)

add_executable(connect main.c ${SOURCE_FILES})


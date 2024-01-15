# /src

set(SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/model.c
	${CMAKE_CURRENT_SOURCE_DIR}/model.h
	${CMAKE_CURRENT_SOURCE_DIR}/socket_helper.c
	${CMAKE_CURRENT_SOURCE_DIR}/socket_helper.h
	)

set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)

add_executable(webserver main.c ${SOURCE_FILES})


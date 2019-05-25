cmake_minimum_required( VERSION 3.0 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )

project( stl_viewer )

get_filename_component( CINDER_PATH "/data/git/Cinder/" ABSOLUTE )
get_filename_component( SRC_PATH "./" ABSOLUTE )
get_filename_component( BLOCK_PATH "/data/git/Cinder/blocks/Cinder-Assimp/src/" ABSOLUTE )

include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )

set( SRC_FILES
	${SRC_PATH}/stl_viewer.cpp
	${BLOCK_PATH}/Actor.cpp
	${BLOCK_PATH}/AnimCurve.cpp
	${BLOCK_PATH}/AssimpLoader.cpp
	${BLOCK_PATH}/ModelIo.cpp
	${BLOCK_PATH}/MorphedMesh.cpp
	${BLOCK_PATH}/Node.cpp
	${BLOCK_PATH}/Renderer.cpp
	${BLOCK_PATH}/Skeleton.cpp
	${BLOCK_PATH}/SkeletalTriMesh.cpp
	${BLOCK_PATH}/SkeletalMesh.cpp
	${BLOCK_PATH}/StaticMesh.cpp
	${BLOCK_PATH}/SurfacePool.cpp
)

set( ADDONS_FILES
	/data/git/cindervrx/addons/
	/data/git/Cinder/blocks/
	/data/git/Cinder/blocks/Cinder-Assimp/
	/data/git/Cinder/blocks/Cinder-Assimp/assimp/include/
	)
	
ci_make_app (
	CINDER_PATH ${CINDER_PATH}
	SOURCES     ${SRC_FILES}
	INCLUDES    ${ADDONS_FILES}
	BLOCKS      Cinder-Assimp
	LIBRARIES   assimp
	#RESOURCES   ${APP_PATH}/../../
	)

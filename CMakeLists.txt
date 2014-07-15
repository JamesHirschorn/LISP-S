#############################################################################
# CMake Build System for LISP-S												#
#																			#
# Copyright (C) 2014 James Hirschorn <James.Hirschorn@gmail.com>			#
#############################################################################

cmake_minimum_required( VERSION 2.8 )

project( LISP_S )
set_property( GLOBAL PROPERTY USE_FOLDERS ON )

#--------------------------------------------------
# initial settings - non-cached

set( LISP_S_ROOT_DIR ${PROJECT_SOURCE_DIR} )

set( LISP_S_PARSER_DIR ${LISP_S_ROOT_DIR}/parser )
set( LISP_S_TREE_DIR ${LISP_S_ROOT_DIR}/tree )
set( LISP_S_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR} )

# Disable compiler depreciation warnings.
#add_definitions( -D_CRT_SECURE_NO_WARNINGS )

#---------------------------------------------------------
# Process headers and source files.

file( GLOB LISP_S_PARSER_HEADERS ${LISP_S_PARSER_DIR}/*.hpp )
file( GLOB LISP_S_TREE_HEADERS ${LISP_S_TREE_DIR}/*.hpp )
file( GLOB LISP_S_SOURCES ${LISP_S_ROOT_DIR}/*.cpp )

source_group( "parser" FILES ${LISP_S_PARSER_HEADERS} )
source_group( "tree" FILES ${LISP_S_TREE_HEADERS} )
source_group( "Source Files" FILES ${LISP_S_SOURCES} )

#---------------------------------------------------------
# Create the library.

include_directories( ${LISP_S_PARSER_HEADERS} ${LISP_S_TREE_HEADERS} )
add_executable( TreeSumming ${LISP_S_SOURCES} ${LISP_S_TREE_HEADERS} ${LISP_S_PARSER_HEADERS} )

#install( TARGETS LISP_S
#		 RUNTIME DESTINATION bin
#		 LIBRARY DESTINATION lib
#		 ARCHIVE DESTINATION lib
#)

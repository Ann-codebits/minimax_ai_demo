cmake_minimum_required(VERSION 3.6)

project(TicTacToe)

add_executable(TicTacToe 
	GameMain.cpp
	Player.h
	TicTacToe.cpp
	TicTacToe.h
	)
	
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT TicTacToe)	

cmake_minimum_required(VERSION 3.8)
project(Server)

set(CMAKE_CXX_STANDARD 98)
set(SOURCE_FILES main.cpp Server.cpp Server.h ClientHandler.cpp ClientHandler.h CommandsManager.cpp CommandsManager.h Command.h StartGameCommand.cpp StartGameCommand.h GameDetails.cpp GameDetails.h GetGamesListCommand.cpp GetGamesListCommand.h JoinGameCommand.cpp JoinGameCommand.h PlayCommand.cpp PlayCommand.h CloseCommand.cpp CloseCommand.h ListOfGames.cpp ListOfGames.h GameManager.cpp GameManager.h)
add_executable(Server ${SOURCE_FILES} Server.cpp Server.h ClientHandler.cpp ClientHandler.h CommandsManager.cpp CommandsManager.h Command.h StartGameCommand.cpp StartGameCommand.h GameDetails.cpp GameDetails.h GetGamesListCommand.cpp GetGamesListCommand.h JoinGameCommand.cpp JoinGameCommand.h PlayCommand.cpp PlayCommand.h CloseCommand.cpp CloseCommand.h ListOfGames.cpp ListOfGames.h GameManager.cpp GameManager.h)

set(CMAKE_CXX_FLAGS -pthread)
cmake_minimum_required(VERSION 3.8)
project(Server)

set(CMAKE_CXX_STANDARD 98)
set(SOURCE_FILES src/main.cpp src/Server.cpp include/Server.h src/ClientHandler.cpp include/ClientHandler.h src/CommandsManager.cpp include/CommandsManager.h include/Command.h src/StartGameCommand.cpp include/StartGameCommand.h src/GameDetails.cpp include/GameDetails.h include/GameManager.h src/GameManager.cpp src/GetGamesListCommand.cpp include/GetGamesListCommand.h src/JoinGameCommand.cpp include/JoinGameCommand.h src/ListOfGames.cpp include/ListOfGames.h src/GameManager.cpp include/GameManager.h include/ThreadPool.h include/Task.h src/ThreadPool.cpp)
add_executable(Server ${SOURCE_FILES} src/Server.cpp include/Server.h src/ClientHandler.cpp include/ClientHandler.h src/CommandsManager.cpp include/CommandsManager.h include/Command.h src/StartGameCommand.cpp include/StartGameCommand.h src/GameDetails.cpp include/GameDetails.h include/GameManager.h src/GameManager.cpp src/GetGamesListCommand.cpp include/GetGamesListCommand.h src/JoinGameCommand.cpp include/JoinGameCommand.h src/ListOfGames.cpp include/ListOfGames.h src/GameManager.cpp include/GameManager.h)

set(CMAKE_CXX_FLAGS -pthread)
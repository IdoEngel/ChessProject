#include "Exceptions.h"

const char* ChessExceptions::PipeException::what() const noexcept {
	return "pipe connnot be connected";
}

const char* ChessExceptions::GameExcption::what() const noexcept {
	return "Wining was occured! game over";
}

const char* ChessExceptions::NoBoardErrors::what() const noexcept {
	return "No errors found in the game level";
}
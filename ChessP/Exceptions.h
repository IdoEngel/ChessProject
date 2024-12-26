#pragma once
#include <exception>

namespace ChessExceptions {

	/*When the pipe is not able to connect*/
	class PipeException : std::exception {
	public:
		const char* what() const noexcept override;
	};

	/*When the game ended*/
	class GameExcption : std::exception {
	public:
		const char* what() const noexcept override;
	};

	/*When the board check for errors found nothing*/
	class NoBoardErrors : std::exception {
		const char* what() const noexcept override;
	};
}

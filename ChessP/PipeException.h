#pragma once
#include <exception>

class PipeException : std::exception {
public: 
	const char* what() const noexcept override {
		return "pipe connnot be connected";
	}
};

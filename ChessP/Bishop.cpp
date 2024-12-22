#include "Bishop.h"
Bishop::Bishop(const std::string& position, const char type) : Piece(type, position)
{
}
Bishop::~Bishop()
{
	this->_way.clear();
}

std::vector<std::string> Bishop::possibleMoves(const std::string& dstPosition)
{

}
#include "Game.h"

//Constractor/Destractor

Game::Game(const bool onGraphics) :
	_board(new Board()), _numOfMoves(0), _onGraphics(onGraphics) {

	//create the players
	this->_playes[0] = Player(WHITE);
	this->_playes[1] = Player(BLACK);

	//on graphics
	if (onGraphics) {
		this->_pipe = new Pipe();

		// free and throw an error if connot connect
		if (!connectToPipe()) {
			delete this->_board;
			delete this->_pipe;
			throw ChessExceptions::PipeException();
		}
		else { //send the first msg to the pipe
			this->_pipe->sendMessageToGraphics((char*)FIRST_MSG_TO_PIPE);
		}
	}
	else {
		this->_pipe = nullptr;
	}

}

Game::~Game()
{
	this->_pipe->close();
	delete this->_pipe;
	delete this->_board;
}

//Helping/getters functions

char Game::getCurrPlayerColor() const noexcept {
	return (this->_numOfMoves % 2 == 0 ? this->_playes[0].getColor() : this->_playes[1].getColor());
}

char Game::getOpponentPlayerColor() const noexcept
{
	return (this->_numOfMoves % 2 == 0 ? this->_playes[1].getColor() : this->_playes[0].getColor());
}

Piece* Game::getKing(const bool isMyKing) const noexcept {
	char kingColor = (isMyKing ? this->getCurrPlayerColor() : this->getOpponentPlayerColor());
	Piece* king = nullptr;

	intArr coords;
	int rowPiece = 0;
	int columnPiece = 0;

	int row = 0;
	int column = 0;
	for (row = 0; row < ROW_COLUMN; row++) {
		for (column = 0; column < ROW_COLUMN; column++) {

			//transfer to the right coords
			coords = Board::strToCoords(Board::coordsToStr(row, column));
			rowPiece = coords.get()->at(SRC_START_INDEX);
			columnPiece = coords.get()->at(SRC_START_INDEX + 1);

			//make sure the piece is not nullptr
			if ((*this->_board)(rowPiece, columnPiece) != nullptr) {

				// if both are black
				if (IS_BLACK_PIECE((*this->_board)(rowPiece, columnPiece)->getType()) &&
					IS_BLACK_PIECE(kingColor) &&
					(*this->_board)(rowPiece, columnPiece)->getType() == B_KING_CHAR) { // take only the king 
					king = (*this->_board)(rowPiece, columnPiece);
				}
				// if both are white
				else if (IS_WHITE_PIECE((*this->_board)(rowPiece, columnPiece)->getType()) &&
					IS_WHITE_PIECE(kingColor) &&
					(*this->_board)(rowPiece, columnPiece)->getType() == W_KING_CHAR) { // take only the king 
					king = (*this->_board)(rowPiece, columnPiece);
				}
			}
		}
	}

	return king;
}

std::string Game::getCoordinatesOfPiece(const Piece* piece) const noexcept { //MAYBE transfer to Board (?)
	char type = piece->getType();
	std::string coordinates = "";
	Piece* p = nullptr;

	intArr coords;
	int rowPiece = 0;
	int columnPiece = 0;

	int row = 0;
	int column = 0;
	for (row = 0; row < ROW_COLUMN; row++) {
		for (column = 0; column < ROW_COLUMN; column++) {

			//transfer to the right coords
			coords = Board::strToCoords(Board::coordsToStr(row, column));
			rowPiece = coords.get()->at(SRC_START_INDEX);
			columnPiece = coords.get()->at(SRC_START_INDEX + 1);

			p = (*this->_board)(static_cast<const int>(rowPiece), static_cast<const int>(columnPiece));
			if (p != nullptr) { // make sure the piece is not nullptr
				if (p->getType() == type) { // if the type is the same
					coordinates = Board::coordsToStr(row, column);
				}
			}
		}
	}
	return coordinates;
}

bool Game::isCurrTurnMatchColorSelected(const Piece* piece) const noexcept {
	bool isVal = false;

	//if nullptr - connot be black or while
	if (piece != nullptr) {
		if (this->_numOfMoves % 2 == 0) {
			isVal = IS_WHITE_PIECE(piece->getType());
		}
		else {
			isVal = IS_BLACK_PIECE(piece->getType());
		}
	}
	return isVal;
}

int Game::lenOfPassibleMoves(const std::string& coord) const noexcept {
	int srcRow = 0;
	int srcColumn = 0;
	int len = 0;
	Piece* piece = nullptr;
	std::vector<std::string> moves;

	//get the coords
	intArr points = Board::strToCoords(coord);
	srcRow = points.get()->at(SRC_START_INDEX);
	srcColumn = points.get()->at(SRC_START_INDEX + 1);

	piece = (*this->_board)(srcRow, srcColumn);
	if (piece != nullptr) {
		moves = piece->possibleMoves(coord);
		len = moves.size();

		// clean vector
		moves.clear();
		moves.resize(0);
	}

	return len;
}

//Logic funcs	

std::ostream& operator<<(std::ostream& os, const Game& g) {
	int row = 0;
	int column = 0;
	Piece* p = nullptr;

	for (row = 0; row < ROW_COLUMN; row++) {
		for (column = 0; column < ROW_COLUMN; column++) {

			p = (*g._board)(row, column);
			if (p == nullptr) {
				os << EMPTY << " ";
			}
			else {
				os << p->getType() << " ";
			}
		}
		os << std::endl;
	}

	return os;
}

std::string Game::play() {
	std::string pCode = "";

	//Choose the right func to run
	if (this->_onGraphics) {
		pCode = playGraphics();
	}
	else {
		pCode = playConsole();
	}

	return pCode;
}

std::string Game::playGraphics() {

	std::string code = "";
	std::string coordinates = this->_pipe->getMessageFromGraphics();
	code = this->codeForGraphics(coordinates);

	if (code == CODE_0 || code == CODE_1) { // code "0" - no errors found

		if (this->_board->movePeice(coordinates)) { //returns if the king was eaten
			code = CODE_8;
		}
		this->_numOfMoves++; //next turn only if code 0 or 1 (successe)
	}

	// if code 8 - game over (raise an error typed game)
	if (code == CODE_8) {
		throw ChessExceptions::GameExcption();
	}


	this->_pipe->sendMessageToGraphics((char*)code.c_str());
	return Game::prettyCodes(code);
}

std::string Game::playConsole() {
	// start turn - choose coords
	std::cout << "Enter the coordinates of the source square and the destination square:" << std::endl;
	std::string coordinates = "";
	std::cin >> coordinates;

	std::string code = "";
	code = this->codeForGraphics(coordinates);

	if (code == CODE_0 || code == CODE_1) { // code "0" - no errors found

		if (this->_board->movePeice(coordinates)) { //returns if the king was eaten
			code = CODE_8;
		}
		this->_numOfMoves++; //next turn only if code 0 or 1 (successe)
	}

	// if code 8 - game over (raise an error typed game)
	if (code == CODE_8) {
		throw ChessExceptions::GameExcption();
	}

	return Game::prettyCodes(code);
}

std::string Game::codeForGraphics(const std::string& coordinats) const noexcept {
	char type = ' ';
	intArr points;
	std::string code = CODE_0;
	int row = 0;
	int column = 0;

	try {
		code = this->_board->isPositionValid(coordinats);
	}
	catch (const ChessExceptions::NoBoardErrors& e) { // error - move is valid (no errors found)
		points = Board::strToCoords(coordinats);
		row = points.get()->at(SRC_START_INDEX);
		column = points.get()->at(SRC_START_INDEX + 1);

		type = (*this->_board)(row, column)->getType();

		//check the src coord (match the color) - the second part of code 2
		if (!isCurrTurnMatchColorSelected((*this->_board)(row, column))) {
			code = CODE_2;
		}
		// code 6 - the move of the piece is valid - part 1 (Pawn only)
		else if (((*this->_board)(row, column)->getType() == W_PAWN_CHAR || (*this->_board)(row, column)->getType() == B_PAWN_CHAR) && //check if pawn
			//check basic movement 
			((!isWayClear((*this->_board)(row, column)->possibleMoves(coordinats), FOR_OPPO_CHECK) ||
				(lenOfPassibleMoves(coordinats) == 0)) ||
				//check specific pawn movement
				!isPawnMoveValid(coordinats)))
		{
			code = CODE_6;
		}
		// code 6 - the move of the piece is valid - part 2 (all other pieces)
		else if (!isWayClear((*this->_board)(row, column)->possibleMoves(coordinats), FOR_OPPO_CHECK) ||
			(lenOfPassibleMoves(coordinats) == 0)) { // invalid move (logicly)
			code = CODE_6;
		}
		//code 4 - self check (first part - if king is moving)
		else if ((((type == W_KING_CHAR) || (type == B_KING_CHAR))) && //if this is a king, continue to the check
			isSelfChecked(coordinats, coordinats, KING_MOVING)) { //getting the king of the current player
			code = CODE_4;
		}
		// code 4 - self check (second part - if the king mo moving) - UNCHECKED
		else if ((!((type == W_KING_CHAR) || (type == B_KING_CHAR))) && // not the king
			(isSelfChecked(getCoordinatesOfPiece(getKing(MY_KING)), coordinats))) {
			code = CODE_4;
		}
		//code 1 (valid) - check if check on other player
		else if (isCheckedOnOpponent(getCoordinatesOfPiece(getKing(OPPO_KING)), coordinats)) {
			code = CODE_1;
		}
		//code 8 - checkmate
		else if (isCheckedOnOpponent(getCoordinatesOfPiece(getKing(OPPO_KING)), coordinats) && //check on opponent must be done
			isCheckmate(getCoordinatesOfPiece(getKing(OPPO_KING)), coordinats)) {
			code = CODE_8;
		}
	}

	return code;
}

bool Game::isCheckedOnOpponent(const std::string& kingCoordinate, const std::string& pieceCoord) const noexcept {
	std::string kingDest = kingCoordinate.substr(kingCoordinate.size() - NOT_THE_LAST_TWO_CHARS);
	std::string pieceDest = pieceCoord.substr(pieceCoord.size() - NOT_THE_LAST_TWO_CHARS);
	std::string pieceSrc = pieceCoord.substr(0, TAKE_TWO_CHARS);

	std::vector<std::string> allMoves;

	bool isChecked = false;
	int loopLen;

	allWays ways = getBoardPiecesInfo(FOR_OPPO_CHECK, kingCoordinate, pieceCoord);
	loopLen = ways.get()->size();

	intArr coords;
	int rowPiece = 0;
	int columnPiece = 0;
	Piece* piece = nullptr;

	int i = 0;
	for (i = 0; i < loopLen; i++) {
		if (std::get<LEN_OF_VECTOR>(ways.get()->at(i)) != 0 && std::get<IS_CLEAR>(ways.get()->at(i))) {
			isChecked = true;
		}
	}

	//check if the curr play coused check
	coords = Board::strToCoords(pieceSrc);
	rowPiece = coords.get()->at(SRC_START_INDEX);
	columnPiece = coords.get()->at(SRC_START_INDEX + 1);

	piece = (*this->_board)(rowPiece, columnPiece);
	//check if pawn
	if ((piece->getType() == W_PAWN_CHAR || piece->getType() == B_PAWN_CHAR) && isPawnMoveValid(pieceSrc + kingDest)) {
		allMoves = piece->possibleMoves(pieceDest + kingDest);
	}
	else if (piece->getType() != W_PAWN_CHAR && piece->getType() != B_PAWN_CHAR) {
		allMoves = piece->possibleMoves(pieceDest + kingDest);
	}


	if (allMoves.size() != 0 && isWayClear(allMoves, FOR_OPPO_CHECK, pieceSrc, pieceDest)) {
		isChecked = true;
	}

	//clear the vector
	allMoves.clear();
	allMoves.resize(0);
	return isChecked;
}

bool Game::isSelfChecked(const std::string& kingCoordinate, const std::string& pieceCoord, const bool isKingPlaying) const noexcept {
	bool isChecked = false;

	int loopLen = 0;
	int lastVectorLen = 0;
	int rowPiece = 0;
	int columnPiece = 0;

	std::string lastMove = "";
	std::string srcCurrPiece = "";
	intArr coords;

	allWays ways = getBoardPiecesInfo(FOR_SELF_CHECK, kingCoordinate, pieceCoord);
	loopLen = ways.get()->size();
	

	int i = 0;
	for (i = 0; i < loopLen; i++) {

		if (//make sure not pawn
			(std::get<TYPE_OF_PIECE>(ways.get()->at(i)) != W_PAWN_CHAR && std::get<TYPE_OF_PIECE>(ways.get()->at(i)) != B_PAWN_CHAR) &&
			std::get<LEN_OF_VECTOR>(ways.get()->at(i)) != 0 && std::get<IS_CLEAR>(ways.get()->at(i))) {
			isChecked = true;
		}
		else if (//only pawn
			(std::get<TYPE_OF_PIECE>(ways.get()->at(i)) == W_PAWN_CHAR || std::get<TYPE_OF_PIECE>(ways.get()->at(i)) == B_PAWN_CHAR) &&
			//check move
			std::get<LEN_OF_VECTOR>(ways.get()->at(i)) != 0 && std::get<IS_CLEAR>(ways.get()->at(i)) &&
			//pawn check
			isPawnMoveValid(std::get<FULL_COORD>(ways.get()->at(i)))) {
			
			isChecked = true;
		}

		//if king is playing - need to check that the king dont "block itself"
		if (isKingPlaying) {
			//try to get to the last elem, if vector is empty - skip all (using the try-block)
			try {
				lastMove = /*get curr vector*/std::get<VECTOR>(ways.get()->at(i)).at(
					/*last in vector*/std::get<VECTOR>(ways.get()->at(i)).size() - 2);

				coords = Board::strToCoords(lastMove);
				rowPiece = coords.get()->at(SRC_START_INDEX);
				columnPiece = coords.get()->at(SRC_START_INDEX + 1);

				//check if the last move in moves is tha king that just moving
				if ((*this->_board)(rowPiece, columnPiece) != nullptr && //check that not nullptr
					//check that the king is on the last move
					((*this->_board)(rowPiece, columnPiece)->getType() == W_KING_CHAR ||
						(*this->_board)(rowPiece, columnPiece)->getType() == B_KING_CHAR)) {
					isChecked = true;
				}
			}
			catch (const std::out_of_range& e) {
				//.... skiping
			}
		}

		if (howManyOnTheWay(std::get<VECTOR>(ways.get()->at(i)), NOT_ONLY_SELF_ON_THE_WAY) <= NO_ENOUGH_PIECES_TO_PROTECT_KING &&
			!isKingPlaying) {

			srcCurrPiece = pieceCoord.substr(0, TAKE_TWO_CHARS);
			int j = 0;
			for (j = 0; j < std::get<VECTOR>(ways.get()->at(i)).size(); j++) {
				if (srcCurrPiece == std::get<VECTOR>(ways.get()->at(i)).at(j)) { // is src is equ - block the way to the king - cannot move
					isChecked = true;
				}
			}

		}
		
	}

	return isChecked;
}

allWays Game::getBoardPiecesInfo(const bool forSelfCheck, const std::string& kingCoordinate, const std::string& pieceCoords) const noexcept {

	allWays waysRet = std::make_unique<std::vector<std::tuple<std::vector<std::string>, char, bool, int, std::string> >>();
	std::vector<std::string> moves;
	std::vector<std::string> currMoves; //moves of moving piece
	Piece* piece;

	std::string kingDest = kingCoordinate.substr(kingCoordinate.size() - NOT_THE_LAST_TWO_CHARS); //get the dest of the king
	std::string pieceSrc = pieceCoords.substr(0, TAKE_TWO_CHARS);
	std::string pieceDest = pieceCoords.substr(pieceCoords.size() - NOT_THE_LAST_TWO_CHARS);

	std::string fullCoord = "";
	std::string lastMove = "";
	std::string srcCurrPiece = "";

	intArr coords;
	int rowPiece = 0;
	int columnPiece = 0;
	char typeDel = ' ';

	int row = 0;
	int column = 0;
	for (row = 0; row < ROW_COLUMN; row++) {
		for (column = 0; column < ROW_COLUMN; column++) {

			//transfer to the right coords
			coords = Board::strToCoords(Board::coordsToStr(row, column));
			rowPiece = coords.get()->at(SRC_START_INDEX);
			columnPiece = coords.get()->at(SRC_START_INDEX + 1);

			if ((*this->_board)(rowPiece, columnPiece) != nullptr && //not nullptr
				//make sure theb king is not playing
				Board::coordsToStr(row, column) != kingDest) {

				//get the moves
				fullCoord = Board::coordsToStr(row, column) + kingDest;
				moves = (*this->_board)(rowPiece, columnPiece)->possibleMoves(fullCoord);
				
				piece = (*this->_board)(rowPiece, columnPiece);
				typeDel = piece->getType();
				if ((piece->getType() == W_PAWN_CHAR || piece->getType() == B_PAWN_CHAR) &&
					!isPawnMoveValid(fullCoord)) {
					moves.resize(0);
				}

				//if for self-check
				if (forSelfCheck && !isCurrTurnMatchColorSelected((*this->_board)(rowPiece, columnPiece))) {

					waysRet.get()->push_back({ {moves}, piece->getType(), 
						isWayClear(moves, forSelfCheck, pieceSrc, pieceDest), static_cast<int>(moves.size()), fullCoord }); 
					
				}
				//for oppo check
				else if (!forSelfCheck && isCurrTurnMatchColorSelected((*this->_board)(rowPiece, columnPiece))) {

					waysRet.get()->push_back({ {moves}, piece->getType(),
						isWayClear(moves, forSelfCheck, pieceSrc, pieceDest), static_cast<int>(moves.size()), fullCoord });
				}

			}
		}
	}

	// add the moving piece in its dest
	coords = Board::strToCoords(pieceSrc);
	rowPiece = coords.get()->at(SRC_START_INDEX);
	columnPiece = coords.get()->at(SRC_START_INDEX + 1);

	piece = (*this->_board)(rowPiece, columnPiece);
	moves = piece->possibleMoves(pieceDest + kingDest);

	if (piece->getType() != W_PAWN_CHAR && piece->getType() != B_PAWN_CHAR) { //if not pawn

		moves = piece->possibleMoves(pieceDest + kingDest);

		waysRet.get()->push_back({ {moves}, piece->getType(),
			isWayClear(moves, forSelfCheck, pieceSrc, pieceDest), static_cast<int>(moves.size()), fullCoord });
	}
	else if ((piece->getType() == W_PAWN_CHAR || piece->getType() == B_PAWN_CHAR) &&
		isPawnMoveValid(pieceDest + kingDest, piece)) { //if pawn

		moves = piece->possibleMoves(pieceDest + kingDest);

		waysRet.get()->push_back({ {moves}, piece->getType(),
			isWayClear(moves, forSelfCheck, pieceSrc, pieceDest), static_cast<int>(moves.size()), fullCoord });
	}

	return waysRet;
}

bool Game::isCheckmate(const std::string& kingCoordinate, const std::string& pieceCoords) const noexcept {
	//in the calling func - allready checked that at leat check has occured
	bool overall = false;
	intArr coords;
	int row = 0;
	int column = 0;

	std::string king = "";
	std::string piece = "";

	/*Checking the all the coods the king cam go to*/

	//first (normal coords) check
	king = kingCoordinate;
	piece = pieceCoords;
	overall = isCheckmateINNER(king, piece);

	//second check
	coords = Board::strToCoords(king);
	row = coords.get()->at(SRC_START_INDEX);
	column = coords.get()->at(SRC_START_INDEX + 1);

	if (Board::isCoordsValid(row + 1, column) && (*this->_board)(row + 1, column) == nullptr) {
		overall = overall && isCheckmateINNER(Board::coordsToStr(row + 1, column), piece);
	}

	//third check
	if (Board::isCoordsValid(row, column + 1) && (*this->_board)(row, column + 1) == nullptr) {
		overall = overall && isCheckmateINNER(Board::coordsToStr(row, column + 1), piece);
	}

	//4th
	if (Board::isCoordsValid(row, column - 1) && (*this->_board)(row, column - 1) == nullptr) {
		overall = overall && isCheckmateINNER(Board::coordsToStr(row, column - 1), piece);
	}

	//5th
	if (Board::isCoordsValid(row - 1, column) && (*this->_board)(row - 1, column) == nullptr) {
		overall = overall && isCheckmateINNER(Board::coordsToStr(row - 1, column), piece);
	}

	return overall;
}

bool Game::isCheckmateINNER(const std::string& kingCoordinate, const std::string& pieceCoords) const noexcept {
	//in the calling func - allready checked that at leat check has occured

	bool isCheckmate = false;

	std::string pieceDest = pieceCoords.substr(pieceCoords.size() - NOT_THE_LAST_TWO_CHARS);
	std::string pieceSrc = pieceCoords.substr(0, TAKE_TWO_CHARS);

	intArr coords;
	std::string coordsStr = "";

	int currRow = 0;
	int currColumn = 0;

	Piece* currPiece = nullptr;
	std::vector<std::string> moves;
	std::vector<std::string>* theClearVector = nullptr;
	allWays allWaysToKing = std::make_unique<std::vector<std::tuple<std::vector<std::string>, char, bool, int, std::string> >>();

	int row = 0;
	int column = 0;
	for (row = 0; row < ROW_COLUMN; row++) {

		for (column = 0; column < ROW_COLUMN; column++) {

			//get real coords
			coords = Board::strToCoords(Board::coordsToStr(row, column));
			currRow = coords.get()->at(SRC_START_INDEX);
			currColumn = coords.get()->at(SRC_START_INDEX + 1);

			coordsStr = Board::coordsToStr(row, column);

			//curr piece is of the pieces that can win
			if ((*this->_board)(currRow, currColumn) != nullptr && //piece exist
				isCurrTurnMatchColorSelected((*this->_board)(currRow, currColumn)) && //piece of the one that can win
				!(((*this->_board)(currRow, currColumn)->getType() == B_KING_CHAR) || ((*this->_board)(currRow, currColumn)->getType() == W_KING_CHAR))) { //not the king

				currPiece = (*this->_board)(currRow, currColumn);
				moves = currPiece->possibleMoves(coordsStr + kingCoordinate);

				allWaysToKing.get()->push_back({ {moves}, currPiece->getType(), 
					isWayClear(moves, FOR_OPPO_CHECK, pieceSrc, pieceDest) , static_cast<int>(moves.size()), 
					coordsStr + kingCoordinate }); //collect all the ways

			}

		}
	}

	if (numOfClearWays(allWaysToKing) > 1) { //more then one way - cannot stop in one move
		isCheckmate = true;
	}

	/*Only one clear way now - if not, does not matter what will happen here, the checkmate allready marked as true*/

	//finding the clear vector
	int i = 0;
	for (i = 0; i < allWaysToKing.get()->size(); i++) {

		if (std::get<IS_CLEAR>(allWaysToKing.get()->at(i))) { //if way clear - this is the one that care about
			theClearVector = &std::get<VECTOR>(allWaysToKing.get()->at(i));
		}
	}

	/*Can the opponent (the one that can lose) block the way?*/
	if (theClearVector != nullptr && !canAnyOfPiecesOfOppoBlockTheWay(*theClearVector, pieceSrc, pieceDest)) { //if cannot - checkmate
		isCheckmate = true;
	}

	return isCheckmate;
}

bool Game::isWayClear(const std::vector<std::string>& moves, const bool forSelfCheck, const std::string& ignore, const std::string& takeIntoCount) const noexcept {
	bool isClear = true;

	int dstRow = 0;
	int dstColumn = 0;
	Piece* lastPiece = nullptr;
	intArr points;

	/*Not including the last index because the last contains the coord that might be
	with piece that the curr player can eat - check later*/

	int i = 0;
	int size = moves.size();
	for (i = 0; i < moves.size() - 1; i++) { // not include the ladt index

		try {
			if (moves.at(i) == ignore) { continue; } //if the same as ignore - next iteration

			if (moves.at(i) == takeIntoCount) { // check if the way in going through coords that will not be empty
				isClear = false;
			}

			points = Board::strToCoords(moves.at(i));

			dstRow = points.get()->at(SRC_START_INDEX);
			dstColumn = points.get()->at(SRC_START_INDEX + 1);

			if ((*this->_board)(dstRow, dstColumn) != nullptr) {
				isClear = false;
			}
		}
		catch (const std::out_of_range& e) {
			break;
			//none - catch if the vector is empty
		}
	}

	//check last index
	//get the last coord and the piece inside it
	try {

		points = Board::strToCoords(moves.at(moves.size() - 1));

		dstRow = points.get()->at(SRC_START_INDEX);
		dstColumn = points.get()->at(SRC_START_INDEX + 1);

		lastPiece = (*this->_board)(dstRow, dstColumn);

		//check
		if (lastPiece != nullptr) { //if match - cannot get to the dest (base case is "isClear = true"
			if (forSelfCheck && !isCurrTurnMatchColorSelected(lastPiece)) {
				isClear = false;
			}
			else if (!forSelfCheck && isCurrTurnMatchColorSelected(lastPiece)) {
				isClear = false;
			}
		}
	}
	catch (const std::out_of_range& e) {
		//none - catch if the vector is empty
	}


	return isClear;
}

bool Game::isPawnMoveValid(const std::string& coords, const Piece* take) const noexcept {
	bool isValid = true;

	intArr intCoords;
	int srcRow = 0;
	int srcColumn = 0;
	int dstRow = 0;
	int dstColumn = 0;
	bool moveDiagmal = false;

	intCoords = Board::strToCoords(coords);
	srcRow = intCoords.get()->at(SRC_START_INDEX);
	srcColumn = intCoords.get()->at(SRC_START_INDEX + 1);
	dstRow = intCoords.get()->at(DST_START_INDEX);
	dstColumn = intCoords.get()->at(DST_START_INDEX + 1);

	moveDiagmal = (Piece::isDiagnollyLeftW(coords) || Piece::isDiagnollyLeftB(coords) ||
		Piece::isDiagnollyRightW(coords) || Piece::isDiagnollyRightB(coords));

	// if special move has occurd
	if (moveDiagmal) {
		// if nullptr no piece wan eaten - false movement
		if ((*this->_board)(dstRow, dstColumn) == nullptr) {
			isValid = false;
		}
	}
	else if (!moveDiagmal && (*this->_board)(dstRow, dstColumn) != nullptr) { //not going diagnolly and the dest is not nullptr
		isValid = false;
	}
	
	/*take - when the coord is for the future -need a one what valid*/
	if (take == nullptr) {

		// check each color seperatly
		if ((*this->_board)(srcRow, srcColumn)->getType() == W_PAWN_CHAR) {
			if (srcRow < dstRow) { //didt move backwords
				isValid = false;
			}
			else if (SECOND_ROW_OF_SOLDIERS != srcRow + 1 && (std::abs(srcRow - dstRow) > 1)) { //no more then one sqr at a time
				isValid = false;
			}
		}
		else if ((*this->_board)(srcRow, srcColumn)->getType() == B_PAWN_CHAR) {
			if (srcRow > dstRow) { //didt move backwords
				isValid = false;
			}
			else if (FIRST_ROW_OF_SOLDIERS != srcRow + 1 && (std::abs(srcRow - dstRow) > 1)) { //no more then one sqr at a time
				isValid = false;
			}
		}
	}
	else {
		// check each color seperatly
		if (take->getType() == W_PAWN_CHAR) {
			if (srcRow < dstRow) { //didt move backwords 
				isValid = false;
			}
			else if (SECOND_ROW_OF_SOLDIERS != srcRow + 1 && (std::abs(srcRow - dstRow) > 1)) { //no more then one sqr at a time
				isValid = false;
			}
		}
		else if (take->getType() == B_PAWN_CHAR) {
			if (srcRow > dstRow) { //didt move backwords 
				isValid = false;
			}
			else if (FIRST_ROW_OF_SOLDIERS != srcRow + 1 && (std::abs(srcRow - dstRow) > 1)) { //no more then one sqr at a time
				isValid = false;
			}
		}
	}

	return isValid;
}

unsigned int Game::howManyOnTheWay(const std::vector<std::string>& way, const bool onlySelfPieces) const noexcept {
	intArr coord;
	int row = 0;
	int column = 0;
	unsigned int count = 0;

	int i = 0;

	//skip if not enogh len to the 'way' var
	try {
		for (i = 0; i < way.size(); i++) {
			//get coord in nums
			coord = Board::strToCoords(way[i]);
			row = coord.get()->at(SRC_START_INDEX);
			column = coord.get()->at(SRC_START_INDEX + 1);

			//count only the self pieces
			if ((*this->_board)(row, column) != nullptr &&
				onlySelfPieces && isCurrTurnMatchColorSelected((*this->_board)(row, column))) {
				count++;
			}
			//count all (both colors)
			else if ((*this->_board)(row, column) != nullptr) {
				count++;
			}
		}
	}
	catch (const std::out_of_range& e) {
		//...skiping
	}

	return count;
}

std::string Game::prettyCodes(const std::string& code) noexcept {
	std::string ret = "";

	switch (static_cast<codes>(std::stoi(code)))   //checking what is the return value
	{
	case codes::CODE0:   //for valid move//
		ret = "valid: next turn..";
		break;
	case codes::CODE1:   //valid move, player made check on opponent//
		ret = "Check on opponent!";
		break;
	case codes::CODE2:   //error code 2 - src square doesnt have a piece for curr player//
		ret = "Error! no curr player piece in src square!";
		break;
	case codes::CODE3:  //error code 3 - theres a piece of the curr palyer in the dst square//
		ret = "Error! curr player piece in dst square!";
		break;
	case codes::CODE4:   //error code 4 - movement coused a check on curr player//
		ret = "Error! Check on yourself!";
		break;
	case codes::CODE5:   //error code 5 - invalid indexes of movement//
		ret = "Error! invalid indexes for squares!";
		break;
	case codes::CODE6:   //error code 6 - invalid movement of the chosen piece//
		ret = "Error! Invalid movement of curr piece!";
		break;
	case codes::CODE7:  //error code 7 - same src and dst squares//
		ret = "Error! src square and dst square are equal!";
		break;
	case codes::CODE8:  //valid movement, paleyer won the game//
		ret = "Checkmate!";
	}

	return ret;
}

bool Game::connectToPipe() noexcept {
	bool isConnect = this->_pipe->connect();
	unsigned int counter = 0;

	srand(time_t(NULL));

	//try 30 times - stop if connected
	while (!isConnect && counter < TOO_MANY_TRYEIS) {
		counter++;
		Sleep(5000);
		isConnect = this->_pipe->connect();
	}

	return isConnect;
}

unsigned int Game::numOfClearWays(const allWays& ways) const noexcept {
	unsigned int numOfWays = 0;

	int i = 0;
	for (i = 0; i < ways.get()->size(); i++) {

		if (std::get<IS_CLEAR>(ways.get()->at(i))) {
			numOfWays++;
		}
	}

	return numOfWays;
}

bool Game::canAnyOfPiecesOfOppoBlockTheWay(const std::vector<std::string>& wayToBlock, const std::string& ignore, const std::string& takeIntoCount) const noexcept{
	bool canBlockTheWay = false;

	std::vector<std::string> moves; // ways of each to the target
	intArr coords;
	std::string coordsStr = "";

	int currRow = 0;
	int currColumn = 0;

	int row = 0;
	int column = 0;
	for (row = 0; row < ROW_COLUMN; row++) {
		for (column = 0; column < ROW_COLUMN; column++) {

			//get real coords
			coords = Board::strToCoords(Board::coordsToStr(row, column));
			currRow = coords.get()->at(SRC_START_INDEX);
			currColumn = coords.get()->at(SRC_START_INDEX + 1);

			coordsStr = Board::coordsToStr(row, column);

			if ((*this->_board)(currRow, currColumn) != nullptr && //piece exist
				!isCurrTurnMatchColorSelected((*this->_board)(currRow, currColumn)) && //piece of opponent (the one that can lose)
				!(((*this->_board)(currRow, currColumn)->getType() == B_KING_CHAR) || ((*this->_board)(currRow, currColumn)->getType() == W_KING_CHAR))) { //not the king

				//check for every valid piece (piece of opponent) if can move to any of the points that can block the way
				int i = 0;
				for (i = 0; i < wayToBlock.size(); i++) {
					moves = (*this->_board)(currRow, currColumn)->possibleMoves(coordsStr + wayToBlock.at(i)); //get the moves from curr to move on the way

					// if way exists and clear - can block
					if (moves.size() != 0 && isWayClear(moves, FOR_OPPO_CHECK, ignore, takeIntoCount)) {
						canBlockTheWay = true;
					}

					//clear the vector
					moves.clear();
					moves.resize(0);
				}
			}

		}
	}

	return canBlockTheWay;
}


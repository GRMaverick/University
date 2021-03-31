//------------------------------------------------------------------------
//  Author: Paul Roberts 2016
//------------------------------------------------------------------------

#include "ChessPlayerAI.h"
#include <iostream>		//cout
#include <SDL.h>
#include <iomanip>		//Precision
#include <algorithm>	//Sort
#include "ChessConstants.h"
#include "../Texture2D.h"
#include "ChessMoveManager.h"

using namespace::std;

//--------------------------------------------------------------------------------------------------

const int kPawnScore		= 1;
const int kKnightScore		= 5;
const int kBishopScore	= 5;
const int kRookScore		= 10;
const int kQueenScore	= 25;
const int kKingScore		= 0;

const int kStalemateScore		= 25;		//Tricky one because sometimes you want this, sometimes you don't.
const int kCheckScore				= 100;
const int kCheckmateScore		= 9999;

const int kPieceWeight			= 1;		//Scores as above.
const int kMoveWeight			= 1;		//Number of moves available to pieces.
const int kPositionalWeight		= 1;		//Whether in CHECK, CHECKMATE or STALEMATE.

const int kBoardPositionalScores[8][8] = 
{
	{ 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 3, 3, 3, 3, 1, 1 },
	{ 2, 2, 3, 5, 5, 3, 2, 2 },
	{ 2, 2, 3, 5, 5, 3, 2, 2 },
	{ 1, 1, 3, 3, 3, 3, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1 },
};

//--------------------------------------------------------------------------------------------------

ChessPlayerAI::ChessPlayerAI(SDL_Renderer* renderer, COLOUR colour, Board* board, vector<Vector2D>* highlights, Vector2D* selectedPiecePosition, Move* lastMove, int* searchDepth)
	: ChessPlayer(renderer, colour, board, highlights, selectedPiecePosition, lastMove)
{
	mDepthToSearch = searchDepth;
}

//--------------------------------------------------------------------------------------------------

ChessPlayerAI::~ChessPlayerAI()
{
}

//--------------------------------------------------------------------------------------------------

bool ChessPlayerAI::MakeAMove(Move* move)
{	
	if (move->from_X == 0.0f && move->from_Y == 0.0f && move->to_X == 0.0f && move->to_Y == 0.0f)
		return false;

	//If this was an en'passant move the taken piece will not be in the square we moved to.
	if (mChessBoard->currentLayout[move->from_X][move->from_Y].piece == PIECE_PAWN)
	{
		//If the pawn is on its start position and it double jumps, then en'passant may be available for opponent.
		if ((move->from_Y == 1 && move->to_Y == 3) ||
			(move->from_Y == 6 && move->to_Y == 4))
		{
			mChessBoard->currentLayout[move->from_X][move->from_Y].canEnPassant = true;
		}
	}

	//En'Passant removal of enemy pawn.
	//If our pawn moved into an empty position to the left or right, then must be En'Passant.
	if (mChessBoard->currentLayout[move->from_X][move->from_Y].piece == PIECE_PAWN &&
		mChessBoard->currentLayout[move->to_X][move->to_Y].piece == PIECE_NONE)
	{
		int pawnDirectionOpposite = mTeamColour == COLOUR_WHITE ? -1 : 1;

		if ((move->from_X < move->to_X) ||
			(move->from_X > move->to_X))
		{
			mChessBoard->currentLayout[move->to_X][move->to_Y + pawnDirectionOpposite] = BoardPiece();
		}
	}

	//CASTLING - Move the rook.
	if (mChessBoard->currentLayout[move->from_X][move->from_Y].piece == PIECE_KING)
	{
		//Are we moving 2 spaces??? This indicates CASTLING.
		if (move->to_X - move->from_X == 2)
		{
			//Moving 2 spaces to the right - Move the ROOK on the right into its new position.
			mChessBoard->currentLayout[move->from_X + 3][move->from_Y].hasMoved = true;
			mChessBoard->currentLayout[move->from_X + 1][move->from_Y] = mChessBoard->currentLayout[move->from_X + 3][move->from_Y];
			mChessBoard->currentLayout[move->from_X + 3][move->from_Y] = BoardPiece();
		}
		else if (move->to_X - move->from_X == -2)
		{
			//Moving 2 spaces to the left - Move the ROOK on the left into its new position.
			//Move the piece into new position.
			mChessBoard->currentLayout[move->from_X - 4][move->from_Y].hasMoved = true;
			mChessBoard->currentLayout[move->from_X - 1][move->from_Y] = mChessBoard->currentLayout[move->from_X - 4][move->from_Y];
			mChessBoard->currentLayout[move->from_X - 4][move->from_Y] = BoardPiece();
		}
	}

	//Move the piece into new position.
	mChessBoard->currentLayout[move->from_X][move->from_Y].hasMoved = true;
	mChessBoard->currentLayout[move->to_X][move->to_Y] = mChessBoard->currentLayout[move->from_X][move->from_Y];
	mChessBoard->currentLayout[move->from_X][move->from_Y] = BoardPiece();

	//Store the last move to output at start of turn.
	mLastMove->from_X = move->from_X;
	mLastMove->from_Y = move->from_Y;
	mLastMove->to_X = move->to_X;
	mLastMove->to_Y = move->to_Y;

	//Record the move.
	MoveManager::Instance()->StoreMove(*move);

	//Piece is in a new position.
	mSelectedPiecePosition->x = move->to_X;
	mSelectedPiecePosition->y = move->to_Y;

	//Check if we need to promote a pawn.
	if (mChessBoard->currentLayout[move->to_X][move->to_Y].piece == PIECE_PAWN && (move->to_Y == 0 || move->to_Y == 7))
	{
		//Time to promote - Always QUEEN at the moment.
		PIECE newPieceType = PIECE_QUEEN;

		//Change the PAWN into the selected piece.
		mChessBoard->currentLayout[move->to_X][move->to_Y].piece = newPieceType;
	}

	//Not finished turn yet.
	return true;
}
bool ChessPlayerAI::RetractLastMove()
{
	Move lastMove = MoveManager::Instance()->GetLastMove();

	Move moveBack = Move(lastMove.to_X, lastMove.to_Y, lastMove.from_X, lastMove.from_Y);

	MakeAMove(&moveBack);

	return true;
}
bool ChessPlayerAI::RetractLastMove(Move* move)
{
	Move moveBack = Move(move->to_X, move->to_Y, move->from_X, move->from_Y);

	MakeAMove(&moveBack);

	return true;
}

//--------------------------------------------------------------------------------------------------

bool ChessPlayerAI::TakeATurn(SDL_Event e)
{
	//TODO: Code your own function - Remove this version after, it is only here to keep the game functioning for testing.

	for (int row = 0; row < kBoardDimensions; row++)
	{
		for (int column = 0; column < kBoardDimensions; column++)
		{
			switch (mChessBoard->currentLayout[row][column].colour)
			{
			case COLOUR_BLACK:
				break;
			case COLOUR_WHITE:
			case COLOUR_NONE:
			default:
				break;
			}
		}
	}

	DWORD startTime = GetTickCount();

	Move bestMove;
	MiniMax(*mChessBoard, *mDepthToSearch, &bestMove);
	MakeAMove(&bestMove);

	DWORD currentTime = GetTickCount();

	std::string from = MoveManager::Instance()->ConvertBoardPositionIntToLetter(bestMove.from_X) + std::to_string(bestMove.from_Y + 1);
	std::string to = MoveManager::Instance()->ConvertBoardPositionIntToLetter(bestMove.to_X) + std::to_string(bestMove.to_Y + 1);
	std::cout << std::endl << "TakeATurn: BestMove is " << from << " to " << to << ": " << bestMove.score << std::endl;

	cout << " - [AI Time taken: " << std::setprecision(10) << (currentTime - startTime) / 1000.0f << " seconds]";
	return true;
}

//--------------------------------------------------------------------------------------------------

int ChessPlayerAI::MiniMax(Board& board, int depth, Move* bestMove)
{
	return Maximise(board, depth, bestMove, MaxInt);
}

//--------------------------------------------------------------------------------------------------

int ChessPlayerAI::Maximise(Board& board, int depth, Move* bestMove, int parentLow)
{
	if (depth == 0)
	{
		return ScoreTheBoard(board);
	}
	else
	{
		int bestScore = -9999;

		vector<Move> moves;
		GetAllMoveOptions(board, mTeamColour, &moves);

		for (Move mv : moves)
		{
			std::string from = MoveManager::Instance()->ConvertBoardPositionIntToLetter(mv.from_X) + std::to_string(mv.from_Y+1);
			std::string to = MoveManager::Instance()->ConvertBoardPositionIntToLetter(mv.to_X) + std::to_string(mv.to_Y+1);

			MakeAMove(&mv);
			mv.score = Minimise(board, depth - 1, bestMove, MaxInt);

			std::cout << std::endl << "Move is " << from << " to " << to << ": " << mv.score << std::endl;

			if (mv.score > bestScore)
			{
				bestScore = mv.score;

				bestMove->from_X = mv.from_X;
				bestMove->from_Y = mv.from_Y;
				bestMove->to_X = mv.to_X;
				bestMove->to_Y = mv.to_Y;
				bestMove->score = mv.score;

				std::string from = MoveManager::Instance()->ConvertBoardPositionIntToLetter(bestMove->from_X) + std::to_string(bestMove->from_Y + 1);
				std::string to = MoveManager::Instance()->ConvertBoardPositionIntToLetter(bestMove->to_X) + std::to_string(bestMove->to_Y + 1);
				std::cout << std::endl << "Max BestMove is " << from << " to " << to << ": " << mv.score << std::endl;
			}

			RetractLastMove(&mv);
		}

		return bestScore;
	}
}

//--------------------------------------------------------------------------------------------------

int ChessPlayerAI::Minimise(Board& board, int depth, Move* bestMove, int parentHigh)
{
	if (depth == 0)
	{
		return ScoreTheBoard(board);
	}
	else
	{
		int bestScore = 9999;

		vector<Move> moves;
		GetAllMoveOptions(board, mTeamColour, &moves);

		for (Move mv : moves)
		{
			std::string from = MoveManager::Instance()->ConvertBoardPositionIntToLetter(mv.from_X) + std::to_string(mv.from_Y+1);
			std::string to = MoveManager::Instance()->ConvertBoardPositionIntToLetter(mv.to_X) + std::to_string(mv.to_Y+1);

			MakeAMove(&mv);
			mv.score = Maximise(board, depth - 1, bestMove, MaxInt);

			std::cout << std::endl << "Move is " << from << " to " << to << ": " << mv.score << std::endl;

			if (mv.score < bestScore)
			{
				bestScore = mv.score;

				bestMove->from_X = mv.from_X;
				bestMove->from_Y = mv.from_Y;
				bestMove->to_X = mv.to_X;
				bestMove->to_Y = mv.to_Y;
				bestMove->score = mv.score;

				std::string from = MoveManager::Instance()->ConvertBoardPositionIntToLetter(bestMove->from_X) + std::to_string(bestMove->from_Y + 1);
				std::string to = MoveManager::Instance()->ConvertBoardPositionIntToLetter(bestMove->to_X) + std::to_string(bestMove->to_Y + 1);
				std::cout << std::endl << "Min BestMove is " << from << " to " << to << ": " << mv.score << std::endl;
			}
			RetractLastMove(&mv);
		}

		return bestScore;
	}
}

//--------------------------------------------------------------------------------------------------

void ChessPlayerAI::OrderMoves(Board board, vector<Move>* moves, bool highToLow)
{
	//TODO
}

//--------------------------------------------------------------------------------------------------

void ChessPlayerAI::CropMoves(vector<Move>* moves, unsigned int maxNumberOfMoves)
{
	//TODO
}

//--------------------------------------------------------------------------------------------------

int ChessPlayerAI::ScoreTheBoard(Board boardToScore)
{
	int score = 0;
	
	score += this->MaterialScore(boardToScore) * kPieceWeight;
	score += this->PositionalScore(boardToScore) * kPositionalWeight;
	score += this->MovementScore(boardToScore) * kMoveWeight;

	return score;
}

int ChessPlayerAI::MaterialScore(Board boardToScore)
{
	int score = 0;
	int colourMultiplier = 0;

	int kings = 0;
	int queens = 0;
	int rooks = 0;
	int bishops = 0;
	int knights = 0;
	int pawns = 0;

	for (int row = 0; row < kBoardDimensions; row++)
	{
		for (int column = 0; column < kBoardDimensions; column++)
		{
			switch (boardToScore.currentLayout[row][column].colour)
			{
			case COLOUR_BLACK:
				colourMultiplier = 1;		// AI's
				break;
			case COLOUR_WHITE:
				colourMultiplier = -1;		// Player's
				break;
			case COLOUR_NONE:
			default:
				break;
			}
			switch (boardToScore.currentLayout[row][column].piece)
			{
			case PIECE_PAWN:
				pawns +=		kPawnScore * colourMultiplier;
				break;
			case PIECE_KNIGHT:
				knights +=	kKnightScore * colourMultiplier;
				break;
			case PIECE_ROOK:
				rooks +=		kRookScore * colourMultiplier;
				break;
			case PIECE_BISHOP:
				bishops +=	kBishopScore * colourMultiplier;
				break;
			case PIECE_QUEEN:
				queens +=	kQueenScore * colourMultiplier;
				break;
			case PIECE_KING:
				kings +=		kKingScore * colourMultiplier;
				break;
			case PIECE_NONE:
			default:
				break;
			}
		}
	}

	score += kings + queens + rooks + bishops + knights + pawns;

	return score;
}
int ChessPlayerAI::PositionalScore(Board boardToScore)
{
	int score = 0;

	for (int row = 0; row < kBoardDimensions; row++)
	{
		for (int column = 0; column < kBoardDimensions; column++)
		{
			switch (boardToScore.currentLayout[row][column].colour)
			{
				case COLOUR_BLACK:
					score += kBoardPositionalScores[row][column] * 1;
					break;
				case COLOUR_WHITE:
					score += kBoardPositionalScores[row][column] * -1;
					break;
				case COLOUR_NONE:
				default:
					break;
			}			
		}
	}

	return score;
}
int ChessPlayerAI::MovementScore(Board boardToScore)
{
	int score = 0;
	return score;
}

//--------------------------------------------------------------------------------------------------

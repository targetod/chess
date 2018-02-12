#pragma once
#ifndef ASYNC_AI_PLAYER_H_INCLUDED
#define ASYNC_AI_PLAYER_H_INCLUDED

#include <global.h>
#include <list>

#include "asyncplayer.h"

#include "chessboard.h"

#include "chessplayer.h"


// Pieces' values
#define WIN_VALUE  50000	// win the game
#define PAWN_VALUE    30	// 8x
#define ROOK_VALUE    90	// 2x
#define KNIGHT_VALUE  85	// 2x
#define BISHOP_VALUE  84	// 2x
#define QUEEN_VALUE  300	// 1x
#define KING_VALUE 	 ((PAWN_VALUE * 8) + (ROOK_VALUE * 2) \
                        + (KNIGHT_VALUE * 2) + (BISHOP_VALUE * 2) + QUEEN_VALUE + WIN_VALUE)

class ChessBoard;

struct EvaluationInformation {
    int depth = 0;
    int alpha = 0;
    int beta = 0;
    bool quiescent = 0;
    #ifdef TRACE
    std::list<Move> * moved = NULL;
    std::list<Move> * best = NULL;
    #endif
};

class AsyncAiPlayer : public AsyncPlayer, public std::enable_shared_from_this<AsyncAiPlayer>
{
public:
    AsyncAiPlayer(int color, int search_depth);
    virtual ~AsyncAiPlayer();

    virtual void asyncPrepare(const ChessBoard & board, ReadyHandler handler) ;
    virtual void asyncGetNext(const ChessBoard & board, MoveReadyHandler handler) ;
    virtual void asyncShowMove(const ChessBoard & board, const Move & move, ReadyHandler handler);
    virtual void asyncShowResult(const ChessBoard & board, EndStatus status, ReadyHandler handler);

    /**
     * @brief cancel -- cancels any of the asunc operation
     */
    virtual void cancel();

    AsyncPlayer::EndStatus getStatus ( ChessBoard & board);

private:
    void prepare(const ChessBoard & board, ReadyHandler handler) ;
    void getMove(const ChessBoard & board, MoveReadyHandler handler) ;

    void showMove(const ChessBoard & board, const Move & move, ReadyHandler handler) ;

    /*
    * MinMax search for best possible outcome
    */
    int evalAlphaBeta(ChessBoard & board, const EvaluationInformation * info) const;

    /*
    * For now, this checks only material
    */
    int evaluateBoard(const ChessBoard & board) const;


protected:

    /*
    * how deep to min-max
    */
    int ai_depth;


};


#endif

#pragma once
#ifndef ASYNC_AI_PLAYER_H_INCLUDED
#define ASYNC_AI_PLAYER_H_INCLUDED

#include "asyncplayer.h"

class AsyncAiPlayer : public AsyncPlayer
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


protected:

    /*
    * how deep to min-max
    */
    int ai_depth;
};


#endif

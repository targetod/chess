

#include "asyncaiplayer.h"

AsyncAiPlayer::AsyncAiPlayer(int color, int search_depth)
 : AsyncPlayer(color),
   ai_depth(search_depth)
{
    srand(time(NULL));
}

AsyncAiPlayer::~AsyncAiPlayer()
{

}

void AsyncAiPlayer::asyncPrepare(const ChessBoard & board,
                                 ReadyHandler handler)
{

}
void AsyncAiPlayer::asyncGetNext(const ChessBoard & board,
                                 MoveReadyHandler handler)
{

}

void AsyncAiPlayer::asyncShowMove(const ChessBoard & board,
                                  const Move & move,
                                  ReadyHandler handler)
{

}

void AsyncAiPlayer::asyncShowResult(const ChessBoard & board,
                                    EndStatus status,
                                    ReadyHandler handler)
{

}

#pragma once
#include <memory>
#include <boost/asio/io_service.hpp>

#include "asyncaiplayer.h"
#include "chessboard.h"

using namespace  std;

class AsyncGame {

public:
    AsyncGame (shared_ptr<boost::asio::io_service>  io_ptr,
               shared_ptr<AsyncAiPlayer> player1,
               shared_ptr<AsyncAiPlayer> player2);

    void start (AsyncPlayer::ResultReadyHandler  setStatusFunc);

private:
    shared_ptr<boost::asio::io_service> ptr_io_serv_;
    shared_ptr<AsyncAiPlayer> ptr_player1_;
    shared_ptr<AsyncAiPlayer> ptr_player2_;
  //  boost::asio::io_service::strand  strand_;
    ChessBoard board_;
    AsyncPlayer::EndStatus status_;

};

#pragma once

#include <boost/asio/io_service.hpp>
#include "asyncaiplayer.h"
#include "chessboard.h"

class AsyncGame {

    AsyncGame (shared_ptr<boost::asio::io_service>  io_ptr,
               shared_ptr<AsyncAiPlayer> player1,
               shared_ptr<AsyncAiPlayer> player2)
    :ptr_io_serv_(io_ptr),
     ptr_player1_(player1),
     ptr_player2_(player2),
     status_(ChessPlayer::Normal)
    {
            board.initDefaultSetup();
    }

    void start (AsyncPlayer::ResultReadyHandler  setStatusFunc){
        //to do
        // strand need use wrap   post
        // prepare
        ptr_player1_->prepare(board_);
        ptr_player2_->prepare(board_);
        AdvancedMoveData advanced;
        while (status_ == ChessPlayer::Normal || status_ == ChessPlayer::InCheck) {
            Move move;
            // get move from one player
            ptr_player1_->getMove(board_, move, &advanced);
            // execute move
            board_.move(move);
            // show this move to other player
            ptr_player2_->showMove(board_, move);
            board_.print(move);
            cout << "Evaluation: " << advanced.board_evaluation << endl;
            cout << board_.toFEN() << endl;

            status = board_.getPlayerStatus(ptr_player2_->getColor());
            // exchange players
            std::swap(ptr_player1_, ptr_player2_);

            int figures_count = board_.get_all_figures_count();
            board_.refreshFigures();
            if (figures_count != board_.get_all_figures_count()) {
                cerr << "Figures count problem";
                exit(1);
            }
        }


        // callback
        setStatusFunc(status_);
    }


private:
    shared_ptr<boost::asio::io_service> ptr_io_serv_;
    shared_ptr<AsyncAiPlayer> ptr_player1_;
    shared_ptr<AsyncAiPlayer> ptr_player2_;

    ChessBoard board_;
    ChessPlayer::Status status_;
};

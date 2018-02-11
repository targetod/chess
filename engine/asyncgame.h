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
               shared_ptr<AsyncAiPlayer> player2)
    :ptr_io_serv_(io_ptr),
     ptr_player1_(player1),
     ptr_player2_(player2),
     strand_(make_shared<boost::asio::io_service::strand>(*ptr_io_serv_)),
     status_(AsyncPlayer::NONE)
    {

            board_.initDefaultSetup();
            ptr_player1_->setService(ptr_io_serv_);
            ptr_player2_->setService(ptr_io_serv_);
            ptr_player1_->setStrand(strand_);
            ptr_player2_->setStrand(strand_);

    }

    void start (AsyncPlayer::ResultReadyHandler  setStatusFunc){
        //to do
        // strand need use wrap   post
        // prepare

        ptr_player1_->asyncPrepare(board_,    [] () {/* do nothing*/ }  );// TRUE
        ptr_player2_->asyncPrepare(board_,    [] () {/* do nothing*/ }  );// TRUE
        //AdvancedMoveData advanced;

        while (status_ == ChessPlayer::Normal || status_ == ChessPlayer::InCheck) {
            Move move;
            // get move from one player
            //ptr_player1_->getMove(board_, move, &advanced);
            ptr_player1_->asyncGetNext(board_,
                            [this, &move] (const Move & mv)  {
                            // execute move
                            move = mv;
                            board_.move(move);
            }); // TRUE


            //asyncShowResult(const ChessBoard & board, EndStatus status, ReadyHandler handler);

            // execute move
            //board_.move(move);

            // show this move to other player
           // ptr_player2_->showMove(board_, move);
            ptr_player2_-> asyncShowMove(board_, move,
                                         [this, move]() {

                board_.print(move);
                //cout << "Evaluation: " << advanced.board_evaluation << endl;
                cout << board_.toFEN() << endl;
            } );


            status_ = board_.getPlayerStatus(ptr_player2_->getColor());
            // exchange players
            std::swap(ptr_player1_, ptr_player2_);


        }

        // callback
        setStatusFunc(status_);
    }


private:
    shared_ptr<boost::asio::io_service> ptr_io_serv_;
    shared_ptr<AsyncAiPlayer> ptr_player1_;
    shared_ptr<AsyncAiPlayer> ptr_player2_;
    shared_ptr<boost::asio::io_service::strand> strand_;
    ChessBoard board_;
    AsyncPlayer::EndStatus status_;
};

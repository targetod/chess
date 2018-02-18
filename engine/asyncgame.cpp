#include <boost/asio/strand.hpp>
#include <boost/bind.hpp>
#include "asyncgame.h"


AsyncGame::AsyncGame (shared_ptr<boost::asio::io_service>  io_ptr,
           shared_ptr<AsyncAiPlayer> player1,
           shared_ptr<AsyncAiPlayer> player2)
:ptr_io_serv_(io_ptr),
 ptr_player1_(player1),
 ptr_player2_(player2),
 // strand_(*ptr_io_serv_),
 status_(AsyncPlayer::NONE)
{

        board_.initDefaultSetup();
        auto str_ptr = make_shared<boost::asio::io_service::strand>(*ptr_io_serv_);
        //strand_ = make_shared<boost::asio::io_service::strand>();
        ptr_player1_->setService(ptr_io_serv_);
        ptr_player2_->setService(ptr_io_serv_);
        ptr_player1_->setStrand(str_ptr);
        ptr_player2_->setStrand(str_ptr);

}



void AsyncGame::start (AsyncPlayer::ResultReadyHandler  setStatusFunc){

    StatusFunc_ = setStatusFunc;
    ptr_io_serv_->post(  boost::bind( &AsyncGame::do_start, this));
}

void AsyncGame::onGetNext(const Move & mv){
    move_ = mv;
    board_.move(move_);
    ptr_player2_-> asyncShowMove(board_, move_, boost::bind(&AsyncGame::onShowMove,this));
}

void AsyncGame::onShowMove(){
    board_.print(move_);
    //cout << "Evaluation: " << advanced.board_evaluation << endl;
    cout << board_.toFEN() << endl;

    status_ = ptr_player2_->getStatus(board_);
    if (status_ != AsyncPlayer::NONE){
        StatusFunc_(status_);
    }else{
    // exchange players
        std::swap(ptr_player1_, ptr_player2_);
        ptr_player1_->asyncGetNext(board_, boost::bind(&AsyncGame::onGetNext,this, _1));
    }
}

void AsyncGame::do_start(){

    ptr_player1_->asyncPrepare(board_,    [] () {/* do nothing*/ }  );// TRUE
    ptr_player2_->asyncPrepare(board_,    [] () {/* do nothing*/ }  );// TRUE

    // get move from one player
    ptr_player1_->asyncGetNext(board_, boost::bind(&AsyncGame::onGetNext,this, _1));

}

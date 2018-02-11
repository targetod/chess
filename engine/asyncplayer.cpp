#include "asyncplayer.h"

AsyncPlayer::AsyncPlayer(int color):
    color(color)
{

}

AsyncPlayer::~AsyncPlayer()
{

}

int AsyncPlayer::getColor() const
{
    return color;
}

void AsyncPlayer::setColor(int value)
{
    color = value;
}

std::shared_ptr<boost::asio::io_service::strand> AsyncPlayer::getStrand() const
{
    return strand_;
}

void AsyncPlayer::setStrand(const std::shared_ptr<boost::asio::io_service::strand> &value)
{
    strand_ = value;
}

std::shared_ptr<boost::asio::io_service> AsyncPlayer::getService() const
{
    return ptr_serv_;
}

void AsyncPlayer::setService(const std::shared_ptr<boost::asio::io_service> &value)
{
    ptr_serv_ = value;
}


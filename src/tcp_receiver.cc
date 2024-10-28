#include <iostream>
#include "tcp_receiver.hh"
using namespace std;

void TCPReceiver::receive( TCPSenderMessage message )
{

  //cout<<"^^^^^^^^^^^^^TCP sender message: SYN: "<<message.SYN<<" FIN: "<<message.FIN<<" RST: "<<message.RST<<" seq length: "<<message.sequence_length()<<"\n payload: "<<message.payload<<endl;

  if(message.SYN) isn_ = message.seqno;
  if(message.RST) reassembler_.reader().set_error();
  if(isn_.has_value())
  {
     uint64_t index_ = message.seqno.unwrap(*isn_,reassembler_.writer().bytes_pushed());
     //if (index_ < 0) message.payload = "";
     if (index_ == 0 && !message.SYN) message.payload = "";
     if(index_>0 && !message.SYN) index_ = index_ - 1;
     reassembler_.insert(index_,message.payload,message.FIN);
     if(message.FIN) close = 1;
     if(close && reassembler_.bytes_pending() == 0) actuallyClose = 1;
     //cout<<"index_: "<<index_<<endl;
  }
}

TCPReceiverMessage TCPReceiver::send() const
{
  TCPReceiverMessage tcpRM;
  if(reassembler_.reader().has_error())  tcpRM.RST = true;

  if(isn_.has_value())
  {
    tcpRM.ackno = isn_.value().wrap(reassembler_.writer().bytes_pushed()+1+actuallyClose , isn_.value());
    //cout<<">>>>>>TCPReceiverMsg   ackno: "<<tcpRM.ackno.value().raw_value_<<"   bytes_pushed: "<<reassembler_.writer().bytes_pushed()+1+actuallyClose<<endl;
  }
  tcpRM.window_size = (reassembler_.writer().available_capacity()<65535)?reassembler_.writer().available_capacity():65535 ;  
  return tcpRM;
}

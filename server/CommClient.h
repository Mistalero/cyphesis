// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2000,2001 Alistair Riddoch

#ifndef SERVER_COMM_CLIENT_H
#define SERVER_COMM_CLIENT_H

#include <Atlas/Objects/Decoder.h>
#include <Atlas/Objects/Encoder.h>
#include <Atlas/Net/Stream.h>
#include <Atlas/Codec.h>

#include <skstream/skstream.h>

class CommServer;
class Connection;

class CommClient : Atlas::Objects::Decoder {
  public:
    CommServer & commServer;

  private:
    basic_socket_stream clientIos;
    Atlas::Codec<std::iostream> * codec;
    Atlas::Objects::Encoder * encoder;
    Atlas::Net::StreamAccept * accept;
    Connection & connection;

    bool negotiate();
  protected:
    virtual void UnknownObjectArrived(const Atlas::Message::Object&);
    virtual void ObjectArrived(const Atlas::Objects::Operation::Login & op);
    virtual void ObjectArrived(const Atlas::Objects::Operation::Logout & op);
    virtual void ObjectArrived(const Atlas::Objects::Operation::Create & op);
    virtual void ObjectArrived(const Atlas::Objects::Operation::Imaginary & op);
    virtual void ObjectArrived(const Atlas::Objects::Operation::Move & op);
    virtual void ObjectArrived(const Atlas::Objects::Operation::Set & op);
    virtual void ObjectArrived(const Atlas::Objects::Operation::Touch & op);
    virtual void ObjectArrived(const Atlas::Objects::Operation::Look & op);
    virtual void ObjectArrived(const Atlas::Objects::Operation::Talk & op);
    virtual void ObjectArrived(const Atlas::Objects::Operation::Get & op);

  public:
    CommClient(CommServer & svr, int fd, int port);
    virtual ~CommClient();

    bool read() {
        if (codec != NULL) {
            codec->Poll();
            return false;
        } else {
            return negotiate();
        }
    }

    void send(const Atlas::Objects::Operation::RootOperation & op) {
        if (isOpen()) {
            //    std::fstream file(1);
            //    Atlas::Codecs::XML c(file, (Atlas::Bridge*)this);
            //    Atlas::Objects::Encoder enc(&c);
            //    enc.StreamMessage(op);
            //    std::cout << std::endl << flush;

            encoder->StreamMessage(&op);
            clientIos << std::flush;
            if (clientIos.timeout()) {
                std::cerr << "TIMOUT" << std::endl << std::flush;
                clientIos.close();
            }
        }
    }

    int peek() { return clientIos.peek(); }
    int eof() { return clientIos.eof(); }
    int getFd() { return clientIos.getSocket(); }
    bool isOpen() { return clientIos.is_open(); }
    bool online() { return (encoder != NULL); }
    void close() { clientIos.close(); }

    void message(const Atlas::Objects::Operation::RootOperation &);
    void setup();
};

#endif // SERVER_COMM_CLIENT_H

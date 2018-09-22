// Cyphesis Online RPG Server and AI Engine
// Copyright (C) 2000,2001 Alistair Riddoch
// Copyright (C) 2013 Erik Ogenvik
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA


#ifndef CLIENT_BASE_CLIENT_H
#define CLIENT_BASE_CLIENT_H

#include "ClientConnection.h"

class CreatorClient;

/// \brief Base class for classes that implement clients used to connect to a
/// cyphesis server
class BaseClient {
  protected:
    /// \brief Low level connection to the server
    ClientConnection m_connection;
    /// \brief Store for details of the account after login
    Atlas::Objects::Root m_player;
    /// \brief Name used for the username of the account and the name of avatars
    std::string m_playerName;
    /// \brief Identifier of the Account on the server after login
    std::string m_playerId;

    std::string m_username;
    std::string m_password;

    /**
     * Called when an operation is received from the server.
     *
     * @param op The operation.
     * @param res Any operations to be sent back.
     */
    virtual void operation(const Operation & op, OpVector & res) = 0;

    std::string getErrorMessage(const Operation & err);

  public:
    explicit BaseClient(boost::asio::io_service& io_service);
    virtual ~BaseClient() = default;

    const std::string & id() const {
        return m_playerId;
    }

    Atlas::Objects::Root createSystemAccount(const std::string& usernameSuffix = "");
    Atlas::Objects::Root createAccount(const std::string & name,
                                       const std::string & pword);
    CreatorClient * createCharacter(const std::string & name);
    void logout();
    int pollOne(const boost::posix_time::time_duration& duration);
    
    /// \brief Function called when nothing else is going on
    //virtual void idle() = 0;

    /// \brief Connect to a local server via a unix socket
    int connectLocal(const std::string & socket) {
        return m_connection.connectLocal(socket);
    }

    /// \brief Connect to a remote server using a network socket
    int connect(const std::string & server, int port) {
        return m_connection.connect(server, port);
    }

    /// \brief Send an operation to the server
    void send(const Atlas::Objects::Operation::RootOperation & op);

    int wait() {
        return m_connection.wait();
    }

    int sendAndWaitReply(const Operation & op, OpVector & res) {
        return m_connection.sendAndWaitReply(op, res);
    }

    int runTask(ClientTask * task, const std::string & arg);
    int endTask();

    /**
     * Checks if there's an active task.
     * @return True if there's a task set.
     */
    bool hasTask() const;

    /**
     * Poll the server until the current task has completed.
     * @return 0 if successful
     */
    int pollUntilTaskComplete();

};

#endif // CLIENT_BASE_CLIENT_H

#ifndef NICKCOMMAND_HPP
#define NICKCOMMAND_HPP

#include "ICommand.hpp"

class Server;

class NickCommand : public ICommand {
private:
    Server& _server;

public:
    NickCommand(Server& server);
    ~NickCommand();

    std::vector<std::string> execute(Client& client, const ParsedCommand& cmd);
};

#endif
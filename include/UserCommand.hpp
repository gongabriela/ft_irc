#ifndef USERCOMMAND_HPP
# define USERCOMMAND_HPP

# include "ICommand.hpp"
#include "Server.hpp"

class UserCommand : public ICommand {
    private:
        Server& _server;

    public:
        UserCommand(Server& server);
        ~UserCommand();

        std::vector<std::string> execute(Client& client, const ParsedCommand& cmd);
};

#endif
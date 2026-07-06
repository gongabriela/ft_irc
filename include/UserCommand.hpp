#ifndef USERCOMMAND_HPP
#define USERCOMMAND_HPP

#include "ICommand.hpp"

class UserCommand : public ICommand {
public:
    UserCommand();
    ~UserCommand();

    std::vector<std::string> execute(Client& client, const ParsedCommand& cmd);
};

#endif
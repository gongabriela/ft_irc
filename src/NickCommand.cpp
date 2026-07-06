#include "../include/NickCommand.hpp"
#include "../include/Server.hpp"
#include "../include/Replies.hpp"
#include <iostream>

NickCommand::NickCommand(Server& server) : _server(server) {}

NickCommand::~NickCommand() {}

std::vector<std::string> NickCommand::execute(Client& client, const ParsedCommand& cmd) {
    std::vector<std::string> replies;

    if (cmd.args.empty()) {
        replies.push_back(":server " ERR_NONICKNAMEGIVEN_CODE " * :" ERR_NONICKNAMEGIVEN_MSG);
        return replies;
    }

    std::string nickname = cmd.args[0];
    
    // TODO: add invalid chars verification (ERR_ERRONEUSNICKNAME)
    // TODO: add verification if the nick is already in use (ERR_NICKNAMEINUSE)

    client.setNickname(nickname);
    std::cout << "[NickCommand] Client FD " << client.getFd() << " set nickname to: " << nickname << std::endl;

    return replies;
}
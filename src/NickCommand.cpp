#include "../include/NickCommand.hpp"
#include "../include/Server.hpp"
#include "../include/Replies.hpp"
#include <iostream>

NickCommand::NickCommand(Server& server) : _server(server) {}

NickCommand::~NickCommand() {}

static bool isValidNickname(const std::string& nick) {
    if (nick.empty() || nick.find_first_of(" #:,*?!@.") != std::string::npos) {
        return false;
    }
    return true;
}

std::vector<std::string> NickCommand::execute(Client& client, const ParsedCommand& cmd) {
    
    std::vector<std::string> replies;

    if (cmd.args.empty()) {
        replies.push_back(_server.buildReply(ERR_NONICKNAMEGIVEN_CODE, "*", ERR_NONICKNAMEGIVEN_MSG));
        return replies;
    }

    std::string nickname = cmd.args[0];
    if (!isValidNickname(nickname)) {
        replies.push_back(_server.buildReply(ERR_ERRONEUSNICKNAME_CODE, nickname, ERR_ERRONEUSNICKNAME_MSG));
        return replies;
    }
    if (_server.isNicknameInUse(nickname)) {
        replies.push_back(_server.buildReply(ERR_NICKNAMEINUSE_CODE, nickname, ERR_NICKNAMEINUSE_MSG));
        return replies;
    }
    client.setNickname(nickname);
    std::cout << "[NickCommand] Client FD " << client.getFd() << " set nickname to: " << nickname << std::endl;

    if (!client.isAuthenticated() && client.hasPassword() && !client.getNickname().empty() && !client.getUsername().empty()) {
        client.setAuthenticated(true);
        replies.push_back(_server.buildReply(RPL_WELCOME_CODE, client.getNickname(), RPL_WELCOME_MSG + client.getNickname()));
        std::cout << "[Server] Client FD " << client.getFd() << " is now fully authenticated!" << std::endl;
    }

    return replies;
}
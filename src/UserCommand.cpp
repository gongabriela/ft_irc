#include "../include/UserCommand.hpp"
#include "../include/Replies.hpp"
#include <iostream>

UserCommand::UserCommand() {}

UserCommand::~UserCommand() {}

std::vector<std::string> UserCommand::execute(Client& client, const ParsedCommand& cmd) {
    std::vector<std::string> replies;

    // if already registered, cannot change the USER
    if (client.isAuthenticated()) {
        replies.push_back(":server " ERR_ALREADYREGISTRED_CODE " * :" ERR_ALREADYREGISTRED_MSG);
        return replies;
    }

    // USER command arguments: <user> <mode> <unused> <realname>
    if (cmd.args.size() < 4) {
        replies.push_back(":server " ERR_NEEDMOREPARAMS_CODE " USER :" ERR_NEEDMOREPARAMS_MSG);
        return replies;
    }

    client.setUsername(cmd.args[0]);
    
    client.setRealname(cmd.args[3]); 

    std::cout << "[UserCommand] Client FD " << client.getFd() << " registered as " << cmd.args[0] << std::endl;

    if (!client.isAuthenticated() && client.hasPassword() && !client.getNickname().empty() && !client.getUsername().empty()) {
        client.setAuthenticated(true);
        replies.push_back(":server " RPL_WELCOME_CODE " " + client.getNickname() + " :" RPL_WELCOME_MSG + client.getNickname());
        std::cout << "[Server] Client FD " << client.getFd() << " is now fully authenticated!" << std::endl;
    }
    // IRC Protocol does not require the server to reply in the case that the user is not authenticated correctly
    return replies;
}
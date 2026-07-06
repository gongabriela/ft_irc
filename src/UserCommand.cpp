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

    // TODO: verify if client has all required information (PASS, NICK, USER)
    // If so, call client.setAuthenticated(true) and send welcome message (001)

    return replies;
}
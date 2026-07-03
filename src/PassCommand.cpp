#include "PassCommand.hpp"
#include "Server.hpp"
#include <iostream>

/**
 * @brief Constructs the PassCommand with a reference to the Server.
 * @param server The main server instance, used to validate the connection password.
 */
PassCommand::PassCommand(Server& server) : _server(server) {}

/**
 * @brief Destructor for PassCommand.
 */
PassCommand::~PassCommand() {}

/**
 * @brief Executes the PASS command logic.
 * * Validates the password provided by the client against the server's password.
 * According to RFC 2812:
 * - ERR_NEEDMOREPARAMS (461) if no password is provided.
 * - ERR_ALREADYREGISTRED (462) if the client is already authenticated.
 * - ERR_PASSWDMISMATCH (464) if the password is incorrect.
 * * @param client The client attempting to set the password.
 * @param cmd The parsed command containing the arguments.
 * @return std::vector<std::string> A list of IRC numeric replies if errors occur.
 */
std::vector<std::string> PassCommand::execute(Client& client, const ParsedCommand& cmd) {
    std::vector<std::string> replies;

    // 1. Check if the client is already fully authenticated
    if (client.isAuthenticated()) {
        replies.push_back(":server 462 * :Unauthorized command (already registered)");
        return replies;
    }

    // 2. Check if the password argument was provided
    if (cmd.args.empty()) {
        replies.push_back(":server 461 * PASS :Not enough parameters");
        return replies;
    }

    // 3. Validate the password
    if (cmd.args[0] == _server.getPassword()) {
        client.setHasPassword(true);
        std::cout << "[PassCommand] Client FD " << client.getFd() << " provided the correct password." << std::endl;
    } else {
        replies.push_back(":server 464 * :Password incorrect");
        std::cout << "[PassCommand] Client FD " << client.getFd() << " provided an incorrect password." << std::endl;
    }

    return replies;
}
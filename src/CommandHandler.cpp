/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:19:34 by ggoncalv          #+#    #+#             */
/*   Updated: 2026/07/03 14:43:27 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/CommandHandler.hpp"
#include "../include/Server.hpp"
#include "../include/PassCommand.hpp"
#include <iostream>

/**
 * @brief Constructs the CommandHandler and initializes the command registry.
 * @param server Reference to the main IRC server to access global configurations (e.g., password).
 */
CommandHandler::CommandHandler(Server& server) : _server(server) {
    _commands["PASS"] = new PassCommand(server);
}

/**
 * @brief Destructor that cleans up dynamically allocated command objects from the heap.
 */
CommandHandler::~CommandHandler() {
    std::map<std::string, ICommand*>::iterator it;
    for (it = _commands.begin(); it != _commands.end(); ++it) {
        delete it->second;
    }
    _commands.clear();
}

/**
 * @brief Routes the parsed command to the appropriate command execution class.
 * @param client The user who triggered the command.
 * @param cmd The parsed data from the network.
 * @return std::vector<std::string> The generated IRC responses to queue for the client.
 */
std::vector<std::string> CommandHandler::execute(Client& client, const ParsedCommand& cmd) {
    std::vector<std::string> replies;

    if (cmd.command.empty()) {
        return replies;
    }

    std::map<std::string, ICommand*>::iterator it = _commands.find(cmd.command);
    
    if (it != _commands.end()) {
        replies = it->second->execute(client, cmd);
    } else {
        std::cout << "[CommandHandler] Unknown command received: " << cmd.command << std::endl;
    }

    return replies;
}
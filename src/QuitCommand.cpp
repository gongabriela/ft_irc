/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 15:23:55 by ggoncalv          #+#    #+#             */
/*   Updated: 2026/08/08 16:17:05 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/QuitCommand.hpp"
// #include "../include/Replies.hpp"
#include <iostream>

QuitCommand::QuitCommand() {}
QuitCommand::~QuitCommand() {}

/**
 * @brief Executes the QUIT command logic.
 * Flags the client for safe disconnection at the end of the server's read cycle
 * to prevent mid-loop memory invalidation (Segfaults).
 * @param client The client requesting to disconnect.
 * @param cmd The parsed command containing an optional quit message.
 * @return An empty vector (replies are handled during the disconnect process).
 */
std::vector<std::string> QuitCommand::execute(Client &client, const ParsedCommand &cmd)
{
    std::vector<std::string> replies;

    std::string reason = "Leaving";
    if (!cmd.args.empty()) {
        reason = "";
        for (size_t i = 0; i < cmd.args.size(); ++i) {
            reason += cmd.args[i];
            if (i < cmd.args.size() - 1)
                reason += " ";
        }
    }

    std::string errorMsg = BRED "Closing Link: " + client.getNickname() + " (" + reason + ")" NC;
    client.queueMessage(errorMsg);
    client.setQuitReason(reason);
    client.setPendingDisconnect(true);

    std::cout << BCYN "[QuitCommand] " << client.getNickname() << " is disconnecting." << NC << std::endl;

    return replies;
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 15:09:23 by ggoncalv          #+#    #+#             */
/*   Updated: 2026/08/08 15:23:50 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PingCommand.hpp"
#include "../include/Replies.hpp"
#include "../include/Server.hpp"

PingCommand::PingCommand(Server& server) : _server(server) {}
PingCommand::~PingCommand() {}

std::vector<std::string> PingCommand::execute(Client& client, const ParsedCommand& cmd) {

    std::vector<std::string> replies;

    if (cmd.args.empty()) {
        replies.push_back(_server.buildReply(ERR_NOORIGIN_CODE, client.getNickname(), "", ERR_NOORIGIN_MSG));
        return replies;
    }

    std::string token = cmd.args[0];
    std::string pongResponse = ":" + _server.getName() + " PONG " + _server.getName() + " :" + token;
    std::cout << "[PingCommand] Ping received, sending PONG, received PING from FD " << client.getFd() << std::endl;
    replies.push_back(pongResponse);

    return replies;
}
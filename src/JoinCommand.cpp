/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 07:22:00 by ggoncalv          #+#    #+#             */
/*   Updated: 2026/07/07 07:41:07 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/JoinCommand.hpp"
#include "../include/Channel.hpp"

JoinCommand::JoinCommand(Server& server) : _server(server) {}

JoinCommand::~JoinCommand() {}

std::vector<std::string> JoinCommand::execute(Client& client, const ParsedCommand& cmd) {
    std::vector<std::string> responses;

    if (cmd.args.empty()) {
        return responses;
    }

    std::string channelName = cmd.args[0];

    if (channelName.empty() || channelName[0] != '#') {
        return responses;
    }

    Channel* channel = _server.getChannel(channelName);

    if (channel == NULL) {
        channel = new Channel(channelName);
        _server.addChannel(channelName, channel);
        channel->addMember(&client);
        channel->addOperator(&client);
    } 
    else {
        channel->addMember(&client);
    }

    // TODO step 4: send confirmation messages and channel member list
    
    return responses;
}


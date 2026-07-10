/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 16:59:47 by ggoncalv          #+#    #+#             */
/*   Updated: 2026/07/10 20:54:58 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/JoinCommand.hpp"
#include "../include/Replies.hpp"
#include "../include/Channel.hpp"

JoinCommand::JoinCommand(Server& server) : _server(server) {}

JoinCommand::~JoinCommand() {}

/**
 * @brief Executes the JOIN command.
 * Validates the channel name, assigns the client to the channel, and formats the appropriate success or error replies.
 * @param client The client requesting to join.
 * @param cmd The parsed command data containing the target channel.
 * @return A vector of formatted IRC replies to be sent back to the client.
 */
std::vector<std::string> JoinCommand::execute(Client& client, const ParsedCommand& cmd) {
    
    std::vector<std::string> responses;

    if (cmd.args.empty()) {
        responses.push_back(_server.buildReply(ERR_NEEDMOREPARAMS_CODE, client.getNickname(), "JOIN", ERR_NEEDMOREPARAMS_MSG));
        return responses;
    }

    std::string channelName = cmd.args[0];
    if (!isValidChannelName(channelName)) {
        responses.push_back(_server.buildReply(ERR_NOSUCHCHANNEL_CODE, client.getNickname(), channelName, ERR_NOSUCHCHANNEL_MSG));
        return responses;
    }
    Channel* channel = getOrCreateChannel(channelName, client);

    formatJoinResponses(client, channel, channelName, responses);
    std::string joinNotification = ":" + client.getPrefix() + " JOIN :" + channelName;
    channel->broadcast(joinNotification, &client);
    return responses;
}

/**
 * @brief Validates if the provided channel name strictly follows the IRC protocol prefix rules.
 * @param name The channel name to evaluate.
 * @return true if valid (starts with '#' or '&'), false otherwise.
 */
bool JoinCommand::isValidChannelName(const std::string& name) const {
    return (!name.empty() && (name[0] == '#' || name[0] == '&'));
}

/**
 * @brief Retrieves an existing channel or creates a new one in the server.
 * If created, the initiating client is automatically granted operator privileges.
 * @param channelName The name of the channel.
 * @param client The client joining the channel.
 * @return A pointer to the requested Channel instance.
 */
Channel* JoinCommand::getOrCreateChannel(const std::string& channelName, Client& client) {
    
    Channel* channel = _server.getChannel(channelName);

    if (channel == NULL) {
        channel = new Channel(channelName);
        _server.addChannel(channelName, channel);
        channel->addMember(&client);
        channel->addOperator(&client);
    } else {
        channel->addMember(&client);
    }
    
    return channel;
}

/**
 * @brief Constructs the sequence of success replies required by RFC 2812 upon joining a channel.
 * This includes the JOIN confirmation mask, the RPL_NAMREPLY (353), and RPL_ENDOFNAMES (366).
 * @param client The client joining.
 * @param channel The channel joined.
 * @param channelName The exact string name of the channel.
 * @param responses The vector where formatted replies will be appended.
 */
void JoinCommand::formatJoinResponses(Client& client, Channel* channel, const std::string& channelName, std::vector<std::string>& responses) const {
    
    std::string clientNick = client.getNickname();
    responses.push_back(":" + client.getPrefix() + " JOIN :" + channelName);

    std::string membersList = "";
    const std::vector<Client*>& members = channel->getMembers();
    for (size_t i = 0; i < members.size(); ++i) {
        if (channel->isOperator(members[i])) {
            membersList += "@";
        }
        membersList += members[i]->getNickname();
        if (i < members.size() - 1) {
            membersList += " ";
        }
    }

    responses.push_back(_server.buildReply(RPL_NAMREPLY_CODE, clientNick, "= " + channelName, membersList));
    responses.push_back(_server.buildReply(RPL_ENDOFNAMES_CODE, clientNick, channelName, RPL_ENDOFNAMES_MSG));
}
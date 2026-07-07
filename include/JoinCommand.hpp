/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 07:21:18 by ggoncalv          #+#    #+#             */
/*   Updated: 2026/07/07 16:56:58 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOINCOMMAND_HPP
#define JOINCOMMAND_HPP

#include "ICommand.hpp"
#include "Server.hpp"

/**
 * @brief Handles the IRC JOIN command.
 * Allows a client to start listening to a specific channel, creating it if it does not exist.
 */
class JoinCommand : public ICommand {
    private:
        Server& _server;

        bool isValidChannelName(const std::string& name) const;
        Channel* getOrCreateChannel(const std::string& channelName, Client& client);
        void formatJoinResponses(Client& client, Channel* channel, const std::string& channelName, std::vector<std::string>& responses) const;

    public:
        JoinCommand(Server& server);
        ~JoinCommand();

        std::vector<std::string> execute(Client& client, const ParsedCommand& cmd);
};

#endif
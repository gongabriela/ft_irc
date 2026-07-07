/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 07:21:18 by ggoncalv          #+#    #+#             */
/*   Updated: 2026/07/07 07:51:28 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOINCOMMAND_HPP
#define JOINCOMMAND_HPP

#include "ICommand.hpp"
#include "Server.hpp"

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
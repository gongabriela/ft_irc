/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 15:09:06 by ggoncalv          #+#    #+#             */
/*   Updated: 2026/08/08 15:11:43 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PINGCOMMAND_HPP
#define PINGCOMMAND_HPP

#include "ICommand.hpp"
#include "Server.hpp"

class PingCommand : public ICommand {
    private:
        Server& _server;

    public:
        PingCommand(Server& server);
        ~PingCommand();
        std::vector<std::string> execute(Client& client, const ParsedCommand& cmd);
};

#endif
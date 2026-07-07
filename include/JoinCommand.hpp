/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 07:21:18 by ggoncalv          #+#    #+#             */
/*   Updated: 2026/07/07 07:21:46 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOINCOMMAND_HPP
#define JOINCOMMAND_HPP

#include "ICommand.hpp"
#include "Server.hpp"

class JoinCommand : public ICommand {
private:
    Server& _server;

public:
    JoinCommand(Server& server);
    ~JoinCommand();

    std::vector<std::string> execute(Client& client, const ParsedCommand& cmd);
};

#endif
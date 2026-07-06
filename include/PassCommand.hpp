/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 14:42:00 by ggoncalv          #+#    #+#             */
/*   Updated: 2026/07/03 14:42:24 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASSCOMMAND_HPP
#define PASSCOMMAND_HPP

#include "ICommand.hpp"

class Server;

class PassCommand : public ICommand {
private:
    Server& _server;

public:
    PassCommand(Server& server);
    ~PassCommand();

    std::vector<std::string> execute(Client& client, const ParsedCommand& cmd);
};

#endif
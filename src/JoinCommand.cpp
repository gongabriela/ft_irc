/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 07:22:00 by ggoncalv          #+#    #+#             */
/*   Updated: 2026/07/07 07:24:17 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JoinCommand.hpp"

JoinCommand::JoinCommand(Server& server) : _server(server) {}

JoinCommand::~JoinCommand() {}

std::vector<std::string> JoinCommand::execute(Client& client, const ParsedCommand& cmd) {
    std::vector<std::string> responses;
    (void)client;
    (void)cmd;   
    return responses;
}
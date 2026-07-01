/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-alm <alde-alm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 12:57:59 by alde-alm          #+#    #+#             */
/*   Updated: 2026/07/01 12:58:02 by alde-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Irc.hpp"
#include "Poller.hpp"
#include "Client.hpp"
#include "Parser.hpp"
#include "CommandHandler.hpp"

class Server
{
private:
	int _port;
	std::string _password;
	int _serverFd;

	Poller poller;					  // Integrated Poller - manages all FDs
	std::map<int, Client *> _clients; // map of fd to Client pointer

	void initSocket();												 // Create, configure and put the socket (FD) into listen
	void acceptNewClient();											 // Accept new connections
	void handleRead(int fd, Parser &parser, CommandHandler &handle); // Handle reading data
	void handleWrite(int fd);										 // Handle sending data
	void disconnectClient(int fd);									 // Remove clients, close FD and clean up

public:
	Server(int port, const std::string &password);
	~Server();

	void runIrc();
};

#endif
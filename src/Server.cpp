/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-alm <alde-alm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 12:56:39 by alde-alm          #+#    #+#             */
/*   Updated: 2026/07/01 12:57:06 by alde-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port, const std::string &password)
	: _port(port), _password(password), _serverFd(-1)
{
	initSocket();
}

Server::~Server()
{
	if (_serverFd != -1)
		close(_serverFd);
	std::map<int, Client *>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it)
	{
		close(it->first);  // Socket's fd
		delete it->second; // Client's object pointer
	}
}

void Server::initSocket()
{
	_serverFd = socket(AF_INET, SOCK_STREAM, 0); // TCP (SOCK_STREAM) IPv4 (AF_INET), 0 = default protocol
	if (_serverFd < 0)
		throw std::runtime_error("Can't creat a socket!");
	// Syscall that sets the properties of a file descriptor. Makes the socket non-blocking
	if (fcntl(_serverFd, F_SETFL, O_NONBLOCK) < 0) // Set FD flags (F_SETFL) to include O_NONBLOCK
		throw std::runtime_error("Fcntl failed");
	int opt = 1; // Enable the option
	// Syscall that sets special socket options.
	if (setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) //(SO_REUSEADDR) Allows reusing the port immediately after the server closes, avoiding "address already in use" errors
		throw std::runtime_error("setsockopt failed");

	sockaddr_in address; // IPv4 address structure, required for bind()
	std::memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;				 // IPv4 addresses
	address.sin_addr.s_addr = htonl(INADDR_ANY); // Set IP address
	address.sin_port = htons(_port);			 // Set port

	// Bind the socket (_serverFd) to the IP address + port (addr)
	if (bind(_serverFd, (sockaddr *)&address, sizeof(address)) < 0)
		throw std::runtime_error("bind failed");
	// Turn the TCP socket (_serverFd) into a passive socket that listens for client connections (TCP server)
	if (listen(_serverFd, SOMAXCONN) < 0) // Backlog of maximum pending connections before refusing new ones
		throw std::runtime_error("listen failed");
	// Add the server socket FD to the event loop
	poller.add(_serverFd, POLLIN); // (POLLIN) - notify when there's a new connection
	std::cout << BGRN "Server listening on port " BYEL << _port << NC << std::endl;
}

void Server::runIrc()
{
	Parser parser;
	CommandHandler handler(*this);

	while (true)
	{
		poller.wait(); // Single poll() of the project. Wait until some FD has an event
		for (size_t i = 0; i < poller.size(); ++i)
		{
			pollfd &pfd = poller[i];
			// If the current FD is _serverFd and revents contains POLLIN, a client is trying to connect
			if (pfd.fd == _serverFd && (pfd.revents & POLLIN))
			{
				acceptNewClient();
				continue; // Skip to the next FD
			}
			if (pfd.revents & POLLIN) // Read - detects data received from a client
				handleRead(pfd.fd, parser, handler);
			if (pfd.revents & POLLOUT) // Write - detects that the socket is ready to send
				handleWrite(pfd.fd);
			if (pfd.revents & (POLLHUP | POLLERR | POLLNVAL)) // Detect errors and disconnections
				disconnectClient(pfd.fd);
		}
	}
}

void Server::acceptNewClient()
{
	while (true)
	{
		int clientFd = accept(_serverFd, NULL, NULL);
		if (clientFd < 0)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break;
			std::cerr << BRED "accept error: " << std::strerror(errno) << NC << std::endl;
			break;
		}
		if (fcntl(clientFd, F_SETFL, O_NONBLOCK) < 0)
		{
			std::cerr << BRED "fcntl failed on client" << NC << std::endl;
			close(clientFd);
			continue;
		}
		Client *client = new Client(clientFd);
		_clients[clientFd] = client;
		poller.add(clientFd, POLLIN);
		std::cout << BYEL "New client connected: fd=" << BBLU << clientFd << NC << std::endl;
	}
}

void Server::handleRead(int fd, Parser &parser, CommandHandler &handler)
{
	Client *client = _clients[fd];
	char buffer[1024];

	std::memset(buffer, 0, sizeof(buffer));
	int bytes = recv(fd, buffer, sizeof(buffer), 0);
	if (bytes <= 0)
	{
		disconnectClient(fd);
		return;
	}
	client->appendToRecvBuffer(std::string(buffer, bytes));

	while (client->hasCompleteLine())
	{
		std::string line = client->extractLine();

		//========= Conection with B ============
		ParsedCommand cmd = parser.parse(line); // Component B
		std::vector<std::string> replies = handler.execute(*client, cmd);
		// Returnes a complete formatted response.
		//=======================================

		for (size_t i = 0; i < replies.size(); ++i)
			client->queueMessage(replies[i]);
		poller.enable(fd, POLLOUT);
	}
}

void Server::handleWrite(int fd)
{
	Client *client = _clients[fd];
	std::string &out = client->getSendBuffer();

	if (out.empty())
	{
		poller.disable(fd, POLLOUT);
		return;
	}
	int bytes = send(fd, out.c_str(), out.size(), 0);
	if (bytes <= 0)
	{
		disconnectClient(fd);
		return;
	}
	out.erase(0, bytes);
	if (out.empty())
		poller.disable(fd, POLLOUT);
}

void Server::disconnectClient(int fd)
{
	std::cout << BMAG "Disconnecting client fd=" << fd << NC << std::endl;
	poller.remove(fd);
	std::map<int, Client *>::iterator it = _clients.find(fd);
	if (it != _clients.end())
	{
		delete it->second;
		_clients.erase(it);
	}
	close(fd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-alm <alde-alm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 12:58:07 by alde-alm          #+#    #+#             */
/*   Updated: 2026/07/01 12:58:30 by alde-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int fd) : _fd(fd) {}

Client::~Client() {}

int Client::getFd() const
{
	return _fd;
}
// Input: data received from the socket
void Client::appendToRecvBuffer(const std::string &data)
{
	_recvBuffer += data;
}

bool Client::hasCompleteLine() const
{
	return _recvBuffer.find('\n') != std::string::npos; // An IRC line ends with '\n' (may have '\r' before)
}

std::string Client::extractLine()
{
	std::string::size_type pos = _recvBuffer.find('\n');
	std::string line = _recvBuffer.substr(0, pos);		// Extract up to the '\n'
	if (!line.empty() && line[line.size() - 1] == '\r') // Remove '\r' if present
		line.erase(line.size() - 1);
	_recvBuffer.erase(0, pos + 1); // Remove the line from the buffer
	return line;
}
// Output: data to send to the client
void Client::queueMessage(const std::string &msg)
{
	_sendBuffer += msg + "\r\n"; // The IRC protocol requires CRLF
}

bool Client::hasDataToSend() const
{
	return !_sendBuffer.empty();
}

std::string &Client::getSendBuffer()
{
	return _sendBuffer;
}
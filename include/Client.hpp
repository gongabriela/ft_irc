/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-alm <alde-alm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 12:57:24 by alde-alm          #+#    #+#             */
/*   Updated: 2026/07/01 12:57:29 by alde-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Irc.hpp"

class Client
{
private:
	int _fd;
	std::string _recvBuffer;
	std::string _sendBuffer;

public:
	Client(int fd);
	~Client();

	int getFd() const;

	// ======== Input ========
	void appendToRecvBuffer(const std::string &data);
	bool hasCompleteLine() const;
	std::string extractLine();

	// ======== Output ========
	void queueMessage(const std::string &msg);
	bool hasDataToSend() const;
	std::string &getSendBuffer();
};

#endif
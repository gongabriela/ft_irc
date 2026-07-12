/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 15:22:27 by ggoncalv          #+#    #+#             */
/*   Updated: 2026/07/11 15:15:41 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
#define REPLIES_HPP

#include <string>

/**
 * @file Replies.hpp
 * @brief Defines standard IRC numeric reply codes and messages according to RFC 2812.
 * Serves as a single source of truth for protocol-specific static strings.
 */
 
#define ERR_NEEDMOREPARAMS_CODE "461"
#define ERR_NEEDMOREPARAMS_MSG "Not enough parameters"

#define ERR_ALREADYREGISTRED_CODE "462"
#define ERR_ALREADYREGISTRED_MSG "Unauthorized command (already registered)"

#define ERR_PASSWDMISMATCH_CODE "464"
#define ERR_PASSWDMISMATCH_MSG "Password incorrect"

#define ERR_UNKNOWNCOMMAND_CODE "421"
#define ERR_UNKNOWNCOMMAND_MSG "Unknown command"

// === NICK ====
#define ERR_NONICKNAMEGIVEN_CODE "431"
#define ERR_NONICKNAMEGIVEN_MSG "No nickname given"

#define ERR_ERRONEUSNICKNAME_CODE "432"
#define ERR_ERRONEUSNICKNAME_MSG "Erroneous nickname"

#define ERR_NICKNAMEINUSE_CODE "433"
#define ERR_NICKNAMEINUSE_MSG "Nickname is already in use"

// === welcome message === 

#define RPL_WELCOME_CODE "001"
#define RPL_WELCOME_MSG "Welcome to the ft_irc Network, "

// === JOIN ====
#define ERR_NOSUCHCHANNEL_CODE "403"
#define ERR_NOSUCHCHANNEL_MSG "No such channel"

#define RPL_NAMREPLY_CODE "353"

#define RPL_ENDOFNAMES_CODE "366"
#define RPL_ENDOFNAMES_MSG "End of /NAMES list"

// === unauth error ===
#define ERR_NOTREGISTERED_CODE "451"
#define ERR_NOTREGISTERED_MSG "You have not registered"

// === PRIVMSG ====
#define ERR_NOSUCHNICK_CODE "401"
#define ERR_NOSUCHNICK_MSG "No such nick/channel"

#define ERR_CANNOTSENDTOCHAN_CODE "404"
#define ERR_CANNOTSENDTOCHAN_MSG "Cannot send to channel"

#define ERR_NORECIPIENT_CODE "411"
#define ERR_NORECIPIENT_MSG "No recipient given (PRIVMSG)"

#define ERR_NOTEXTTOSEND_CODE "412"
#define ERR_NOTEXTTOSEND_MSG "No text to send"

// === PART ====
#define ERR_NOTONCHANNEL_CODE "442"
#define ERR_NOTONCHANNEL_MSG "You're not on that channel"

#endif
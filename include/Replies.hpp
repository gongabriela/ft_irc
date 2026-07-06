/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 15:22:27 by ggoncalv          #+#    #+#             */
/*   Updated: 2026/07/06 11:05:58 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLIES_HPP
#define REPLIES_HPP

#include <string>

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

#endif
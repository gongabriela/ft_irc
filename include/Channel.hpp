/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 16:04:31 by ggoncalv          #+#    #+#             */
/*   Updated: 2026/07/15 09:55:57 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"
# include <string>
# include <vector>
# include <algorithm>

/**
 * @brief Represents an IRC channel.
 * * Manages channel properties like name and topic, as well as its 
 * participants (standard members and operators).
 */
class Channel {
    private:
        std::string _name;
        std::string _topic;
        std::vector<Client*> _members;
        std::vector<Client*> _operators;
        std::vector<std::string> _invitedNicks;

    public:
        Channel(const std::string& name);
        ~Channel();

        const std::string& getName() const;
        const std::string& getTopic() const;
        
        void setTopic(const std::string& topic);

        bool isMember(Client* client) const;
        void addMember(Client* client);
        bool isOperator(Client* client) const;
        void addOperator(Client* client);

        const std::vector<Client*>& getMembers() const;
        const std::vector<Client*>& getOperators() const;

        void broadcast(const std::string& message, Client* sender);

        void removeMember(Client* client);
        void removeOperator(Client* client);
        bool isEmpty() const;

        void invite(const std::string& nickname);
        bool isInvited(const std::string& nickname) const;
    };

#endif
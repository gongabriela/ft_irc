#include "Channel.hpp"
#include <algorithm>

Channel::Channel(const std::string& name) : _name(name) {}

Channel::~Channel() {}

/**
 * @brief Gets the channel's name.
 * @return The name of the channel.
 */
const std::string& Channel::getName() const {
    return _name;
}

/**
 * @brief Gets the channel's current topic.
 * @return The topic string.
 */
const std::string& Channel::getTopic() const {
    return _topic;
}

/**
 * @brief Sets or updates the channel's topic.
 * @param topic The new topic string.
 */
void Channel::setTopic(const std::string& topic) {
    _topic = topic;
}

/**
 * @brief Checks if a client is present in the channel.
 * @param client Pointer to the client to check.
 * @return true if the client is a member, false otherwise.
 */
bool Channel::isMember(Client* client) const {
    return std::find(_members.begin(), _members.end(), client) != _members.end();
}

/**
 * @brief Adds a client to the channel if not already a member.
 * @param client Pointer to the client to add.
 */
void Channel::addMember(Client* client) {
    if (!isMember(client)) {
        _members.push_back(client);
    }
}

/**
 * @brief Checks if a client has operator privileges in the channel.
 * @param client Pointer to the client to check.
 * @return true if the client is an operator, false otherwise.
 */
bool Channel::isOperator(Client* client) const {
    return std::find(_operators.begin(), _operators.end(), client) != _operators.end();
}

/**
 * @brief Grants operator privileges to a client.
 * @param client Pointer to the client to promote.
 */
void Channel::addOperator(Client* client) {
    if (!isOperator(client)) {
        _operators.push_back(client);
    }
}

/**
 * @brief Retrieves the list of all members in the channel.
 * @return A constant reference to the vector of member clients.
 */
const std::vector<Client*>& Channel::getMembers() const {
    return _members;
}

/**
 * @brief Retrieves the list of all operators in the channel.
 * @return A constant reference to the vector of operator clients.
 */
const std::vector<Client*>& Channel::getOperators() const {
    return _operators;
}
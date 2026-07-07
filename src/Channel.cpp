#include "Channel.hpp"
#include <algorithm>

Channel::Channel(const std::string& name) : _name(name) {}

Channel::~Channel() {}

const std::string& Channel::getName() const {
    return _name;
}

const std::string& Channel::getTopic() const {
    return _topic;
}

void Channel::setTopic(const std::string& topic) {
    _topic = topic;
}

bool Channel::isMember(Client* client) const {
    return std::find(_members.begin(), _members.end(), client) != _members.end();
}

void Channel::addMember(Client* client) {
    if (!isMember(client)) {
        _members.push_back(client);
    }
}

bool Channel::isOperator(Client* client) const {
    return std::find(_operators.begin(), _operators.end(), client) != _operators.end();
}

void Channel::addOperator(Client* client) {
    if (!isOperator(client)) {
        _operators.push_back(client);
    }
}

const std::vector<Client*>& Channel::getMembers() const {
    return _members;
}

const std::vector<Client*>& Channel::getOperators() const {
    return _operators;
}
#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Client.hpp"
#include <string>
#include <vector>
#include <algorithm>

class Channel {
private:
    std::string _name;
    std::string _topic;
    std::vector<Client*> _members;
    std::vector<Client*> _operators;

public:
    Channel(const std::string& name);
    ~Channel();

    const std::string& getName() const;
    const std::string& getTopic() const;
    
    void setTopic(const std::string& topic);

};

#endif
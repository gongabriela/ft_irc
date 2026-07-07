#include "JoinCommand.hpp"
#include "Replies.hpp"

JoinCommand::JoinCommand(Server& server) : _server(server) {}

JoinCommand::~JoinCommand() {}

std::vector<std::string> JoinCommand::execute(Client& client, const ParsedCommand& cmd) {
    
    std::vector<std::string> responses;

    if (cmd.args.empty()) {
        responses.push_back(_server.buildReply(ERR_NEEDMOREPARAMS_CODE, client.getNickname(), "JOIN", ERR_NEEDMOREPARAMS_MSG));
        return responses;
    }

    std::string channelName = cmd.args[0];
    if (!isValidChannelName(channelName)) {
        responses.push_back(_server.buildReply(ERR_NOSUCHCHANNEL_CODE, client.getNickname(), channelName, ERR_NOSUCHCHANNEL_MSG));
        return responses;
    }
    Channel* channel = getOrCreateChannel(channelName, client);

    formatJoinResponses(client, channel, channelName, responses);
    return responses;
}

bool JoinCommand::isValidChannelName(const std::string& name) const {
    return (!name.empty() && (name[0] == '#' || name[0] == '&'));
}

Channel* JoinCommand::getOrCreateChannel(const std::string& channelName, Client& client) {
    
    Channel* channel = _server.getChannel(channelName);

    if (channel == NULL) {
        channel = new Channel(channelName);
        _server.addChannel(channelName, channel);
        channel->addMember(&client);
        channel->addOperator(&client);
    } else {
        channel->addMember(&client);
    }
    
    return channel;
}

void JoinCommand::formatJoinResponses(Client& client, Channel* channel, const std::string& channelName, std::vector<std::string>& responses) const {
    
    std::string clientNick = client.getNickname();
    responses.push_back(":" + client.getPrefix() + " JOIN :" + channelName);

    std::string membersList = "";
    const std::vector<Client*>& members = channel->getMembers();
    for (size_t i = 0; i < members.size(); ++i) {
        if (channel->isOperator(members[i])) {
            membersList += "@";
        }
        membersList += members[i]->getNickname();
        if (i < members.size() - 1) {
            membersList += " ";
        }
    }

    responses.push_back(_server.buildReply(RPL_NAMREPLY_CODE, clientNick, "= " + channelName, membersList));
    responses.push_back(_server.buildReply(RPL_ENDOFNAMES_CODE, clientNick, channelName, RPL_ENDOFNAMES_MSG));
}
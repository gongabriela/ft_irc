/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 19:05:44 by ggoncalv          #+#    #+#             */
/*   Updated: 2026/06/20 19:16:25 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib> 
#include <string>

int main(int argc, char **argv) {

    if (argc != 3) {
        std::cerr << "Error: invalid number of arguments." << std::endl;
        std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
        return 1;
    }

    int port = std::atoi(argv[1]);
    if (port < 1024 || port > 65535) {
        std::cerr << "Error: port must be a number between 1024 and 65535." << std::endl;
        return 1;
    }

    std::string password = argv[2];
    if (password.empty()) {
        std::cerr << "Error: password cannot be empty." << std::endl;
        return 1;
    }

    std::cout << "Server starting on port: " << port << std::endl;
    std::cout << "Password set to: " << password << std::endl;

    return 0;
}
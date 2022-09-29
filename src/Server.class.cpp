#include "../includes/Server.class.hpp"

Server::Server(AReporter & logger) : Server(logger, SERVER_DEFAULT_PORT) {}

Server::Server(AReporter & logger, port_t portNo) : _logger(logger), _portNo(portNo) {}

Server::Server(Server const & src) : _logger(src.getLogger()) {
    *this = src;
    return ;
}

Server::~Server(void) {}

Server & Server::operator=(Server const & rhs) {
    if (this == &rhs)
        return *this;
    
    this->_portNo = rhs.getPortNo();
    this->_logger = rhs.getLogger();
    return *this;
}

port_t Server::getPortNo(void) const {
    return this->_portNo;
}

AReporter & Server::getLogger(void) const {
    return this->_logger;
}

/**
 * @brief Run the TCP server.
 * 
 * Further info: https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/
 * 
 */
void Server::run(void) {
    int opt = true;

    int master_socket = socket(AF_INET, SOCK_STREAM, 0);
    int client_sockets[SERVER_MAX_CLIENT];

	char buffer[1024];
    std::string sbuffer;
	fd_set readfds;

    buffer[0] = 0;

    int sd, max_sd, activity, new_socket, nbytes;

    for (uint8_t i = 0; i < SERVER_MAX_CLIENT; i++)
        client_sockets[i] = 0;

    if (master_socket == -1) {
        this->_logger.error("Failed to create socket. errno: " + std::string(strerror(errno)));
        return ;
    }

    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0) {
		this->_logger.error("Cannot allow multiple connection. errno: " + std::string(strerror(errno)));
		return ;
	}

    sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    sockaddr.sin_port = htons(this->getPortNo());

    if (bind(master_socket, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
        this->_logger.error("Failed to bind to port " \
                                + std::to_string(this->getPortNo()) \
                                + ". errno: " + std::string(strerror(errno)));
        return ;
    }

    if (listen(master_socket, SERVER_MAX_CLIENT) < 0) {
        this->_logger.error("Failed to listen on socket. errno: " + std::string(strerror(errno)));
        return ;
    }

    // Grab a connection from the queue
    auto addrlen = sizeof(sockaddr);

    do {
        
        //clear the socket set
		FD_ZERO(&readfds);
	
		//add master socket to set
		FD_SET(master_socket, &readfds);
		max_sd = master_socket;

        //add child sockets to set
		for (uint8_t i = 0 ; i < SERVER_MAX_CLIENT ; i++)
		{
			//socket descriptor
			sd = client_sockets[i];
				
			//if valid socket descriptor then add to read list
			if(sd > 0)
				FD_SET( sd , &readfds);
				
			//highest file descriptor number, need it for the select function
			if(sd > max_sd)
				max_sd = sd;
		}
	
		//wait for an activity on one of the sockets , timeout is NULL ,
		//so wait indefinitely
		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

        if ((activity < 0) && (errno!=EINTR)) {
			this->_logger.error("Select failed. errno: " + std::string(strerror(errno)));
            return ;
		}

        //If something happened on the master socket ,
		//then its an incoming connection
		if (FD_ISSET(master_socket, &readfds))
		{
			if ((new_socket = accept(master_socket, \
                    (struct sockaddr *)&sockaddr, (socklen_t*)&addrlen))<0) {
                this->_logger.error("Failed to grab connection. errno: " \
                                        + std::string(strerror(errno)));
				return ;
			}

			//add new socket to array of sockets
			for (uint8_t i = 0; i < SERVER_MAX_CLIENT; i++)
			{
				//if position is empty
				if( client_sockets[i] == 0 ) {
					client_sockets[i] = new_socket;
					goto accepted_connection;
                }
			}

            // If no available socket close socket & display message
            close(new_socket);
            this->_logger.warning("Refused incomming connection as I'm already overbooked !");

            accepted_connection:
                continue;
		}

        for (uint8_t i = 0; i < SERVER_MAX_CLIENT; i++)
		{
			sd = client_sockets[i];
				
			if (FD_ISSET( sd , &readfds)) {
				//Check if it was for closing , and also read the
				//incoming message
				if ((nbytes = read(sd , buffer, 1024)) == 0) {
					//Somebody disconnected
					//Close the socket and mark as 0 in list for reuse
					close(sd);
					client_sockets[i] = 0;
				}
				else {
					buffer[nbytes] = '\0';

                    sbuffer = buffer;
                    sbuffer = Utility::String::trim(sbuffer);

                    if (Utility::String::to_lower(sbuffer) == "quit")
                        break ;
                    
                    if (sbuffer.empty())
                        continue ;

                    this->_logger.log("User input: " + sbuffer);
                    sbuffer = "";
                    buffer[0] = 0;
                }
			}
		}

    } while (Utility::String::to_lower(sbuffer) != "quit");

    this->_logger.info("Request quit.");

    for (uint8_t i = 0; i < SERVER_MAX_CLIENT; i++) {
        if (client_sockets[i] != 0)
            close(client_sockets[i]);
    }

    close(master_socket);

}

std::ostream & operator<<(std::ostream & o, Server const & i) {
    o << "Server running on *:" << i.getPortNo();
    return o;
}
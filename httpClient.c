#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    
    // GRAB SERVER ADDRESS FROM COMMAND-LINE
    char *address;
    address = argv[1];
    
    // CREATE CLIENT SOCKET
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in client_address;
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(80);
    inet_aton(address, &client_address.sin_addr.s_addr);

    int connection_status = connect(client_socket, (struct sockaddr *) &client_address, sizeof(client_address));

    char request[] = "GET / HTTP/1.1\r\n\r\n";
    char response[4098];

    send(client_socket, request, sizeof(request), 0);

    recv(client_socket, &response, sizeof(response), 0);

    printf("The server replied: %s", response);

    close(client_socket);

    return 0;
}

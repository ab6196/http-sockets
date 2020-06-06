#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main() {
    
    // OPEN HTML FILE TO SERVE 
    FILE *html_data;
    html_data = fopen("index.html","r");
    
    
    // READ DATA FROM FILE TO STRING
    char response_data[1024];
    fgets(response_data, 1024, html_data);
    
    // CREATE HTTP HEADER 
    char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
    strcat(http_header, response_data);
    
    // CREATE SOCKET
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    //DEFINE ADDRESS FOR SERVER SOCKET

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8001);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // BIND SOCKET TO IP ADDRESS

    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    // LISTEN FOR CONNECTIONS (SERVER SOCKET NAME, BUFFER SIZE TO STORE BACKLOG)

    listen(server_socket, 5);

    // ACCEPT REQUESTS

    int client_socket;

    while(1) {
        client_socket = accept(server_socket, NULL, NULL);
        send(client_socket, http_header, sizeof(http_header), 0);
        close(client_socket);
    }
    // close(client_socket);
    return 0;
}

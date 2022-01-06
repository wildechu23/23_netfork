#include "networking.h"


int main() {

	int server_socket;

	server_socket = client_connect();

	char buffer[BUFFER_SIZE];
    while(fgets(buffer, sizeof(buffer), stdin)) {
		// printf("%s\n", buffer);
        write(server_socket, buffer, sizeof(buffer));
        char s[BUFFER_SIZE];
        read(server_socket, s, sizeof(s));

        printf("%s\n", s);
    }
}

#include "networking.h"


int main() {

	int sd;
	int client_socket;

	sd = server_setup();
	
	while(1) {
		client_socket = server_connect(sd);

		int f;
		f = fork();

		if(f) {
			//server
			close(client_socket);
		} else {
			//subserver
			// to_client = server_connect( from_client );
			char s[BUFFER_SIZE];
			int r = 0;
			while(r = read(client_socket, s, sizeof(s))) {
				// printf("%d\n", r);
				// printf("%s\n", s);
				s[strlen(s)-1] = '\0';
				strcat(s, "<3");
				s[strlen(s)] = '\0';
				//printf("%s\n", s);
				write(client_socket, s, strlen(s)+1);
				for(int i = 0; i < BUFFER_SIZE; i++) s[i] = '\0';
			}
		}
	}
}

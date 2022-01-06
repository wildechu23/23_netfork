#include "networking.h"


/*=========================
  server_setup
  args:
  creates the WKP (upstream) and opens it, waiting for a
  connection.
  removes the WKP once a connection has been made
  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  // int from_client = 0;
  // int b;
  //
  // printf("[server] handshake: making wkp\n");
  // b = mkfifo(WKP, 0600);
  // if ( b == -1 ) {
  //   printf("mkfifo error %d: %s\n", errno, strerror(errno));
  //   exit(-1);
  // }
  // //open & block
  // from_client = open(WKP, O_RDONLY, 0);
  // //remove WKP
  // remove(WKP);
  //
  // printf("[server] handshake: removed wkp\n");
  // return from_client;

  //use getaddrinfo
  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  hints->ai_flags = AI_PASSIVE; //only needed on server
  getaddrinfo(NULL, "9845", hints, &results);  //Server sets node to NULL
  // printf("getaddrinfo success\n");

  //create socket
  int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
  // printf("socket created\n");

  bind(sd, results->ai_addr, results->ai_addrlen);
  // printf("bound\n");

  listen(sd, 10);

  free(hints);
  freeaddrinfo(results);
  
  return sd;
}

/*=========================
  server_connect
  args: int from_client
  handles the subserver portion of the 3 way handshake
  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int sd) {
  // int to_client  = 0;

  // int b;
  // char buffer[HANDSHAKE_BUFFER_SIZE];
  // //read initial message
  // b = read(from_client, buffer, sizeof(buffer));
  // printf("[server] handshake received: -%s-\n", buffer);


  // to_client = open(buffer, O_WRONLY, 0);
  // //create SYN_ACK message
  // srand(time(NULL));
  // int r = rand() % HANDSHAKE_BUFFER_SIZE;
  // sprintf(buffer, "%d", r);

  // write(to_client, buffer, sizeof(buffer));
  // //rad and check ACK
  // read(from_client, buffer, sizeof(buffer));
  // int ra = atoi(buffer);
  // if (ra != r+1) {
  //   printf("[server] handshake received bad ACK: -%s-\n", buffer);
  //   exit(0);
  // }//bad response
  // printf("[server] handshake received: -%s-\n", buffer);
  // return to_client;
  int client_socket;
  socklen_t sock_size;
  struct sockaddr_storage client_address;
  sock_size = sizeof(client_address);
  client_socket = accept(sd,(struct sockaddr *)&client_address, &sock_size);
  return client_socket;
}

int client_connect() {
  //use getaddrinfo
  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  getaddrinfo("127.0.0.1", "9845", hints, &results);  //Server sets node to NULL
  //create socket
  int sd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

  connect(sd, results->ai_addr, results->ai_addrlen);
  return sd;
}

// string_server.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define MYPORT 3492 // the port users will be connecting to
#define BUFFSIZE 1000
#define BACKLOG 10 // how many pending connections queue will hold

void sigchld_handler(int s)
{
  while(waitpid(-1, NULL, WNOHANG) > 0);
}

int main(void) {

  int socket_fd, new_socket_fd; 
  struct sockaddr_in my_address;
  struct sockaddr_in your_address;
  int yes = 1; // ???
  //  struct sigaction sa;
  socklen_t sin_size;

  // creates a socket and returns error if cannot
  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(1);
  }

  if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
    perror("setsockopt");
    exit(1);
  }

  my_address.sin_family = AF_INET; // wha does this do?
  my_address.sin_port = htons(MYPORT); // again, what?
  my_address.sin_addr.s_addr = INADDR_ANY; // what?

  // sets the memory to null from beg to end (aka zeroing the addr or clearing the structure)
  memset(my_address.sin_zero, '\0', sizeof my_address.sin_zero);

  if (bind(socket_fd, (struct sockaddr *) &my_address, sizeof my_address) == -1) {
    perror("bind");
    exit(1);
  } 

  if (listen(socket_fd, BACKLOG) == -1) {
    perror("listen");
    exit(1);
  } 

  /*
  // skipping signal handler
  sa.sa_handler = sigchld_handler; // reap all dead processes
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if (sigaction(SIGCHLD, &sa, NULL) == -1) {
    perror("sigaction");
    exit(1);
  }
  */


  //  while (1) {
    sin_size = sizeof your_address;
    if ((socket_fd = accept(socket_fd, (struct sockaddr *) &your_address, &sin_size)) == -1) {
      perror("accept");
      //  continue;
    }

    char buffer[1000];
    int bytes_received;
    if (bytes_received = recv(socket_fd, buffer, BUFFSIZE, 0)) {
      perror("recv");
      exit(1); // may change this later to keep looping
    }
    buffer[bytes_received] = '\0';
    printf("Did you say? %s\n", buffer);
    // changing to uppercase
    for (int i = 0; i < sizeof buffer; ++i) 
      buffer[i] = toupper(buffer[i]);

    if (!fork()) {
      close(socket_fd);
      if (send(new_socket_fd, buffer, sizeof buffer, 0) == -1) 
	perror("send");
      close(new_socket_fd);
      exit(0);
    }
    close(new_socket_fd);
    //  } // while
  return 0;
} // main
// string_server.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define MYPORT 3492 // the port users will be connecting to
#define BUFFSIZE 1000
#define BACKLOG 10 // how many pending connections queue will hold

void sigchld_handler(int s)
{
  while(waitpid(-1, NULL, WNOHANG) > 0);
}

int main(void) {

  int socket_fd, new_socket_fd; 
  struct sockaddr_in my_address;
  struct sockaddr_in your_address;
  int yes = 1; // ???
  //  struct sigaction sa;
  socklen_t sin_size;

  // creates a socket and returns error if cannot
  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(1);
  }

  if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
    perror("setsockopt");
    exit(1);
  }

  my_address.sin_family = AF_INET; // wha does this do?
  my_address.sin_port = htons(MYPORT); // again, what?
  my_address.sin_addr.s_addr = INADDR_ANY; // what?

  // sets the memory to null from beg to end (aka zeroing the addr or clearing the structure)
  memset(my_address.sin_zero, '\0', sizeof my_address.sin_zero);

  if (bind(socket_fd, (struct sockaddr *) &my_address, sizeof my_address) == -1) {
    perror("bind");
    exit(1);
  } 

  if (listen(socket_fd, BACKLOG) == -1) {
    perror("listen");
    exit(1);
  } 

  /*
  // skipping signal handler
  sa.sa_handler = sigchld_handler; // reap all dead processes
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if (sigaction(SIGCHLD, &sa, NULL) == -1) {
    perror("sigaction");
    exit(1);
  }
  */


  //  while (1) {
    sin_size = sizeof your_address;
    if ((socket_fd = accept(socket_fd, (struct sockaddr *) &your_address, &sin_size)) == -1) {
      perror("accept");
      //  continue;
    }

    char buffer[1000];
    int bytes_received;
    if (bytes_received = recv(socket_fd, buffer, BUFFSIZE, 0)) {
      perror("recv");
      exit(1); // may change this later to keep looping
    }
    buffer[bytes_received] = '\0';
    printf("Did you say? %s\n", buffer);
    // changing to uppercase
    for (int i = 0; i < sizeof buffer; ++i) 
      buffer[i] = toupper(buffer[i]);

    if (!fork()) {
      close(socket_fd);
      if (send(new_socket_fd, buffer, sizeof buffer, 0) == -1) 
	perror("send");
      close(new_socket_fd);
      exit(0);
    }
    close(new_socket_fd);
    //  } // while
  return 0;
} // main

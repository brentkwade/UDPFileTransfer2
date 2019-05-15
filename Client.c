#include <stdio.h> // For printf()
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <unistd.h>
#include <arpa/inet.h> // sockaddr_in, inet_addr
#include <netinet/in.h>
#include <sys/socket.h> // socket(), connect(), send(), recv()

#define PORT 1234
#define FLAG 0
#define BUFFSIZE 32
#define IPAddress "127.0.0.1"
#define nonExist

void dump(char *b)
{
  int i;
  for (i = 0; i < BUFFSIZE; i++)
  {
    b[i] = '\0';
  }
}
int receive(char *buf, int s)
{
  int i;
  char ch;
  for (i = 0; i < s; i++)
  {
    ch = buf[i];
    if (ch == EOF)
    {
      return 1;
    }
    else
    {
      //fwrite(buf, sizeof(char), i, ch);
      printf("%c", ch);
    }
    return 0;
  }
}

int main()
{
  int sockfd, nBytes;
  struct sockaddr_in myAdd;
  int addrlen = sizeof(myAdd);
  myAdd.sin_family = AF_INET;
  myAdd.sin_port = htons(PORT);
  myAdd.sin_addr.s_addr = inet_addr((IPAddress));
  char buf[BUFFSIZE];
  FILE *fp;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  if (sockfd < 0)
  {
    perror("ERROR: File Descriptor Not Received\n");
  } //else {
  //printf("File Descriptor Received: '%s'", sockfd)
  //}

  while (1)
  {
    printf("Enter File Name To Be Retrieved: \n");
    scanf("%s", buf);
    sendto(sockfd, buf, BUFFSIZE, FLAG, (struct sockaddr *)&myAdd, addrlen);
    //fread(buf, sizeof(char), BUFFSIZE, fp);
    //fwrite(buf, sizeof(char), nBytes, fp);
    while (1)
    {
      dump(buf);
      nBytes = recvfrom(sockfd, buf, BUFFSIZE, FLAG, (struct sockaddr *)&myAdd, &addrlen);

      if (receive(buf, BUFFSIZE))
      {
        //fread(buf, sizeof(char), BUFFSIZE, fp);
        //fwrite(buf, sizeof(char), nBytes, fp);
        break;
      }
    }
    return 0;
  }
}
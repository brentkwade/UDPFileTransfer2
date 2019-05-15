#include <stdio.h> // For printf()
#include <stdlib.h>
#include <string.h>
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

int sendFile(FILE *fp, char *buf, int s)
{
  int i, len;
  if (fp == NULL)
  {
    perror("Contents Empty\n");
  }
  char ch;
  for (i = 0; i < s; i++)
  {
    ch = fgetc(fp);
    buf[i] = ch;
    if (ch == EOF)
    {
      return 1;
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

  if (bind(sockfd, (struct sockaddr *)&myAdd, sizeof(myAdd)) == 0)
  {
    printf("Bind Successful\n");
  }
  else
  {
    perror("ERROR: Bind Unsuccessful\n");
  }

  while (1)
  {
    char fileName[BUFFSIZE] = {0};
    printf("Waiting For Client Request...\n");
    dump(buf);
    nBytes = recvfrom(sockfd, fileName, BUFFSIZE, FLAG, (struct sockaddr *)&myAdd, &addrlen);
    FILE *fp = fopen(fileName, "r+");
    printf("File Name: '%s'\n", fileName);
    if (fp == NULL)
    {
      perror("ERROR: Unable To Open File");
    }
    else
    {
      printf("Opened File '%s'\n", fileName);
    }
    while (1)
    {
      if (sendFile(fp, fileName, BUFFSIZE))
      {
        sendto(sockfd, fileName, BUFFSIZE, FLAG, (struct sockaddr *)&myAdd, addrlen);
        break;
      }
      sendto(sockfd, fileName, BUFFSIZE, FLAG, (struct sockaddr *)&myAdd, addrlen);
      //fread(buf, sizeof(char), BUFFSIZE, fp);
      //fwrite(fileName, sizeof(char), nBytes, fp);
      dump(buf);
    }
    if (fp != NULL)
    {
      close(fp);
    }
    return 0;
  }
}

/*void writeFile(int sockfd, FILE* fp) {
  ssize_t n;
  char fileName[BUFFSIZE];
  struct sockaddr_in myAdd;
  socklen_t addrlen = sizeof(myAdd);
  int n = recvfrom
}*/
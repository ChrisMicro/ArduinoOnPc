

#include "WebServer.h"
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>	//write

/*
Socket procedure:
1. create socket
2. bind port
3. listen: wati for connection requests
4. accept connection
5. receive/send data
6. close connection 
*/

WebServer::WebServer(int port)
{
  _port=port;
}

int socket_desc;
int client_sock;

struct sockaddr_in wserver;
struct sockaddr_in client;

void WebServer::begin() 
{
  _currentArgCount=0;

  //Create socket
  socket_desc = socket(AF_INET , SOCK_STREAM , 0);
  if (socket_desc == -1)
  {
    printf("Could not create socket");
  }
  puts("Socket created");

  // Prepare the sockaddr_in structure
  wserver.sin_family = AF_INET;
  wserver.sin_addr.s_addr = INADDR_ANY;
  wserver.sin_port = htons( _port );

  //Bind
  if( bind(socket_desc,(struct sockaddr *)&wserver , sizeof(wserver)) < 0)
  {
    //print the error message
    perror("bind failed. Error");
    //return 1;
  }
  puts("bind done");
  //************ Listen ***************************
  listen(socket_desc , 3);

  //Accept and incoming connection
  puts("Waiting for incoming connections...");

}

#define BUF 1024

typedef void(*THandlerFunction)();


THandlerFunction onHandler;
THandlerFunction notFoundHandler;

void WebServer::handleClient() 
{
  char buffer[BUF];
  int c;
  int len;

  //static int Counter=0;

  //************ accept ***************************
  //accept connection from an incoming client
  c = sizeof(struct sockaddr_in);
  client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);

  if (client_sock > 0) printf ("client (%s) connected ...\n",inet_ntoa (client.sin_addr));

  len = recv (client_sock, buffer, BUF-1, 0);
  if( len > 0) buffer[len] = '\0';
  // printf ("got message: %s\n", buffer);

  // parse message
  String message=String(buffer);

  int i1=message.indexOf("GET")+4;
  int i2=message.indexOf("HTTP")-1;
  String content_GET=message.substring(i1,i2);
//Serial.print("==>");
//Serial.println(part1);

/*
  char str[]="  dies ist ein kleiner test 1";
  str[0]=((uint8_t) Counter)+'1';
  write(client_sock , str , strlen(str));
  printf("%d\n",Counter++);
*/

  if (content_GET.equals("/favicon.ico"))
  {
    // we have no icon yet
    send(404,"","");
  }else
  if (content_GET.equals("/"))
  {
    if(onHandler!=NULL) 
    {
      puts("on handler");
      onHandler();
    }

  //else puts("no handler");
  }
  else  
  {
    Serial.print("not found ==>");
    Serial.println(content_GET);
    if(notFoundHandler!=NULL) 
    {
      notFoundHandler();
    }
  }

  close (client_sock);
}

void WebServer::on(const String &uri, WebServer::THandlerFunction handler) 
{
  onHandler=handler;
}

void WebServer::onNotFound(THandlerFunction fn) 
{
  notFoundHandler=fn;
}

int WebServer::args() 
{
  return _currentArgCount;
}

void WebServer::send(int code, const char* content_type, const String& content) 
{
  char str[1024];
  content.toCharArray(str,1024);

  write(client_sock , str , strlen(str));
}


void WebServer::send(int code, char* content_type, const String& content) 
{
  send(code, (const char*)content_type, content);
}

void WebServer::send(int code, const String& content_type, const String& content) 
{
  char str[1024];
  content_type.toCharArray(str,1024);
  send(code,str,content);
}

String WebServer::arg(String name) 
{
  return "";
}

String WebServer::arg(int i) 
{
  return "";
}

String WebServer::argName(int i) 
{
  return "";
}

/*
  WebServer.cpp - Dead simple web-server.
  Supports only one simultaneous client, knows how to handle GET and POST.
  Copyright (c) 2014 Ivan Grokhotkov. All rights reserved.
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  Modified 8 May 2015 by Hristo Gochkov (proper post and file upload handling)
*/


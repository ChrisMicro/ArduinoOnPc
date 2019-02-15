

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Arduino.h"
#include "HTTP_Method.h"


class WebServer
{
 public:
  WebServer(int port = 8080);

  void begin();
  void handleClient();

  typedef void(*THandlerFunction)();

  void on(const String &uri, THandlerFunction handler);

  void onNotFound(THandlerFunction fn); //called when handler is not assigned
  String uri() { return _currentUri; }
  HTTPMethod method() { return _currentMethod; }
  int args(); // get arguments count
  
  String arg(String name);  // get request argument value by name
  String arg(int i);        // get request argument value by number
  String argName(int i);    // get request argument name by number
  
  void send(int code, const char* content_type = NULL, const String& content = String(""));
  void send(int code, char* content_type, const String& content);
  void send(int code, const String& content_type, const String& content);

 protected:

  struct RequestArgument {
    String key;
    String value;
  };

  int _port;


  HTTPMethod _currentMethod;
  String _currentUri;
  int              _currentArgCount;
  RequestArgument* _currentArgs;
  int              _postArgsLen; 
  RequestArgument* _postArgs;

 String _responseHeaders;

};


#endif //WEBSERVER_H

// template functions from
// https://github.com/espressif/arduino-esp32/blob/master/libraries/WebServer/src/WebServer.h
/*
  WebServer.h - Dead simple web-server.
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


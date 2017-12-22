// Linux
namespace lin
{
  #include "stdio.h"
  #include <sys/socket.h>
  #include <arpa/inet.h>
}


#include "MQTTPacket.h"
#include "MQTTPublish.h"

const char ip[] = "your ip";
const int port = 15041;
char user[] = "username";
char password[] = "password";
 
int main(){
	int sock;
	struct lin::sockaddr_in server;
	 
	//Create socket
	sock = lin::socket(AF_INET , lin::SOCK_STREAM , 0);
	if (sock == -1)
	{
    lin::printf("Could not create socket");
	}
  lin::puts("Socket created");
	 
	server.sin_addr.s_addr = lin::inet_addr(ip);
	server.sin_family =AF_INET;
	server.sin_port = lin::htons(port);

	//Connect to remote server
	if (lin::connect(sock , (struct lin::sockaddr *)&server , sizeof(server)) < 0)
	{
    lin::perror("connect failed. Error");
			return 1;
	}

  unsigned char buf[512];
  // Connection Packet
  MQTTPacket_connectData connect = MQTTPacket_connectData_initializer;

  connect.clientID.cstring = "test";
  connect.keepAliveInterval = 20;
  connect.cleansession = 1;
  connect.username.cstring = user;
  connect.password.cstring = password;
  int len = MQTTSerialize_connect(buf, sizeof(buf), &connect); /* 1 */
  // Send
  lin::send(sock , buf , len, 0);

  // Publish Packet
  // topic
  MQTTString topic = MQTTString_initializer;
  topic.cstring = "testtopic";
  // payload
  unsigned char payload[] = "Hello MQTT!";
  len = MQTTSerialize_publish(buf, sizeof(buf), 0, 0, 0, 0, topic, payload, sizeof(payload));
  // Send
  lin::send(sock , buf , len, 0);

  return 0;
}

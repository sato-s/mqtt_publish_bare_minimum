main: mqtt_publish_bare_minimum.cpp
	g++ mqtt_publish_bare_minimum.cpp MQTTPacket.c MQTTConnectClient.c  MQTTSerializePublish.c -o a.out

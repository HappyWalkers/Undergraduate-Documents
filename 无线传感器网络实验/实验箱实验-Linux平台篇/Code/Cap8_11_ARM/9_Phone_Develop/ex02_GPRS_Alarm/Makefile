all:
	arm-linux-gcc -o \
	ex02_GPRS_Alarm ex02_GPRS_Alarm.c -Iinclude -Llib -llibsmscb -lwsncomm -lpthread \
	-L/usr/local/Trolltech/QtEmbedded-4.7.0-arm/lib -lQtCore -lQtNetwork

clean:
	rm -f ex02_GPRS_Alarm

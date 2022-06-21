from bluepy.btle import Scanner, DefaultDelegate
import socket,time

station_id = "1"
UDP_IP = "" #receiver's ip
UDP_PORT = 5004
soc = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

class ScanDelegate(DefaultDelegate):
    def __init__(self):
        DefaultDelegate.__init__(self)

    def handleDiscovery(self, dev, isNewDev, isNewData):
        if isNewDev:
            print "Discovered device", dev.addr
        elif isNewData:
            print "Received new data from", dev.addr
                

scanner = Scanner().withDelegate(ScanDelegate())

while True:
    devices = scanner.scan(2.0)
    DevicesInfo = ["" for i in range(len(devices))]
    i = 0
    for dev in devices:
        print "Device %s , RSSI=%d dB" % (dev.addr , dev.rssi)
        DevicesInfo[i] = station_id+","+dev.addr+","+str(dev.rssi)
        i = i+1
    MESSAGE = "|"
    for i in range(len(DevicesInfo)):
        MESSAGE += DevicesInfo[i]+"|"
    soc.sendto(MESSAGE, (UDP_IP,UDP_PORT))
    time.sleep(0.2)
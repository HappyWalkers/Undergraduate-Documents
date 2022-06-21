import select

import bluetooth

from bluepy.btle import Scanner, DefaultDelegate
import socket,time

station_id = "1"
UDP_IP = "172.20.10.4" #receiver's ip
UDP_PORT = 5004
soc = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

flag_send=0
num_find=0
devices_info=[]


class MyDiscoverer(bluetooth.DeviceDiscoverer):

    def pre_inquiry(self):
        print('pre inquiry')
        self.done = False

    def device_discovered(self, address, device_class, rssi, name):
        print('device discovered')
        global flag_send
        flag_send=flag_send-1
        global num_find
        num_find=num_find+1
        print("{} - {}".format(address, name))

        # get some information out of the device class and display it.
        # voodoo magic specified at:
        # https://www.bluetooth.org/foundry/assignnumb/document/baseband
        major_classes = ("Miscellaneous",
                         "Computer",
                         "Phone",
                         "LAN/Network Access Point",
                         "Audio/Video",
                         "Peripheral",
                         "Imaging")
        major_class = (device_class >> 8) & 0xf
        if major_class < 7:
            print(" " + major_classes[major_class])
        else:
            print("  Uncategorized")

        print("  Services:")
        service_classes = ((16, "positioning"),
                           (17, "networking"),
                           (18, "rendering"),
                           (19, "capturing"),
                           (20, "object transfer"),
                           (21, "audio"),
                           (22, "telephony"),
                           (23, "information"))

        for bitpos, classname in service_classes:
            if device_class & (1 << (bitpos-1)):
                print("   ", classname)
        print("  RSSI:", rssi)
        
       # device_info=[]
        global station_id
       # device_info.append(station_id)
       # device_info.append(address)
       # device_info.append(rssi)
        devices_info.append(station_id+","+address+","+str(rssi))
       # print(device_info)
       # print(devices_info)

    def inquiry_complete(self):
        self.done = True
        print('inquiry complete')


def send_message():
    print('send message')
    global devices_info
    global soc
    global UDP_IP
    global UDP_PORT
    MESSAGE="|"
    for i in range(len(devices_info)):
        MESSAGE+=devices_info[i]+"|"
    #print("----------------"+MESSAGE)
    soc.sendto(str.encode(MESSAGE),(UDP_IP,UDP_PORT))
    time.sleep(0.2)
    global flag_send
    flag_send=0



while True:
    d = MyDiscoverer()
    d.find_devices(lookup_names=True,duration=8)

    readfiles = [d, ]

    while True:
        rfds = select.select(readfiles, [], [])[0]
        #print(rfds)

        if d in rfds:
            d.process_event()
            print('process event')
            flag_send=flag_send+1
            if flag_send>10:
                send_message()
                break

        if d.done:
            print('d.done')
            send_message()
            break

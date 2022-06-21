import threading
import time
from bluepy.btle import Scanner, DefaultDelegate
import requests
import json

macSet = set()

class ScanDelegate(DefaultDelegate):
    def __init__(self):
        DefaultDelegate.__init__(self)

    def handleDiscovery(self, dev, isNewDev, isNewData):
        macSet.add(dev.addr)


class ScanBluetooth(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        
    def run(self):        
        scanner = Scanner().withDelegate(ScanDelegate())
        while True:
            try:
                devices = scanner.scan(10.0)
            except BaseException:
                pass

class Poster(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
    
    def run(self):
        global macSet
        while True:
            try:
                time.sleep(60)
                macAddressList = list(macSet)
                macSet = set()
                
                url = "http://192.168.0.210:8988/gate/scanData"
                data = {"gate":"SouthGate","macAddressList":macAddressList}
                headers = {"Content-Type":"application/json"}
                 res = requests.post(url = url,data = json.dumps(data),headers = headers)
                print(res)
            except BaseException:
                pass


# 创建新线程
scanBluetooth = ScanBluetooth()
poster = Poster()

# 开启新线程
scanBluetooth.start()
poster.start()
scanBluetooth.join()
poster.join()
print ("退出主线程")
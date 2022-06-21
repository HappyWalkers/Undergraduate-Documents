import socket,math,time,pygame
from datetime import datetime

obj_MAC = "38:89:2C:DD:8B:02"#
obj_dis=[0,0,0]
# stations = [[3,0.4,1.5],[5,3,1.5],[0.35,1.4,1.5]]
stations = [ [0 , 0], [1, 0], [1, 2] ]

UDP_IP = "172.20.10.4" #ip
UDP_PORT0 = 5004
UDP_PORT1 = 5005
UDP_PORT2 = 5006

socket0 = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
socket1 = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
socket2 = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
socket0.bind((UDP_IP, UDP_PORT0))
socket1.bind((UDP_IP, UDP_PORT1))
socket2.bind((UDP_IP, UDP_PORT2))

pygame.init()

FPS = 40
fpsClock = pygame.time.Clock()

size = width,height = 900,700
screen = pygame.display.set_mode(size)
pygame.display.set_caption("Simple Bluetooth Positioning System")
screen.fill((44,44,44))
font = pygame.font.SysFont("arial", 50)

check0 = False
check1 = False
check2 = False

while True:	
	data0, addr0 = socket0.recvfrom(1024)
	tmp0 = str(data0)
	message0 = tmp0.split('\'')[1]
	tmp0 = message0.split('|')
	devices_num0 = len(tmp0)-2
	devices0 = [["","",""] for i in range(devices_num0)]
	for i in range(devices_num0):
		s = tmp0[i+1].split(',')
		devices0[i][0] = s[0]#station_id
		devices0[i][1] = s[1]#dev_MAC
		devices0[i][2] = s[2]#RSSI
		print(devices0[i])
	print()
	id_station0 = devices0[0][0]
	for i in range(devices_num0):
		if devices0[i][1] == obj_MAC:
			check0 = True
			rssi0 = int(devices0[i][2])
			distance0 = math.pow(10,((abs(rssi0)-53)/(10*5)))#这个公式可能需要测试参数
			
	data1, addr1 = socket1.recvfrom(1024)
	tmp1 = str(data1)
	message1 = tmp1.split('\'')[1]
	tmp1 = message1.split('|')
	devices_num1 = len(tmp1)-2
	devices1 = [["","",""] for i in range(devices_num1)]
	for i in range(devices_num1):
		s = tmp1[i+1].split(',')
		devices1[i][0] = s[0]#station_id
		devices1[i][1] = s[1]#dev_MAC
		devices1[i][2] = s[2]#RSSI
		print(devices1[i])
	print()
	id_station1 = devices1[0][0]
	for i in range(devices_num1):
		if devices1[i][1] == obj_MAC:
			check1 = True
			rssi1 = int(devices1[i][2])
			distance1 = math.pow(10,((abs(rssi1)-53)/(10*5)))
			
	data2, addr2 = socket2.recvfrom(1024)
	tmp2 = str(data2)
	message2 = tmp2.split('\'')[1]
	tmp2 = message2.split('|')
	devices_num2 = len(tmp2)-2
	devices2 = [["","",""] for i in range(devices_num2)]
	for i in range(devices_num2):
		s = tmp2[i+1].split(',')
		devices2[i][0] = s[0]#station_id
		devices2[i][1] = s[1]#dev_MAC
		devices2[i][2] = s[2]#RSSI
		print(devices2[i])
	print()
	id_station2 = devices2[0][0]
	for i in range(devices_num2):
		if devices2[i][1] == obj_MAC:
			check2 = True
			rssi2 = int(devices2[i][2])
			distance2 = math.pow(10,((abs(rssi2)-53)/(10*5)))
		
	if check0 and check1 and check2:
		screen.fill((44,44,44))
		#高度(z)相同
		sta0 = pygame.draw.circle(screen,(255,0,0),(370+int(10*float(stations[0][0])),320+int(10*float(stations[0][1]))),3,1)
		sta1 = pygame.draw.circle(screen,(0,255,0),(370+int(10*float(stations[1][0])),320+int(10*float(stations[1][1]))),3,1)
		sta2 = pygame.draw.circle(screen,(0,0,255),(370+int(10*float(stations[2][0])),320+int(10*float(stations[2][1]))),3,1)

		pygame.draw.circle(screen,(255,0,0),(370+int(10*float(stations[0][0])),320+int(10*float(stations[0][1]))),int(10*(distance0)),1)
		pygame.draw.circle(screen,(0,255,0),(370+int(10*float(stations[1][0])),320+int(10*float(stations[1][1]))),int(10*(distance1)),1)
		pygame.draw.circle(screen,(0,0,255),(370+int(10*float(stations[2][0])),320+int(10*float(stations[2][1]))),int(10*(distance2)),1)

		t = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
		text = font.render(t,True,(255,255,255))
		screen.blit(text, (30, 30))
		pygame.display.update() 
		fpsClock.tick(FPS)
		check0 = False
		check1 = False
		check2 = False

	for event in pygame.event.get():
			if event.type == pygame.QUIT:
				pygame.quit()

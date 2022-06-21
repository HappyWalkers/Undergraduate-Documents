address='C:\\Users\\anhuishuangqiao\\Desktop\\sample-plan.txt';
format=repmat('%s ',1,5);
[taxiID first second third fourth]=textread(address,format,'headerlines', 1, 'delimiter', ',');
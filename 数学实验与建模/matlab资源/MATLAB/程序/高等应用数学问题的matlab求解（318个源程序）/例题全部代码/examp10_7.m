fff=newfis('c10mfis');                 % ����ģ������ϵͳģ��
fff=addvar(fff,'input','ip1',[-3,3]);  % �����һ·����
fff=addvar(fff,'input','ip2',[-5,5]);  % ����ڶ�·����
fff=addvar(fff,'output','op',[-2,2]);  % ��������ź�
fuzzy(fff)          % �� fuzzy() �������ӵر༭ģ������ϵͳ

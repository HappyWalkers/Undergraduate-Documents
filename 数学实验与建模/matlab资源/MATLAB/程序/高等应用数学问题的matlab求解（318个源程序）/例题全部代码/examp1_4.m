function c1ex4
[t,x]=ode45('myvdpeq',[0,10],[-1;1]);  % ֱ����΢�ַ�����ֵ��
% ����ĺ������� Van de Pol ���̱���
function y=myvdpeq(t,x)
y=[x(2); -(x(1)^2-1)*x(2)-x(1)];

%�ӳ�΢�ַ��̿����� dde23() ������⣬Ҳ������ Simulink ��⣬���߸�ֱ��
% ������Ƴ� Simulink ģ�ͣ�ѡ�� Simulation/Start �˵���������������
c1ex4mod
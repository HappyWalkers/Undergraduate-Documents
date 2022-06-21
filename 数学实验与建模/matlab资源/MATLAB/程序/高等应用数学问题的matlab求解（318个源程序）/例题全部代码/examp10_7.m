fff=newfis('c10mfis');                 % 建立模糊推理系统模型
fff=addvar(fff,'input','ip1',[-3,3]);  % 定义第一路输入
fff=addvar(fff,'input','ip2',[-5,5]);  % 定义第二路输入
fff=addvar(fff,'output','op',[-2,2]);  % 定义输出信号
fuzzy(fff)          % 用 fuzzy() 函数可视地编辑模糊推理系统

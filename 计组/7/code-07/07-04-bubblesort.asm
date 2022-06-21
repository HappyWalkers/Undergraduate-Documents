d1  segment
    a  dw  32,85,16,15,8
d1  ends      
code segment     
  main proc far  
    assume cs:code,ds:d1
  start:         
    push  ds     
    sub  ax,ax   
    push ax          
    mov  ax,d1 
    mov  ds,ax
    
    
    mov  cx,4        ;5个元素，外层循环为4次
 lop1:
    push cx          ;内存循环要用到cx，需先将cx入栈保存。同时cx也是内存循环执行的次数
    mov  bx,0        ;从第一个元素开始比较，每次进入外层循环都要将指针指向第一个元素
 lop2:
    mov  ax,a[bx]    ;比较相邻两个元素，因为cmp指令的两个操作数不能同时为内存单元，所以需要通过ax中介
    cmp  ax,a[bx+2]   
    jbe  con         ;小于等于则继续操作   
    xchg ax,a[bx+2]  ;大于则交换两个元素的值，同样通过ax中转
    mov  a[bx],ax
con: 
    add  bx,2        ;bx加2，执行下一个元素。（dw类型，每个元素占两个字节）
    loop lop2        ;内存循环

    pop  cx          ;恢复cx值
    loop lop1        ;外层循环

    ret          
  main endp  
code ends        
end start        

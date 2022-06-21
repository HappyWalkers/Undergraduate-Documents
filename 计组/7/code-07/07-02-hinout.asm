d1 segment
   crlf  db 0dh,0ah,'$'
d1 ends
code segment     
  main proc far  
    assume cs:code,ds:d1,es:d1
  start:         
    push  ds     
    sub  ax,ax   
    push ax 
    mov  ax,d1
    mov  ds,ax     
    
  again:    
    mov  bx,0 ;输入的数放在bx中，先给bx置0
    mov  cx,4 ;循环次数，最多4个16进制位
  hin:
    mov  ah,1
    int  21h  ;输入一个字母   

    sub  al,30h ;字母ASCII码变为数值
    cmp  al,0   
    jb   h2b    ;比0小的，不合格，退出输入 
    cmp  al,9   ;小于等于9小的（前面已经保证大于等于0了），合格输入，可直接计入
    jbe  m16    
    sub  al,7   ;对于'A-F',ASCII码为41H-46H，要变成 0ah-0fh，再减掉30h后还需要再减掉7
    cmp  al,0ah 
    jb   h2b    ;小于0ah(10)，不合格，退出输入 
    cmp  al,0fh 
    ja   h2b    ;大于0fh(15)，不合格，退出输入
  m16:  
    push cx     ;下面的bx循环移位次数大于1，必须用到CL寄存器，因此先利用堆栈保存CX。
    mov  cl,4   
    rol  bx,cl  ;bx循环左移四位，把最右侧4位腾出来，用于保存新输入的一个16进制数（4个二进制位）
                ;如原来为00ABH，那么左移4位就是0AB0H。
    add  bl,al  ;将bl加上刚处理完的用户输入数值。如刚输入9，那么0B0h+9=0B9h，bh保持不变，bx值就是0AB9h。
    
    pop  cx     ;还原保存的CX值，一定要对应哦
    loop  hin   ;继续输入下一个数值
    
    lea dx,crlf
    mov ah,9
    int 21h     ;输出回车换行
    
    h2b:
    mov  cx,4   ;4个16进制位，依次输出
  hout:
    push cx     ;cx值入栈，暂时保存cx值
    mov  cl,4   
    rol  bx,cl  ;bx循环左移四位，这样最高4个二进制位（1个16进制位）就移到了最低的4个二进制位。
                ;如36B9h，就变成了6B93h。从16进制位最高位开始依次输出
    mov  dl,bl  ;bl值放入dl中，即保护了bl(bx)的值，也为输出做准备
    and  dl,0fh ;只要输出最低4位，但是dl有8个二进制位，所以通过与操作将dl的高四位清0,低4位保持不变

    add  dl,30h ;数值编程ASCII码
    cmp  dl,3ah ;'0'~'9'直接输出
    jb   hcharout
    add  dl,7   ;如果数值大于10 ，还需继续加7才是其ASCII码。
  hcharout:
    mov  ah,2  
    int  21h    ;输出一个字符
  
    pop  cx     ;恢复CX值
    loop hout   

    
    ret          
  main endp       
code ends       
end start        

public decout 
data  segment
  zero db 0
data  ends

code segment     
  decout proc far  
    assume cs:code,ds:data
    push  ds


    mov  ax,data
    mov  ds,ax

    cmp  bx,0
    jne  next   
    mov  dl,'0'
    mov  ah,2
    int  21h
    jmp  return

next:
    mov  zero,0
    
    mov  cx,10000 ;为除10000预置参数
    call dout     ;调用dout过程，输出万位
                  ;依次输出千位、百位、十位、各位....
    mov  cx,1000
    call dout
    
    mov  cx,100
    call dout
    
    mov  cx,10
    call dout
    
    mov  cx,1
    call dout
    
return:
    pop ds
    ret          
  decout endp
  dout  proc near
    mov  dx,0     ;dx清0,除cx时，被除数为dx,ax
    mov  ax,bx    ;将bx值（第一次为输入的数，随后为余数）赋值给ax
    div  cx       ;(dx,ax)，实际为ax（dx==0）除以cx（cx值在调用程序前设置，作为参数传递进来）
    xchg ax,dx    ;ax与dx交换内容。交换后：ax中为余数，dx中为商
    mov  bx,ax    ;将ax值（余数）赋予bx（进入下一轮运算） 
                  ;如果用户前面输入65535，那么在第一轮除以10000后，dx中值为6，bx中值为5535
    cmp  dl,0     
    jne  outanum  ;如果dx中值不为0，则直接输出相应的数值
    cmp  zero,0   ;如果dx中值为0,那么判断是前面无意义的0，还是中间有意义的0。
                  ;如305，那么如果不进行次判断将输入00305。通过此位可以不输出前面两个0，但是输出中间0。
    je   con      ;如果是前面无意义的0 ，则不输出
 outanum:
    mov  zero,1   ;如果输出了一个大于0的数字，则置标志位为1，使得其后所有0都会被输出
    add  dl,30h   ;dl中数值加上30h，变成对应的ASCII码。
    mov  ah,2
    int  21h      ;输出该数字
 con:
    ret           ;如果要求可以输入负数？输入0会输出吗？
  dout  endp        
code ends
end       

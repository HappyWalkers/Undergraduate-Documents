d1 segment
   zero  db 0   
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

    mov  bx,0     ;输入的数放在bx中，先给bx置0   
    mov  cx,10    ;为除10做准备
  din:
    mov  ah,1
    int  21h      ;输入一个字符   

    sub  al,30h   ;将输入字符的ASCII码值减30h（如果输入的是字符'0'~'9',其ASCII码减30h后为数值0~9）
    cmp  al,0     
    jb   d2b      ;数值小于0，不满足需求，终止输入
    cmp  al,9
    ja  d2b       ;数值大于9，不满足需求，终止输入  
  m10:
    mov  ah,0     ;输入的数值在al中，但是需要扩展到ax，所以直接给ah赋值0
    xchg ax,bx    ;ax与bx交换内容。因为乘以10的是已输入数值，即在bx中的数值。而乘数必须为ax，所以交换位置
    mul  cx       ;ax（原bx）中内容乘以10。如要输入123，已经输入了12，再输入3时，我们需要先将12*10=120
                  ;乘后结果在(dx,ax)，我们只考虑16位数据，所以dx中数据自动丢弃
    add  ax,bx    ;乘后结果在ax中，再加上bx（原ax，新输入）的内容。如120+3=123
    xchg ax,bx    ;ax与bx交换内容。bx内为新的数值如123。ax中内容无所谓。
    jmp  din      ;继续输入
    
    lea dx,crlf
    mov ah,9
    int 21h       ;输出回车换行
    
    d2b:          ;十进制数输出，按照万位、千位、百位....顺序输出
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
    

    
    ret          
  main endp
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
end start        

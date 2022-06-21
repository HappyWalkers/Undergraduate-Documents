data  segment    ;数据段开始
		x	dw 5,14,20 ;存储空间申请（变量定义）
		y	dw 6
		z	dw 7
		w	dw ?
data ends        ;数据段结束

code segment     ;代码段开始
  main proc far  ;主程序定义开始
    assume cs:code,ds:data ;指定缺省段
  start:         ;整个代码开始
    push  ds     ;缺省操作
    sub  ax,ax   ;缺省操作
    push ax      ;缺省操作
    mov  ax,data ;将数据段起始地址通过ax赋给ds
    mov  ds,ax   ;将数据段起始地址通过ax赋给ds
    mov  ax,x    ;将内存以x值为偏移地址的单元的值赋给ax
    add  ax,y    ;将内存以y为偏移地址的单元的值与ax相加并赋给ax
    add  ax,z    ;将内存以z值为偏移地址的单元的值与ax相加并赋给赋给ax
    mov  w,ax    ;将ax寄存器的值赋给内存以z值为偏移地址的单元
    ret          ;主函数返回
  main endp      ;主程序定义结束
code ends        ;代码段结束
end start        ;代码结束

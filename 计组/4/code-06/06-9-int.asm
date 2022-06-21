d1 segment
   crlf  db 0dh,0ah,'$'  ;carriage return & linefeed 
   msg1  db "Hello World!",0dh,0ah,'$'
   msg2  db "char?",'$'
   msg3  db "dup:",'$'
   msg4  db "name?",'$'
   namemax db 20
   namelen db ?
   nameinput  db  20 dup(' ')
   nameoutput db  20 dup(' '),0dh,0ah,'$'
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
    mov  es,ax
    
    lea  dx,msg1
    mov  ah,9
    int  21h
    
    lea  dx,msg2
    mov  ah,9
    int  21h
    mov  ah,1
    int  21h

    lea  dx,crlf
    mov  ah,9
    int  21h

    lea  dx,msg3
    mov  ah,9
    int  21h
    mov  dl,al
    mov  ah,2
    int  21h
  

    lea  dx,crlf
    mov  ah,9
    int  21h
    lea  dx,msg4
    mov  ah,9
    int  21h

    lea  dx,namemax
    mov  ah,10
    int  21h

    

    lea  dx,crlf
    mov  ah,9
    int  21h

    lea  dx,msg3
    mov  ah,9
    int  21h

    mov  cl,namelen
    mov  ch,0
    lea  si,nameinput
    lea  di,nameoutput
    cld
    rep  movsb


    lea  dx,nameoutput
    mov  ah,9
    int  21h
  
    ret          
  main endp        
code ends       
end start        

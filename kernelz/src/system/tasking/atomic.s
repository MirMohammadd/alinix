.globl TestAndSet
TestAndSet:
    mov 4(%esp), %eax  
    mov 8(%esp), %edx  
    lock                
    xchgl %eax, (%edx)    
                        
                        
    ret                 
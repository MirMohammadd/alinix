.globl TestAndSet
TestAndSet:
    movl 4(%esp),%eax  
    movl 8(%esp),%edx 
    lock               
    xchgl %eax,(%edx)                    
                       
                      
    ret               
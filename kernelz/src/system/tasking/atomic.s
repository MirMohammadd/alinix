.globl TestAndSet
TestAndSet:
    mov 4(%esp), %eax  ; get new_value into %eax
    mov 8(%esp), %edx  ; get lock_pointer into %edx
    lock                ; next instruction is locked
    xchgl %eax, (%edx)  ; swap %eax with what is stored in (%edx)                       
                        ; ... and don't let any other CPU touch that
                        ; ... memory location while you're swapping
    ret                 ; return the old value that's in %eax
extern end_proc

; Saves the program's main return value, then calls the real end process function
global end_process
end_process:
    push ebx
    call end_proc
    ret    ; We won't ever reach this point
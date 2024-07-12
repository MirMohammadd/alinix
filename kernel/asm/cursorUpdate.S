Cursor:
VGA.Width equ 80

.SetCoords:
; input bx = x, ax = y
; modifies ax, bx, dx

	mov dl, VGA.Width
	mul dl
	add bx, ax

.SetOffset:
; input bx = cursor offset
; modifies al, dx

	mov dx, 0x03D4
	mov al, 0x0F
	out dx, al

	inc dl
	mov al, bl
	out dx, al

	dec dl
	mov al, 0x0E
	out dx, al

	inc dl
	mov al, bh
	out dx, al
	ret
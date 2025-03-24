section .data
    msg db 'Hola, Mundo!', 0     ; # Definimos el mensaje a imprimir

section .text
    global _start                ; # Especifica el punto de entrada

_start:
    ; Escribir mensaje en la salida estándar
    mov eax, 4                  ; # Número de la llamada al sistema para "sys_write"
    mov ebx, 1                  ; # 1 es el descriptor de archivo para la salida estándar (stdout)
    mov ecx, msg                ; # Dirección del mensaje
    mov edx, 13                 ; # Longitud del mensaje
    int 0x80                    ; # Llamada al sistema (interrupción 0x80)

    ; Salir del programa
    mov eax, 1                  ; # Número de la llamada al sistema para "sys_exit"
    xor ebx, ebx                ; # Código de salida (0)
    int 0x80                    ; # Llamada al sistema (interrupción 0x80)

# CONTROL-DE-MEMORIA-KALI-LINUX

C interactúa directamente con el kernel de Linux a través de llamadas al sistema (syscalls). Aquí tienes un ejemplo de cómo se estructuraría un programa en C para realizar una tarea de optimización crítica: limpiar la memoria caché del sistema y ajustar la prioridad de procesos (OOM Killer).
Código en C para Optimización de Memoria (Limpieza de Caché)
Este programa requiere privilegios de root porque interactúa con el sistema de archivos /proc.
-----------------------------------------------------------------------------------------------


´´´ bash

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // 1. Sincronizar archivos en disco antes de limpiar
    printf("[*] Sincronizando datos en disco...\n");
    sync();

    // 2. Abrir el archivo de control del kernel para caché
    int fd = open("/proc/sys/vm/drop_caches", O_WRONLY);
    if (fd == -1) {
        perror("[-] Error: Ejecuta como root (sudo)");
        return 1;
    }

    // 3. Escribir '3' para limpiar: PageCache, dentries e inodes
    // Es la forma más agresiva de liberar RAM "fantasma"
    printf("[*] Liberando PageCache, dentries e inodes...\n");
    if (write(fd, "3", 1) == -1) {
        perror("[-] Error al escribir en drop_caches");
        close(fd);
        return 1;
    }

    close(fd);
    printf("[+] Optimización de memoria completada.\n");

    return 0;
}

´´´

--------------------------------------------------------------------------------------------------------------------------------------
Usa el código con precaución.


    Acceso Directo a Descriptores de Archivo: Usamos open() y write() de bajo nivel, lo que evita la sobrecarga de las funciones de alto nivel de Python.
    Gestión de Memoria (Stack vs Heap): Este programa usa una cantidad despreciable de RAM (unos pocos KB), mientras que el intérprete de Python consume varios MB solo al arrancar.
    Llamada sync(): En C, esta función es una instrucción directa al kernel para que asegure la integridad de los datos antes de vaciar la memoria.

Cómo optimizar Kali Linux para auditorías pesadas
Si tu objetivo es que Kali funcione mejor durante un ataque de fuerza bruta o escaneo masivo, tres técnicas de bajo nivel:

    Ajuste del OOM Score: Puedes escribir un programa en C que cambie el valor de /proc/[PID]/oom_score_adj a -1000. Esto le dice al kernel: "No mates este proceso aunque te quedes sin RAM". Es vital para que tus herramientas de auditoría no se cierren solas.
    Afinidad de CPU: Usa la librería <sched.h> en C para anclar tu exploit a un núcleo específico de la CPU (CPU_SET). Esto evita que el sistema operativo mueva el proceso entre núcleos, reduciendo la latencia.
    Huge Pages: Configura el uso de "páginas de memoria grandes" para que las herramientas que manejan bases de datos enormes (como diccionarios de contraseñas de GBs) no saturen la tabla de páginas del procesador.

Para ejecutar el código anterior:

    Guárdalo como optimizar.c.
    Compílalo: gcc optimizar.c -o optimizar.
    Ejecútalo: sudo ./optimizar.

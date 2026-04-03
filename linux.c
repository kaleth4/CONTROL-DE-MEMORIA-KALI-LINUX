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
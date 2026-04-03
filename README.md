
<div align="right">
    
<img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C Language">
<img src="https://img.shields.io/badge/Kali_Linux-557C94?style=for-the-badge&logo=kali-linux&logoColor=white" alt="Kali Linux">
<img src="https://img.shields.io/badge/Kernel_Level-000000?style=for-the-badge&logo=linux&logoColor=white" alt="Linux Kernel">
<img src="https://img.shields.io/badge/Root_Required-FF0000?style=for-the-badge&logo=sudo&logoColor=white" alt="Root">
<img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C Language">
<img src="https://img.shields.io/badge/Kali_Linux-557C94?style=for-the-badge&logo=kali-linux&logoColor=white" alt="Kali Linux">
<img src="https://img.shields.io/badge/Kernel_Level-000000?style=for-the-badge&logo=linux&logoColor=white" alt="Linux Kernel">
<img src="https://img.shields.io/badge/Root_Required-FF0000?style=for-the-badge&logo=sudo&logoColor=white" alt="Root">
![Python](https://img.shields.io/badge/Python-3.7+-blue?style=for-the-badge&logo=python&logoColor=white)
-----------------------------------------------------------------------------------------------------------------------------------------------------------
🧠 Control de Memoria Kali Linux
Optimización de Bajo Nivel y Gestión de Recursos con C
-----------------------------------------------------------------------------------------------------------------------------------------------------------

Una herramienta ligera y directa que interactúa con el kernel de Linux a través de llamadas al sistema (syscalls) para realizar tareas de optimización crítica, limpiar la memoria caché y preparar el sistema para auditorías pesadas.

🚀 Compilación y Uso • 💻 Código Fuente • 💡 Funcionamiento Interno • ⚠️ Precauciones

</div>

📋 Tabla de Contenidos


🎯 ¿Por qué usar C para esto?

💻 Código de Optimización

🚀 Compilación y Ejecución

💡 Funcionamiento Interno

🛠️ Técnicas para Auditorías Pesadas

⚠️ Advertencia y Precauciones

✨ Características Principales
<table>
<tr>
<td width="50%">

⚡ Ejecución de Bajo Nivel
Interacción directa con el sistema de archivos /proc mediante syscalls nativas, evitando la sobrecarga de lenguajes interpretados.

</td>
<td width="50%">

🧹 Limpieza Profunda
Liberación de PageCache, dentries e inodes (modo 3), la forma más agresiva de recuperar RAM "fantasma".

</td>
</tr>
<tr>
<td width="50%">

🛡️ Seguridad de Datos
Sincronización previa forzada (sync()) para garantizar que ningún dato en memoria se pierda antes del vaciado.

</td>
<td width="50%">

🪶 Consumo Mínimo
Utiliza una cantidad despreciable de memoria (unos pocos KB), ideal para entornos ya saturados.

</td>
</tr>
</table>

🎯 ¿Por qué usar C para esto?
Mientras que un script en Python podría realizar una tarea similar, el intérprete de Python consume varios megabytes solo al arrancar. Al utilizar C, interactuamos directamente con el kernel de Linux a través de llamadas al sistema. Esto garantiza que el script de optimización no se convierta en un problema de memoria adicional cuando el sistema ya está bajo estrés (por ejemplo, durante un escaneo masivo o un ataque de fuerza bruta).

💻 Código de Optimización
Este programa requiere privilegios de root porque necesita escribir en los archivos de configuración del kernel en tiempo real.


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

---------------------------
🚀 Compilación y Ejecución
Para poner en marcha esta herramienta en tu entorno Kali Linux, sigue estos sencillos pasos:

Bash
# 1. Guarda el código en un archivo
nano optimizar.c

# 2. Compila el código fuente usando GCC
gcc optimizar.c -o optimizar

# 3. Ejecuta el binario resultante con privilegios de superusuario
sudo ./optimizar
💡 Funcionamiento Interno
¿Qué hace que este código sea eficiente?

Llamada sync(): En C, esta función es una instrucción directa al kernel para que asegure la integridad de los datos, escribiendo cualquier búfer pendiente en el disco físico antes de vaciar la memoria.

Acceso Directo a Descriptores de Archivo: Usamos open() y write() de bajo nivel. Al no pasar por librerías de alto nivel, la ejecución es instantánea.

Gestión de Memoria (Stack vs Heap): Este programa opera casi enteramente en el stack, evitando la fragmentación y el uso del heap, lo que lo hace ridículamente ligero frente a cualquier script en Bash o Python.

🛠️ Técnicas para Auditorías Pesadas
Si tu objetivo es que Kali funcione de manera impecable durante un ataque de fuerza bruta o un escaneo masivo de red, complementa este script con estas tres técnicas de bajo nivel:

<div align="center">

Técnica	Objetivo	Implementación
🎯 Ajuste del OOM Score	Evitar que el OOM Killer cierre tus herramientas	Escribir -1000 en /proc/[PID]/oom_score_adj. Le dice al kernel: "No mates este proceso aunque te quedes sin RAM".
🧲 Afinidad de CPU	Reducir la latencia y evitar cambios de contexto	Usar <sched.h> (maco CPU_SET) en C para anclar un exploit o escáner a un núcleo específico del procesador.
📖 Huge Pages	Optimizar el manejo de bases de datos/diccionarios enormes	Configurar páginas de memoria grandes para que no se sature la tabla de páginas del procesador al cargar diccionarios de varios GBs.
</div>

⚠️ Advertencia y Precauciones
<div align="center">

🛡️ USA CON PRECAUCIÓN EN PRODUCCIÓN
</div>

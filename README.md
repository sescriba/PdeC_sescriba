# CESE Protocolos de Comunicacion en Sistemas Embebidos#
========================================================
Driver para modulo IMU MPU9250
------------------------------

** Introduccion **
El proyecto contenido en este repositorio formula un Driver generico para un IMU (Unidad de Medicion Inercial, por sus siglas en ingles) MPU9250 que, mediante comunicacion I2C, permite obtener los valores del Giroscopo, aceleracion y temperatura medidos por el dispositivo. Dada su portabilidad, es posible cambiar de sensor inercial simplemente modificando las direcciones de los registros intervinientes. Tambien es posible alternar el protocolo de comunicacion sin necesidad de modificar el alto nivel del software.

** Implementacion **
El driver es del tipo no bloqueante mediante el uso de interrupciones. A su vez se encuentra modularizado en capas segun el diagrama a continuacion.

dev/
├── inc
│   ├── mpu9250.h
│   └── port.h
└── src
    ├── mpu9250.c
    └── port.c

** Ejemplo **
Finalmente, se adjunta un ejemplo de aplicacion, donde se encuentra implementada una MEF capaz de exponer los valores devueltos mediante UART.

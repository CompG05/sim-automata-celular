# Juego de la Vida

Trabajo práctico para Simulación

Autores:

- D'Autilio Joel
- Rossi Pablo

Este trabajo es una implementación en PowerDEVS del Juego de la Vida de Conway

## Archivos

- El directorio [atomics/](atomics) contiene las definiciones de los modelos atómicos 'célula' y 'escritor'.
- [examples/](examples) contiene modelos de tableros del juego de la vida de diferentes dimensiones.
- [patrones/](patrones) contiene archivos con configuraciones iniciales de diferentes patrones.
- [Vida.pdl](Vida.pdl) es una librería que puede ser incorporada a PowerDEVS y contiene los modelos atómicos y modelos acoplados con tableros de diferentes dimensiones.
- [imprimir_estados.py](imprimir_estados.py) y [setup.sh](setup.sh) son scripts útiles.


## Uso

Se recomienda clonar este repositorio dentro de la carpeta root-powerdevs/sim-automata-celular/ donde root-powerdevs es el directorio raiz de powerdevs (el que contiene los directorios engine y atomics).

    git clone https://github.com/CompG05/sim-automata-celular.git
    cd sim-automata-celular

### PowerDEVS

Primero es necesario copiar el contenido del directorio [atomics/](atomics) a root-powerdevs/atomics/vida/. Esto se facilita con el script [setup.sh](setup.sh).

    ./setup.sh

#### Librería
Se puede incluír la librería a PowerDEVS a través de Options -> Add/Remove library y buscar el archivo [Vida.pdl](Vida.pdl). Ésta provee tres modelos acoplados con tableros de 2x2, 4x4 y 8x8 listos para ser ejecutados, además de los modelos atómicos de célula y escritor.

#### Configuración inicial

Los modelos leen su configuración inicial desde el archivo sim-automata-celular/estado.txt, el cual debe ser modificado para definir nuevas condiciones iniciales. Su formato es el siguiente:

    <cantidad de filas>
    <cantidad de columnas>
    <estado inicial (matriz de 0's y 1's)>
    <reglas de supervivencia>
    <reglas de nacimiento>
    <tiempo entre estados>

Notar que las dimensiones del archivo deben coincidir con las del modelo a utilizar.

#### Ejemplo de estado.txt

    4
    4
    0100
    0100
    0100
    0000
    23
    3
    0.5

#### Patrones
El directorio [patrones/](patrones) contiene archivos de configuración inicial de diferentes patrones. Para utilizarlos se deben copiar reemplazando al archivo [estado.txt](estado.txt). Por ejemplo:
    
    cp patrones/8x8/naves/nave_ligera.txt estado.txt

### Salida producida

El atómico escritor toma como parámetro el nombre archivo de salida. Por defecto, cada modelo escribe en el archivo root-powerdevs/output/output.csv una salida con una secuencia de estados expresados como cadena de 0's y 1's con su correspondiente tiempo. El formato es el siguiente:

    <t_0>, <estado_0>
    <t_1>, <estado_1>
    ...
    <t_n>, <estado_n>

#### Ejemplo de salida

    0, 0100010001000000
    1, 0000111000000000
    2, 0100010001000000
    ...

#### Visualización de la salida

Para visualizar fácilmente la salida se provee el script [imprimir_estados.py](imprimir_estados.py) que requiere instalar las dependencias. Se recomienda hacerlo dentro de un ambiente de python

    python3 -m venv .env
    source .env/bin/activate

    python3 -m pip install -r requirements.txt

El script permite visualizar la secuencia de estados tanto en consola como a través de matplotlib. También permite mostrar la secuencia con avance automático o manual.

#### Ejemplos de Visualización

Mostrar los tableros con matplotlib
    
    python imprimir_estados.py ../output/output.csv

Mostrar los tableros por consola
    
    python imprimir_estados.py ../output/output.csv -c

Mostrar los tableros por consola con avance manual
    
    python imprimir_estados.py ../output/output.csv -cm

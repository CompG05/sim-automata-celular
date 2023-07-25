import argparse
import math
import time
import matplotlib.pyplot as plt

VIVO = " ■ "
MUERTO = " - "

def imprimir_estado(tiempo, board):
    board = como_matriz(board)
    print(f"Tiempo: {tiempo}")

    print("-", end='')
    for x in range(len(board[0])):
        print("---", end='')
    print("-")
    for x in range(len(board)):
        print("|", end='')
        for y in range(len(board[x])):
            if board[x][y] == 0:
                print(MUERTO, end='')
            else:
                print(VIVO, end='')
        print("|")
    print("-", end='')
    for x in range(len(board[0])):
        print("---", end='')
    print("-")
    return 0


def plotear(tiempo, estado):
    estado = como_matriz(estado)

    # Obtener las dimensiones de la matriz
    filas = len(estado)
    columnas = len(estado[0])

    # Graficar la matriz utilizando imshow
    plt.imshow(estado, cmap='binary')

    # Dibujar líneas de cuadrícula
    plt.hlines([i - 0.5 for i in range(filas + 1)], xmin=-0.5, xmax=columnas - 0.5, colors='black', linewidth=1)
    plt.vlines([i - 0.5 for i in range(columnas + 1)], ymin=-0.5, ymax=filas - 0.5, colors='black', linewidth=1)

    # Eliminar los números de los ejes
    plt.xticks([])
    plt.yticks([])

    # Agregar título al gráfico
    plt.title(f"Tiempo: {tiempo}")


def como_matriz(estado):
    dimension = int(math.sqrt(len(estado)))
    matriz = []
    for i in range(dimension):
        fila = []
        for j in range(dimension):
            fila.append(estado[i * dimension + j])
        matriz.append(fila)

    return matriz


def leer_archivo(nombre_archivo):
    estados = []
    tiempos = []
    with open(nombre_archivo, 'r') as archivo:
        for linea in archivo:
            valores = linea.split(',')
            estado = [int(valor) for valor in valores[1].strip()]
            estados.append(estado)
            tiempos.append(float(valores[0]))
    return tiempos, estados


def main():
    #Parseo de argumentos
    parser = argparse.ArgumentParser(prog='imprimir_Estados', description='Impresión de estados del juego de la vida',
                                     epilog='Simulación 2023')
    parser.add_argument('-m', '--manual', action='store_true', help="Comando manual para obtener el siguiente estado (default: tiempo de simulación)")
    parser.add_argument('-c', '--consola', action='store_true', help="Opción para graficar por consola (default: por matplotlib)")
    parser.add_argument("archivo",
                        action="store",
                        help="Archivo de entrada con estados del juego de la vida")
    args = parser.parse_args()

    #Lectura del archivo e impresión de estados
    tiempos, estados = leer_archivo(args.archivo)
    tiempos_estados = list(zip(tiempos, estados))
    espera = tiempos[1]

    if args.manual:
        if args.consola:

            # Manual y por consola
            for tiempo, estado in tiempos_estados:
                imprimir_estado(tiempo, estado)
                input()
        else:

            # Manual y por matplotlib
            for tiempo, estado in tiempos_estados:
                plotear(tiempo, estado)
                plt.show()

    elif args.consola:

        # Automático y por consola
        for tiempo, estado in tiempos_estados:
            time.sleep(espera)
            imprimir_estado(tiempo, estado)

    else:

        # Automático y por matplotlib
        for tiempo, estado in tiempos_estados:
            plt.pause(espera)
            plotear(tiempo, estado)
        plt.show()


if __name__ == '__main__':
    main()

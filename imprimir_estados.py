import argparse
from matplotlib import pyplot as plt
import math
import time

VIVO = " ■ "
MUERTO = " - "

def imprimir_estado_consola(board):
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


def imprimir_estado(board):
    plt.figure(figsize=(15, 15))
    plt.imshow(board)
    plt.show()


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
    parser = argparse.ArgumentParser(prog='Imprimir_Estados', description='Impresión de estados del juego de la vida',
                                     epilog='Simulación 2023')
    parser.add_argument('-m', '--manual', action='store_true', help="Comando manual para obtener el siguiente estado (default: tiempo de simulación)")
    parser.add_argument('-p', '--plot', action='store_true', help="Opción para graficar con matplotlib (default: por consola)")
    parser.add_argument("-a", "--archivo",
                        action="store",
                        default="output.csv",
                        help="Archivo de entrada con estados del juego de la vida (default: output.csv)")
    args = parser.parse_args()

    #Lectura del archivo e impresión de estados
    tiempos, estados = leer_archivo(args.archivo)
    tiempos_estados = zip(tiempos, estados)

    if args.manual:
        for tiempo, estado in tiempos_estados:
            print(f"Tiempo: {tiempo}")
            if args.plot:
                imprimir_estado(como_matriz(estado))
            else:
                imprimir_estado_consola(como_matriz(estado))
            input()
    else:
        tiempo_anterior = 0
        if args.plot:
            fig, ax = plt.subplots()
            for tiempo, estado in tiempos_estados:
                ax.clear()
                ax.set_title("Juego de la vida")
                ax.imshow(como_matriz(estado), cmap='binary')
                plt.pause(tiempo - tiempo_anterior)
                ax.set_aspect('equal')
                tiempo_anterior = tiempo
            plt.show()
        else:
            for tiempo, estado in tiempos_estados:
                time.sleep(tiempo - tiempo_anterior)
                print(f"Tiempo: {tiempo}")
                imprimir_estado_consola(como_matriz(estado))
                print()
                tiempo_anterior = tiempo


if __name__ == '__main__':
    main()

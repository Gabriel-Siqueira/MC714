import sys
import random
import socket
import _thread
import time

# constantes do socket
PORT_BASE = 5000
HOST = "localhost"
QUEUE = 1
BUF_SIZE = 1024

# processo inicial
INI = 0

# mensagens
SEI = "ja sabia"
NSEI = "nao sabia"
DATA = "alguma novidade"

def cliente(my_data,n,k):
    """ Realiza fofoca com a informacao recebida.

    :data: informação nova
    :n: numero de processos
    :k: numero para o calculo da chance de parada

    """

    tentativas = 0
    sucesso = 0
    while 1:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            s.connect((HOST, PORT_BASE + random.randrange(0,n)))
        except socket.error:
            continue
        s.sendall(my_data)
        tentativas += 1
        data = s.recv(BUF_SIZE).decode()
        if data == SEI:
            if random.randrange(0,k) == 0:
                print("processo: {0:02d}, tentativas: {1}, sucesso: {2}".format(num,tentativas,sucesso))
                exit(0)
        else:
            sucesso += 1
        time.sleep(1)
        s.close()

def servidor(my_data, num, n, k):
    """ Espera receber informação e responde se ela é nova ou nao.

    :my_data: dado atual do processo
    :num: identificador do processo
    :n: numero de processos
    :k: numero para o calculo da chance de parada

    """
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((HOST, PORT_BASE + num))
    s.listen(QUEUE)

    while 1:
        s.settimeout(60)
        try:
            conn, addr = s.accept()
        except socket.error:
            exit(0)
        data = conn.recv(BUF_SIZE).decode()
        if not data: continue
        if data == my_data:
            conn.send(SEI.encode())
        else:
            conn.send(NSEI.encode())
            my_data = data
            thr = _thread.start_new_thread(cliente,(my_data.encode(),n,k))
        conn.close()
    s.close()

if __name__ == "__main__":
    num = int(sys.argv[1])
    n = int(sys.argv[2])
    k = int(sys.argv[3])

    if num == INI:
        my_data = DATA
        thr = _thread.start_new_thread(cliente,(my_data.encode(),n,k))
    else:
        my_data = ""

    servidor(my_data, num, n, k)

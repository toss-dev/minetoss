__author__ = 'ppanos'
import socket
import threading
import sys
 
port = 4242
thread_count = 1000

def worker():
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.connect(('127.0.0.1',port))
        
        try:
                message = ''.join(chr(x) for x in [
                        0xFF, 0xFF, 0xFF, 0xFF,
                        0x00, 0x00,
                        0x00, 0x00, 0x00, 0x00])

                sock.sendall(message)
                amount_received = 0
                amount_expected = 50
                while amount_received < amount_expected:
                        data = sock.recv(16)
                        amount_received += len(data)
                        print >> sys.stdout, 'received "%s"' % data
        finally:
                sock.close()
                return
 
threads = []
for i in range(thread_count):
        try:
                t = threading.Thread(target=worker)
        except:
                print >> sys.stdout, 'lol'
                continue
        threads.append(t)
        t.start()
#!/usr/bin/python3

from scapy.all import *
import sys
import time

def send_icmp_error(real_src, real_dst, seq, error_type):
    """
    Envoie un paquet ICMP d'erreur simulé pour tester `ping`.

    Args:
        real_src (str): Adresse IP source du ping original.
        real_dst (str): Adresse IP cible du ping original.
        seq (int): Numéro de séquence ICMP attendu par le ping.
        error_type (str): Type d'erreur ICMP à simuler ('ttl_exceeded', 'dest_unreachable').
    """
    print(f"Envoi d'une erreur ICMP {error_type} de {real_dst} vers {real_src}, seq={seq}")

    # Construire le paquet "original" encapsulé
    original_ip = IP(src=real_src, dst=real_dst)
    original_icmp = ICMP(type=8, code=0, seq=seq)

    # Construire le paquet d'erreur ICMP
    if error_type == "ttl_exceeded":
        icmp_error = ICMP(type=11, code=0)  # TTL exceeded
    elif error_type == "dest_unreachable":
        icmp_error = ICMP(type=3, code=1)  # Host unreachable
    else:
        print(f"Erreur inconnue : {error_type}")
        return

    # Construire le paquet final
    error_packet = IP(src=real_dst, dst=real_src)/icmp_error/original_ip/original_icmp

    # Envoyer le paquet
    send(error_packet, verbose=True)

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage : sudo python3 script.py <src_ip> <dst_ip> [<error_type>]")
        print("Types d'erreur possibles : ttl_exceeded, dest_unreachable")
        sys.exit(1)

    real_src = sys.argv[1]  # Source du ping
    real_dst = sys.argv[2]  # Destination cible
    error_type = sys.argv[3] if len(sys.argv) > 3 else "ttl_exceeded"

    print(f"Source IP : {real_src}, Destination IP : {real_dst}, Erreur : {error_type}")
    print("Exécutez `ping` depuis une autre fenêtre avec la destination comme cible.")

    seq = 1
    try:
        while True:
            send_icmp_error(real_src, real_dst, seq, error_type)
            time.sleep(1)
            seq += 1
    except KeyboardInterrupt:
        print("\nInterruption reçue. Fin du script.")

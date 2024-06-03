import matplotlib.pyplot as plt
import numpy as np
import csv

# Ouvrir le fichier CSV pour lecture
with open('data.csv', 'r') as csvfile:
    csvreader = csv.reader(csvfile, delimiter=';')

    # Lire les en-têtes de colonnes
    headers = next(csvreader)

    # Initialiser les listes pour les données
    time = []
    Vc_dt_c = []
    Vc_reel_c = []
    ecart_c = []
    Vc_dt_d = []
    Vc_reel_d = []
    v_alt_pb = []
    Vc_dt_pb = []
    v_alt_ph = []
    Vr_dt = []

    # Lire les données ligne par ligne
    for row in csvreader:
        time.append(float(row[0]))
        Vc_dt_c.append(float(row[1]))
        Vc_reel_c.append(float(row[2]))
        ecart_c.append(float(row[3]))
        Vc_dt_d.append(float(row[4]))
        Vc_reel_d.append(float(row[5]))
        v_alt_pb.append(float(row[6]))
        Vc_dt_pb.append(float(row[7]))
        v_alt_ph.append(float(row[8]))
        Vr_dt.append(float(row[9]))

# Convertir les listes en arrays numpy pour la manipulation et le traçage
time = np.array(time)
Vc_dt_c = np.array(Vc_dt_c)
Vc_reel_c = np.array(Vc_reel_c)
ecart_c = np.array(ecart_c)
Vc_dt_d = np.array(Vc_dt_d)
Vc_reel_d = np.array(Vc_reel_d)
v_alt_pb = np.array(v_alt_pb)
Vc_dt_pb = np.array(Vc_dt_pb)
v_alt_ph = np.array(v_alt_ph)
Vr_dt = np.array(Vr_dt)

# Tracer les graphiques
plt.figure(figsize=(10, 8))

# Charge du condensateur
plt.subplot(3, 2, 1)
plt.plot(time, Vc_dt_c, label='Vc_dt_c')
plt.plot(time, Vc_reel_c, label='Vc_reel_c')
plt.title('Charge du Condensateur')
plt.xlabel('Temps [s]')
plt.ylabel('Tension [V]')
plt.legend()
plt.grid(True)

# Décharge du condensateur
plt.subplot(3, 2, 2)
plt.plot(time, Vc_dt_d, label='Vc_dt_d')
plt.plot(time, Vc_reel_d, label='Vc_reel_d')
plt.title('Décharge du Condensateur')
plt.xlabel('Temps [s]')
plt.ylabel('Tension [V]')
plt.legend()
plt.grid(True)

# Filtre passe-bas (signal d'entrée et filtré)
plt.subplot(3, 2, 3)
plt.plot(time, v_alt_pb, label='v_alt_pb')
plt.plot(time, Vc_dt_pb, label='Vc_dt_pb')
plt.title('Filtre Passe-Bas')
plt.xlabel('Temps [s]')
plt.ylabel('Tension [V]')
plt.legend()
plt.grid(True)

# Filtre passe-haut (signal d'entrée et filtré)
plt.subplot(3, 2, 4)
plt.plot(time, v_alt_ph, label='v_alt_ph')
plt.plot(time, Vr_dt, label='Vr_dt')
plt.title('Filtre Passe-Haut')
plt.xlabel('Temps [s]')
plt.ylabel('Tension [V]')
plt.legend()
plt.grid(True)

# Écart de la charge
plt.subplot(3, 2, 5)
plt.plot(time, ecart_c, label='Ecart Charge')
plt.title('Écart de la Charge')
plt.xlabel('Temps [s]')
plt.ylabel('Écart [V]')
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()

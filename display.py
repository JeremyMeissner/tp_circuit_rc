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
    v_alt_pb = []
    Vc_dt_pb = []
    v_alt_ph = []
    Vr_dt = []
    current_low_pass_capacitor_voltage = []
    current_high_pass_capacitor_voltage = []
    discharge_low_pass = []
    discharge_high_pass = []

    # Lire les données ligne par ligne
    for row in csvreader:
        time.append(float(row[0]))
        v_alt_pb.append(float(row[1]))
        Vc_dt_pb.append(float(row[2]))
        v_alt_ph.append(float(row[3]))
        Vr_dt.append(float(row[4]))
        current_low_pass_capacitor_voltage.append(float(row[5]))
        current_high_pass_capacitor_voltage.append(float(row[6]))
        discharge_low_pass.append(float(row[7]))
        discharge_high_pass.append(float(row[8]))

# Convertir les listes en arrays numpy pour la manipulation et le traçage
time = np.array(time)
v_alt_pb = np.array(v_alt_pb)
Vc_dt_pb = np.array(Vc_dt_pb)
v_alt_ph = np.array(v_alt_ph)
Vr_dt = np.array(Vr_dt)
current_low_pass_capacitor_voltage = np.array(
    current_low_pass_capacitor_voltage)
current_high_pass_capacitor_voltage = np.array(
    current_high_pass_capacitor_voltage)
discharge_low_pass = np.array(discharge_low_pass)
discharge_high_pass = np.array(discharge_high_pass)

# Tracer les graphiques
plt.figure(figsize=(10, 8))

# # Charge du condensateur
# plt.subplot(3, 2, 1)
# plt.plot(time, Vc_dt_c, label='Vc_dt_c')
# plt.title('Charge du Condensateur')
# plt.xlabel('Temps [s]')
# plt.ylabel('Tension [V]')
# plt.legend()
# plt.grid(True)

# # Décharge du condensateur
# plt.subplot(3, 2, 2)
# plt.plot(time, Vc_dt_d, label='Vc_dt_d')
# plt.title('Décharge du Condensateur')
# plt.xlabel('Temps [s]')
# plt.ylabel('Tension [V]')
# plt.legend()
# plt.grid(True)

plt.subplot(3, 3, 1)
plt.plot(time, v_alt_pb, label='signal')
plt.title('Signal original')
plt.xlabel('Temps [s]')
plt.ylabel('Tension [V]')
plt.legend()
plt.grid(True)

plt.subplot(3, 3, 2)
plt.plot(time, Vc_dt_pb, label='signal')
plt.title('Filtre passe-bas')
plt.xlabel('Temps [s]')
plt.ylabel('Tension [V]')
plt.legend()
plt.grid(True)


# Filtre passe-bas (signal d'entrée et filtré)
plt.subplot(3, 3, 4)
plt.plot(time, v_alt_pb, label='signal')
plt.title('Signal original')
plt.xlabel('Temps [s]')
plt.ylabel('Tension [V]')
plt.legend()
plt.grid(True)

# Filtre passe-haut (signal d'entrée et filtré)
plt.subplot(3, 3, 5)
plt.plot(time, Vr_dt, label='signal')
plt.title('Filtre passe-Haut')
plt.xlabel('Temps [s]')
plt.ylabel('Tension [V]')
plt.legend()
plt.grid(True)


limit = 2000

# Charge capacitor fitre passe-bas
plt.subplot(3, 3, 3)
plt.plot(time[:limit],
         current_low_pass_capacitor_voltage[:limit], label='signal')
plt.title('Charge/décharge')
plt.xlabel('Temps [s]')
plt.ylabel('Tension [V]')
plt.legend()
plt.grid(True)

# Charge capacitor fitre passe-bas
plt.subplot(3, 3, 3)
plt.plot(time[:limit], discharge_low_pass[:limit], label='signal')
plt.title('Charge/décharge')
plt.xlabel('Temps [s]')
plt.ylabel('Tension [V]')
plt.legend()
plt.grid(True)


limit = 200


# Charge capacitor fitre passe-haut
plt.subplot(3, 3, 6)
plt.plot(time[:limit],
         current_high_pass_capacitor_voltage[:limit], label='signal')
plt.title('Charge/décharge')
plt.xlabel('Temps [s]')
plt.ylabel('Tension [V]')
plt.legend()
plt.grid(True)


# Charge capacitor fitre passe-haut
plt.subplot(3, 3, 6)
plt.plot(time[:limit], discharge_high_pass[:limit], label='signal')
plt.title('Charge/décharge')
plt.xlabel('Temps [s]')
plt.ylabel('Tension [V]')
plt.legend()
plt.grid(True)


plt.tight_layout()
plt.show()


# TODO, faire un graph des condensateurs par filtre

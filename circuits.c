#include <stdio.h>  // Inclusion de la bibliothèque standard d'entrées/sorties
#include <stdlib.h> // Inclusion de la bibliothèque standard pour les fonctions utilitaires
#include <math.h>   // Inclusion de la bibliothèque mathématique

#define RESISTANCE_VALUE 100 // ohm

double compute_capacitor_value(double cutoff_fre) {
    double capcitor_value = 1 / (2 * M_PI * RESISTANCE_VALUE * cutoff_fre);
    return capcitor_value;
}

int main()
{

    double delta_t = 0.001; // Intervalle de temps pour les calculs (pas de temps)
    double signal_duration = 1;

    double low_frequency = 3; // hz
    double high_frequency = 55; // hz

    double low_cutoff_frequency = 5; // hz
    double high_cutoff_frequency = 55; // hz


    double high_pass_capacity = compute_capacitor_value(high_cutoff_frequency);
    double low_pass_capacity = compute_capacitor_value(low_cutoff_frequency);

    // Conditions initiales pour la charge du condensateur
    double V_initial_c = 2.0; // Tension initiale pour la charge

    double Vr_dt = 0.0;      // Tension sur la résistance à l'instant dt

    double Vc_dt_pb = 0.0; // Tension pour le filtre passe-bas à l'instant dt
    double Vc_dt_ph = 0.0; // Tension pour le filtre passe-haut à l'instant dt

    double V_amplitude = 2.0; // Amplitude de la tension alternative

    // Ouverture du fichier CSV pour écrire les données
    FILE *fp = fopen("data.csv", "w");

    // Écriture des en-têtes de colonnes dans le fichier CSV
    fprintf(fp, "time,v_alt_pb,Vc_dt_pb,v_alt_ph,Vr_dt\n");

    int counter = 0; // Compteur pour le nombre d'itérations
    double time = 0; // Variable de temps


    double low_frequency_signal;
    double high_frequency_signal;
    // Boucle pour le filtre passe-bas
    while (time < signal_duration)
    {
        // Calcul du courant alternatif
        double signal;

        low_frequency_signal = V_amplitude * sin(2 * M_PI * low_frequency * time); // Tension alternative pour le filtre passe-bas
        high_frequency_signal = V_amplitude * sin(2 * M_PI * high_frequency * time); // Tension alternative pour le filtre passe-haut

        signal = low_frequency_signal + high_frequency_signal;

        // Filtre passe-bas
        Vc_dt_pb = Vc_dt_pb + (((signal - Vc_dt_pb) * delta_t) / (RESISTANCE_VALUE * low_pass_capacity)); // Mise à jour de la tension pour le filtre passe-bas

        // Filtre passe-haut
        Vc_dt_ph = Vc_dt_ph + (((signal - Vc_dt_ph) * delta_t) / (RESISTANCE_VALUE * high_pass_capacity)); // Mise à jour de la tension pour le filtre passe-haut
        Vr_dt = signal - Vc_dt_ph;                                          // Calcul de la tension sur la résistance pour le filtre passe-haut

        // Écriture des données dans le fichier CSV
        fprintf(fp, "%lf;%f;%f;%f;%f\n", time, signal, Vc_dt_pb, signal, Vr_dt);

        counter++;  // Incrémentation du compteur
        time += delta_t; // Incrémentation du temps
    }

    // Fermeture du fichier CSV
    fclose(fp);

    return EXIT_SUCCESS; // Retourne un succès à la fin du programme
}

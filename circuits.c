#include <stdio.h>  // Inclusion de la bibliothèque standard d'entrées/sorties
#include <stdlib.h> // Inclusion de la bibliothèque standard pour les fonctions utilitaires
#include <math.h>   // Inclusion de la bibliothèque mathématique

#define PI 3.141593 // Définition de la constante PI

int main()
{

    double r_c = 1.0; // Résistance du circuit de charge/décharge du condensateur
    double c_c = 1.0; // Capacité du condensateur dans le circuit de charge/décharge
    double dt = 0.01; // Intervalle de temps pour les calculs (pas de temps)

    double r_ph = 0.1; // Résistance pour le filtre passe-haut
    double c_ph = 0.1; // Capacité pour le filtre passe-haut

    double r_pb = 0.1; // Résistance pour le filtre passe-bas
    double c_pb = 0.1; // Capacité pour le filtre passe-bas

    // Conditions initiales pour la décharge du condensateur
    double V_initial_d = 0.0; // Tension initiale pour la décharge
    double Vc_0_d = 2.0;      // Tension initiale réelle pour la décharge
    double Vc_reel_d = 2.0;   // Tension réelle à t = 0 pour la décharge

    // Conditions initiales pour la charge du condensateur
    double V_initial_c = 2.0; // Tension initiale pour la charge
    double Vc_0_c = 0.0;      // Tension initiale réelle pour la charge
    double Vc_reel_c = 0.0;   // Tension réelle à t = 0 pour la charge

    double Vc_dt_c = Vc_0_c; // Tension du condensateur pour la charge à l'instant dt
    double Vc_dt_d = Vc_0_d; // Tension du condensateur pour la décharge à l'instant dt
    double Vr_dt = 0.0;      // Tension sur la résistance à l'instant dt

    double Vc_dt_pb = 0.0; // Tension pour le filtre passe-bas à l'instant dt
    double Vc_dt_ph = 0.0; // Tension pour le filtre passe-haut à l'instant dt

    double V_amplitude = 2.0; // Amplitude de la tension alternative

    // Ouverture du fichier CSV pour écrire les données
    FILE *fp = fopen("data.csv", "w");

    // Écriture des en-têtes de colonnes dans le fichier CSV
    fprintf(fp, "time,Vc_dt_c,Vc_reel_c,ecart_c,Vc_dt_d,Vc_reel_d,v_alt_pb,Vc_dt_pb,v_alt_ph,Vr_dt\n");

    int counter = 0; // Compteur pour le nombre d'itérations
    double time = 0; // Variable de temps

    // Fréquence angulaire pour le filtre passe-bas et passe-haut
    double omega_pb = 3; // Fréquence angulaire pour le filtre passe-bas
    double omega_ph = 3; // Fréquence angulaire pour le filtre passe-haut

    double v_alt_pb = 0.0; // Tension alternative pour le filtre passe-bas
    double v_alt_ph = 0.0; // Tension alternative pour le filtre passe-haut

    double ecart;                 // Écart entre la tension réelle et calculée
    double ecart_carre;           // Carré de l'écart
    double somme_ecart = 0;       // Somme des écarts
    double somme_ecart_carre = 0; // Somme des carrés des écarts

    // Boucle pour le filtre passe-bas
    while (time < 5.0)
    {
        // Calcul de la tension réelle et de l'écart pour la charge du condensateur
        Vc_reel_c = 2 * (1 - exp((-time) / (r_c * c_c)));                   // Calcul de la tension réelle théorique pour la charge
        ecart = Vc_reel_c - Vc_dt_c;                                        // Calcul de l'écart entre la tension réelle et calculée
        ecart_carre = pow(ecart, 2);                                        // Calcul du carré de l'écart
        somme_ecart_carre += ecart_carre;                                   // Ajout de l'écart carré à la somme des écarts carrés
        somme_ecart += ecart;                                               // Ajout de l'écart à la somme des écarts
        Vc_dt_c = Vc_dt_c + (((V_initial_c - Vc_dt_c) * dt) / (r_c * c_c)); // Mise à jour de la tension calculée pour la charge

        // Calcul de la tension réelle pour la décharge du condensateur
        Vc_reel_d = 2 * exp((-time) / (r_c * c_c));                         // Calcul de la tension réelle théorique pour la décharge
        Vc_dt_d = Vc_dt_d + (((V_initial_d - Vc_dt_d) * dt) / (r_c * c_c)); // Mise à jour de la tension calculée pour la décharge

        // Calcul du courant alternatif
        v_alt_pb = V_amplitude * sin(2 * PI * omega_pb * time); // Tension alternative pour le filtre passe-bas
        v_alt_ph = V_amplitude * sin(2 * PI * omega_ph * time); // Tension alternative pour le filtre passe-haut

        // Filtre passe-bas
        Vc_dt_pb = Vc_dt_pb + (((v_alt_pb - Vc_dt_pb) * dt) / (r_pb * c_pb)); // Mise à jour de la tension pour le filtre passe-bas

        // Filtre passe-haut
        Vc_dt_ph = Vc_dt_ph + (((v_alt_ph - Vc_dt_ph) * dt) / (r_ph * c_ph)); // Mise à jour de la tension pour le filtre passe-haut
        Vr_dt = v_alt_ph - Vc_dt_ph;                                          // Calcul de la tension sur la résistance pour le filtre passe-haut

        // Écriture des données dans le fichier CSV
        fprintf(fp, "%lf;%f;%f;%f;%f;%f;%f;%f;%f;%f\n", time, Vc_dt_c, Vc_reel_c, ecart, Vc_dt_d, Vc_reel_d, v_alt_pb, Vc_dt_pb, v_alt_ph, Vr_dt);

        counter++;  // Incrémentation du compteur
        time += dt; // Incrémentation du temps
    }

    // Calcul des statistiques
    double moyenne_ecart = somme_ecart / counter;                              // Calcul de la moyenne des écarts
    double moyenne_ecart_carre = somme_ecart_carre / counter;                  // Calcul de la moyenne des écarts carrés
    double ecart_type = pow(moyenne_ecart_carre - pow(moyenne_ecart, 2), 0.5); // Calcul de l'écart type

    printf("ecart type : %lf\n", ecart_type); // Affichage de l'écart type

    // Fermeture du fichier CSV
    fclose(fp);

    return EXIT_SUCCESS; // Retourne un succès à la fin du programme
}

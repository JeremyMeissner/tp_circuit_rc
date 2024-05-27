#include <stdio.h>
#include <math.h> 

double signal_function(float t){
    //We will here make changes with low pass filters and other shit
    return sin(t);
}

int main() {
    // Generate a file with the values of a sine wave. T will go from 0 to 5 and we have a sample rate of 44100
    int duration = 5;
    int sample_rate = 44100;
    int samples = sample_rate * duration;
    double step = 1.0/44100.0;

    double t = 0;

    double results[samples];

    printf("Generating signal\n");

    for(int i = 0; i < samples; i ++){
        t+= step;
        results[i] = signal_function(t);
    }

    printf("Storing results\n");
    //Store results
    FILE *fptr;
    fptr = fopen("data.txt", "w");

    for(int i = 0; i < samples; i ++){
        char str[100];
        // Convert double to string with full precision
        snprintf(str, sizeof(str), "%.16g", results[i]);
        fprintf(fptr, "%s\n",str);
    }
    fclose(fptr);
    printf("Done\n");
    return 0;
}

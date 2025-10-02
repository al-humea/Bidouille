#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


int main( int ac, char **av )
{
	int rang, size;
	char hn[100];
	gethostname( hn, 100 );
    int nb_msg, nb_ping;

    nb_msg = atoi(av[1]);
    nb_ping = atoi(av[2]);
    int i = 0;
    int j = 0;
    char msg[] = "get that";

	if( MPI_Init( &ac, &av ) )
	{
		fprintf(stderr, "Erreur MPI_Init\n" );
		exit( 1 );
	}
        double begin = MPI_Wtime();

        MPI_Comm_rank( MPI_COMM_WORLD, &rang );
        MPI_Comm_size( MPI_COMM_WORLD, &size );

        char msg_recu[10];
        if (size >= 2){
            for (i = 0; i < nb_ping; i++){
                if (rang == 0){
                    for (j = 0; j < nb_msg; j++){
                        MPI_Ssend(msg, strlen(msg)+1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
                    }
                }
                if (rang == 1){
                    for (j = 0; j < nb_msg; j++){
                        MPI_Status s;
                        MPI_Recv(msg_recu, strlen(msg)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &s);
                    }
                    printf("ping %d\n", i);
                }
            }
        }
        double end = MPI_Wtime();
        double time_spent = end - begin;
        printf("Temps process %d : %f\n", rang, time_spent);
	MPI_Finalize();
	return( 0 );
}

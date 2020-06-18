#include "visualizer.h"
#include <QApplication>
#include <mpi/mpi.h>

int main(int argc, char *argv[]) {

    srand(time(NULL));
    MPI_Init(NULL, NULL);

    int world_rank = 1;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if(world_rank == 0)
        printf("\n\nRUNTIME STARTING HERE\n\n");
    printf("%d\n", world_rank);

    if(world_rank == 0) {
        QApplication a(argc, argv);
        Visualizer w;
        w.setFixedSize(w.geometry().width(), w.geometry().height());
        w.show();

        QObject::connect(&a, &QCoreApplication::aboutToQuit, &a, [&](){ MPI_Finalize(); });
        return a.exec();
    } else {
        //slavery

        MPI_Finalize();
        return 0;
    }
 }

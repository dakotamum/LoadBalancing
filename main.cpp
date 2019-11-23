#include <iostream>
#include <mpi.h>
#include <ctime>
#include <unistd.h>
#include <fstream>
#include <complex>
#include <vector>
#include <chrono>
#include <string>
#include <queue>

#define MCW MPI_COMM_WORLD
#define MASTAH 0

using namespace std;

int main(int argc, char **argv){
	queue<int> myqueue;
	int pid, np, data, iterations;
	int flag = 0;
	MPI_Init(&argc, &argv);MPI_Comm_rank(MCW, &pid);MPI_Comm_size(MCW, &np);
	srand(pid);
	int maxTasksGenerated = rand()%2048 + 1024;
	int tasksDone = 0;

	if(pid == 0){
		// generate first task
		int task = rand()%1024 + 1;
		cout << "I have a task of " << task << endl;
		for(int i = 0; i < task*task; i++){}
		cout << "I have " << maxTasksGenerated << " number of max tasks\n";
		data = 10;
		MPI_Send(&data, 1, MPI_INT, 1, 1, MCW);
		MPI_Send(&data, 1, MPI_INT, 2, 1, MCW);
		MPI_Send(&data, 1, MPI_INT, 3, 1, MCW);
	}

	else{
		while (!flag){
			MPI_Iprobe(MPI_ANY_SOURCE, 1, MCW, &flag, MPI_STATUS_IGNORE);
		}
		MPI_Recv(&data, 1, MPI_INT, MPI_ANY_SOURCE, 1, MCW, MPI_STATUS_IGNORE);
		cout << "I got the message loud and clear\n";
	}

 	MPI_Finalize();
	return 0;
}

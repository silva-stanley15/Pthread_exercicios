#include <iostream>
#include <omp.h>

using namespace std;
#define NUM 50

int main () {
	
	int soma = 0;
	omp_set_num_threads(6);
	#pragma omp parallel sections 
	{
		#pragma omp section
		{
			omp_set_nested(1);
			#pragma omp parallel for reduction(+:soma) num_threads(3)
			for(int i = 0; i < NUM; i++){
				soma++;
				cout << omp_get_thread_num() << endl; 
			}
			cout << omp_get_thread_num() << endl;
		}
	}
	cout << soma << endl;
	return 0;
}

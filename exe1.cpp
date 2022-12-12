#include <iostream>
#include <pthread.h>


using namespace std;

int k = 2, 
    cont, 
    n;

int* vet;

void *crivo (void *a){
    int *elemento = (int *) a;
    cout << "Sou thread: " << elemento << endl;
    
    for (cont=k*k; cont <= n;cont=cont+k){
        vet[cont]=-1;
    }

    k++;
    
    while (vet[k]==-1){
        k++;
    }
    
    cout << k << endl;
        
    pthread_exit(NULL);
    return 0;
}


int main(){

    cin >> n;

    vet = new int[n];

    pthread_t threads[n];
    
    for (cont = 1; cont <= n; cont++){
		vet[cont] = cont;
	}

    while(k*k <= n){
        cout << "Thread principal: criando thread " << k << endl;
        pthread_create(&threads[k], NULL, crivo, &k);
        pthread_join(threads[k], NULL);
    }

	for (cont = 2;cont <= n;cont++){
		if (vet[cont]!=-1) 
		    cout << "Vetor arranjado: " << cont << endl;
	}
    pthread_exit(NULL);
}

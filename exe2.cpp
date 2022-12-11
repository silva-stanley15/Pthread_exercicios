#include <iostream>
#include <pthread.h>

using namespace std;

pthread_t ta, tb;
pthread_mutex_t Mutex;
pthread_mutexattr_t MutexAttr;

int primeiraMetade[5],
    segundaMetade[5], 
    segundoMaior = -1, 
    pares = 0, 
    primeiroMaior = -1, 
    media = 0;

void debug (int* array, int size) {
    for(int i = 0; i < size; i++){
        cout << array[i] << " ";
    }
    cout << endl;
}

void divideArray(int *array){

    for(int i = 0; i < 5; i++){
        primeiraMetade[i] = array[i];
    }
    
    for(int i = 5; i < 10; i++){
        segundaMetade[i - 5] = array[i];
    }
}

void *maiores(void* a){
    int* array = (int *) a;

    for(int i = 0; i < 5; i++){
        
        pthread_mutex_lock(&Mutex);
        
        if(array[i]%2 == 0){
            pares += array[i];
        }

        if(primeiroMaior < array[i]){
            segundoMaior = primeiroMaior;
            primeiroMaior = array[i];
        }

        if(segundoMaior < array[i] && array[i] < primeiroMaior){
            segundoMaior = array[i];
        }

        media += array[i];

        pthread_mutex_unlock(&Mutex);
    }
    
    return 0;
}

int main () {
    int arrayRandom[10];
    for(int i = 0; i < 10; i++){
        arrayRandom[i] = rand()%10;
    }

    divideArray(arrayRandom);

    // exibe o array para validação
    debug(primeiraMetade, 5);
    debug(segundaMetade, 5);

    // debug(arrayRandom, 10);

    cout << " " << endl;

    pthread_mutexattr_init(&MutexAttr);
    pthread_mutex_init(&Mutex, &MutexAttr);

    pthread_create(&ta, NULL, maiores, &primeiraMetade);
    pthread_create(&tb, NULL, maiores, &segundaMetade);

    pthread_join(ta, NULL);
    pthread_join(tb, NULL);

    cout << "Dois maiores: "<< segundoMaior << " " << primeiroMaior << endl;
    cout << "Média dos valores: " << media / 10.00 << endl;
    cout << "Pares: "<< pares << endl;
    return 0;
}

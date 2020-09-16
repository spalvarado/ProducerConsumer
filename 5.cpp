#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include<vector>

using namespace std;

vector<int> buffer(10,0); //buffer size initialised to 10

int in = 0;

sem_t full,empty;
pthread_mutex_t mutex;

void* produce(void* arg){
    while(true){
        sleep(1);
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        int item = rand() % 100;
        buffer[in++] = item;
        cout<<"Produced item: "<<item<<endl;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void* consume(void* arg){
    while(true){
        sleep(1);
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[--in];
        cout<<item<< " has been consumed" <<endl;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main(){
    pthread_t producer,consumer;
    sem_init(&empty,0,buffer.size());
    sem_init(&full,0,0);
    pthread_mutex_init(&mutex,NULL);
    pthread_create(&producer,NULL,produce,NULL);
    pthread_create(&consumer,NULL,consume,NULL);
    pthread_exit(NULL);
}

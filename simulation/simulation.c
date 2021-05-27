#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 999
#define NoServiceMan 1

typedef struct {
    int id;
    int arrival_time;
    int service_time;
} element;

typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

double random();
int is_customer_arrived();
void insert_customer(int arrival_time);
int remove_customer();
void print_stat();

void init(QueueType *q);
int is_empty(QueueType *q);
int is_full(QueueType *q);
void enqueue(QueueType *q, element item);
element dequeue(QueueType *q);

// 시뮬레이션에 필요한 여러가지 상태 변수
int duration=100; // 시뮬레이션 시간
double arrival_prob=0.1; // 하나의 시간 단위에 도착하는 평균 고객의 수
int max_serv_time=5; // 하나의 고객에 대한 최대 서비스 시간
int clock;


// 시뮬레이션의 결과
int customers = 0; // 전체고객수
int served_customers= 0; // 서비스받은 고객수
int waited_time = 0; // 고객들이 기다린 시간

QueueType queue;

int main(){
    init(&queue);
    int service_time[NoServiceMan] = {0,}; // 서비스의 alarm clock
    clock=0; // global clock
    while(clock < duration){
        clock++; // clock 시간 하나 경과
        printf("현재시각=%d\n",clock);

        if (is_customer_arrived()) { //new customer 처리
            insert_customer(clock);
        }
        for(int a=0; a< NoServiceMan; a++){ // every service man k
            if (service_time[a] > 0){ // 여기부터 service 처리
                service_time[a]--;}
            else {
            service_time[a] = remove_customer();
            }
        }
    }
print_stat();


}


// 랜덤 숫자를 생성하여 고객이 도착했는지 도착하지 않았는지를 판단
int is_customer_arrived(){
    if( random() < arrival_prob )
        return 1;
    else return 0;
}

// 새로 도착한 고객을 큐에 삽입
void insert_customer(int arrival_time){
    element customer;
    customer.id = customers++;
    customer.arrival_time = arrival_time;
    customer.service_time=(int)(max_serv_time*random()) + 1;
    enqueue(&queue, customer);
    printf("고객 %d이 %d분에 들어옵니다. 서비스시간은 %d분입니다.\n", customer.id, customer.arrival_time, customer.service_time);
}

// 0에서 1사이의 실수 난수 생성 함수
double random(){
    return rand()/(double)RAND_MAX;
}

// 큐에서 기다리는 고객을 꺼내어 고객의 서비스 시간을 반환한다.
int remove_customer(){
    element customer;
    int service_time=0;
    if (is_empty(&queue)) return 0;
    customer = dequeue(&queue);
    service_time = customer.service_time-1;
    served_customers++;
    waited_time += (clock - customer.arrival_time);
    printf("고객 %d이 %d분에 서비스를 시작합니다. 대기시간은 %d분이었습니다.", customer.id, clock, clock - customer.arrival_time);
    return service_time;
}

// 통계치를 출력한다.
void print_stat(){
    printf("서비스받은 고객수 = %d\n", served_customers);
    printf("전체 대기 시간 = %d분\n", waited_time);
    printf("1인당 평군 대기 시간 = %f분\n", (double)waited_time/served_customers);
    printf("아직 대기중인 고객수 = %d\n", customers-served_customers);
}

void init(QueueType *q){
    q->front = q->rear = 0;
}

int is_empty(QueueType *q){
    return (q->front == q->rear);
}

int is_full(QueueType *q){
    return((q->rear+1)%MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType *q, element item){
    if(is_full(q)){
        printf("queue is full");
        return;
    }
    q->rear = (q->rear+1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}

element dequeue(QueueType *q){
    if(is_empty(q)){
        printf("queue is empty");
        return q->queue[q->front];
    }
    q->front = (q->front+1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}
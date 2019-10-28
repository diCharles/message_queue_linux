/**
 USO DE PASO COLAS DE  MENSAJES O BUZONES
  PARA PROTEGER LA REGION CRITICA EN EJEMPLO DE TRENES
 
 SO: LINUX KERNEL , UBUNTU
	
	msgget : create a new msg queue or open an existing one
	msfsnd : add new msg to queue end, 
	msgrcv : feth mssgs from queue in FIFO order
	
	NOTE: Process must share a common key 
	in order to gain access to the queue in the first place
	
	system calls needed for inter proccess communication
	
	ftok : generate unique key
	
	
	
*/


// C Program for Message Queue (Reader Process) 
#include <stdio.h> 
#include <stdint.h>
#include <sys/ipc.h> 
#include <sys/msg.h>



typedef struct {
	long mesg_type ;
	char mesg_text[100];
}g_message_t ; 

int g_msgid;/** will contain msg queue id*/ 

g_message_t msg_queue ;

void producer( void ) ;
void consumer( void ) ;
void destroy_msg_queue( void ) ;


int main()
{
	key_t key ;
	
	/** obtain a key for mssg queue creation*/
	key= ftok("progfile", 65);
	
	/** create new message queue for both producer and consumer */
	
	g_msgid = msgget(key, 0666 | IPC_CREAT);
	msg_queue.mesg_type = 1; 
	
	producer();
	consumer();
	destroy_msg_queue();
	
	printf("END OF PROGRAM\n");
	
}


void producer( void )
{
	/** send msg in queue*/
	msg_queue.mesg_text[0] = 'B' ;
	
	msgsnd(g_msgid, &(msg_queue), sizeof(msg_queue), 0 ) ;
	
}

void consumer( void )
{
		msgrcv(g_msgid,  &(msg_queue), sizeof(msg_queue), 1 , 0 );
		
		/** display received msg*/
		printf("%c \n",msg_queue.mesg_text[0] );
	//	msgrcv(g_msgid,  &(msg_queue), sizeof(msg_queue), 1 , 0 );
}

void destroy_msg_queue( void )
{
	msgctl(g_msgid, IPC_RMID, NULL);

}

#include<stdio.h>
#include<sys/socket.h> 
#include<arpa/inet.h>	//inet_addr
#include <sqlite3.h>

int main(int argc , char *argv[])
{
	
	//Create database
	sqlite3* calculatorDB;
	char *insert;
	char* messageError;
	int status = 0;
	char *tableMake =	"CREATE TABLE IF NOT EXISTS calcData("
						"TIMESTAMP     TEXT    NOT NULL, "
						"DATA          TEXT    NOT NULL );";
	
	//Initialize database (will created calculator.db if not present)
	status = sqlite3_open("calculator.db", &calculatorDB);
	if (status)
	{
		printf("Error opening database.\n");
		return 1;
	}
	else
	{
		printf("Database Opened Successfully!\n");
	}
	status = sqlite3_exec(calculatorDB, tableMake, 0, 0, &messageError);
    if (status != SQLITE_OK ) 
    {
		fprintf(stderr, "SQL error: %s\n", messageError);
		
		sqlite3_free(messageError);        
		sqlite3_close(calculatorDB);
		
		return 1;
    } 
	
	//Create Socket
	int socket_desc;
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	
	if (socket_desc == -1)
	{
		printf("Could not create socket\n");
	}
	printf("socket created\n");
	
	struct sockaddr_in server;
	struct sockaddr_in client;
	
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons( 1234 );
	
	//Bind
	if (bind(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
			printf("bind failed\n");
			return 1;
	}
	printf("Bind Done\n");
	
	//Listen
	listen(socket_desc , 3);
	
	//Accept
	printf("Waiting for incoming connections...\n");
	int c = sizeof(struct sockaddr_in);
	int new_socket;
	while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
	{
		printf("connection accepted\n");
		char *client_ip = inet_ntoa(client.sin_addr);
		int client_port = ntohs(client.sin_port);
	
		printf("%s port %d\n", client_ip, client_port);
		int read_size;
		char client_message[2000];
		char output[49];
		char* buf_ptr = &output[0];
		while( (read_size = recv(new_socket , client_message , 2000 , 0)) > 0 )
		{

			printf("Data Buffer Print: bytes=%d", read_size);
			//convert the received byte array into a readable/saveable string
			for(int i = 0; i < read_size; i++) 
			{
				buf_ptr += sprintf(buf_ptr, "%02X", (unsigned char)client_message[i]);
			}
			printf("buf_ptr: %s\n",output);
			
			//save the received string into the db
			insert = sqlite3_mprintf("INSERT INTO calcData VALUES(datetime('now', 'localtime'),'%q');", output);
		    
			status = sqlite3_exec(calculatorDB, insert, NULL, 0, &messageError);
			if (status != SQLITE_OK) 
			{
				printf("Error Insert\n");
				sqlite3_free(messageError);
			}
			else
				printf("Records created Successfully!\n");
		}
	
		if(read_size == 0)
		{
			printf("Client disconnected\n");
			fflush(stdout);
		}
		else if(read_size == -1)
		{
			perror("recv failed");
		}
		
	}
	
	if(new_socket<0)
	{
		perror("accept failed");
	}
	
	sqlite3_free(insert);
	
	return 0;	
}

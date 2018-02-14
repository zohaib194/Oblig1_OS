#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


void process(int number, int time){
	printf("Prosess %d kjrører\n", number);
	sleep(time);
	printf("Prosess %d kjørte i %d sekunder\n", number, time);
}

int main(void){
	int p, p1, p2, p3;
	
	p=fork();
	if (p < 0) {
		printf("Error occured with process%d", p);
	
	} else if (p == 0) {
		// child code
		process(2,3);
		
		p2=fork();
		if(p < 0) {
			printf("Error occured with process%d", p);
	
		} else if(p2 == 0){
			process(3, 2);
			exit(0);		
		} else {
			waitpid(p2, NULL, 0);
		}
		exit(0);		// exit for process 2
	} else {
		
		// Parent code	
		process(0, 1);
		
		p1 = fork();
		if (p < 0) {
			printf("Error occured with process%d", p);
		} else if(p1 == 0){
			process(1, 2);
			exit(0);		// exit for process 1
		} else {
			process(4, 3);
			waitpid(p1, NULL, 0);
		
			p3 = fork(); 
			if (p < 0) { 
				printf("Error occured with process%d", p);
			} else if (p3 == 0) {
				process(5, 3);
				exit(0);		// exit for process 5
			} else {
				waitpid(p3, NULL, 0);
			}
		}
	waitpid(p, NULL, 0);		
	}
	
return 0;

}




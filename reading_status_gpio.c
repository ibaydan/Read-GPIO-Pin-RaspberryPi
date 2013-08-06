/*
 * * İsmail Baydan
 * * 2013
 * */


#include <wiringPi.h>
#include <stdio.h>
 
int main (void)
{
/*
 *	Pin list size and pin list
 */
int pinListSize=1;

int pinList[1]={7};

int pinPreviousState[20];
/*
 * To add pins change the pinList like this and 
 * change pinListSize according to pinList size
 *
 * Ex.1
 * int pinList[2]={1,7};
 * int pinListSize=2
 *
 * 
 * Ex.2
 * int pinList[3]={1,3,7};
 * int pinListSize=3
 *
 */

int i=0;
 
if (wiringPiSetup() == -1)
exit (1);
 
for(i=0;i<pinListSize;i++){
	pinMode(pinList[i], INPUT);
}

/*
 *	Clear files
 */
/*
 * system("rm /home/myfile1");
 * system("rm /home/myfile2");
 *
 */
 
/*
 *	Look for pins forever
 */
for (;;){
	for(i=0;i<pinListSize;i++){
		
		/*
 	        * Look for pin status
 	        */
		/*
		 *IF PRESSED
 		*/
		if(digitalRead(pinList[i])==1 && pinPreviousState[pinList[i]]!=1){
			pinPreviousState[pinList[i]]=1;
			char command[50];
			sprintf(command,"(date +%HH%M) >> /root/reading_status_gpio/pin%d_press.txt",pinList[i]);
			system(command);
		}
		/*
		 * IF NOT PRESSED 
		 */
		else{
		}

		/*
		 * IF RELASED
		 */
		if(digitalRead(pinList[i])==0){
			pinPreviousState[pinList[i]]=0;
			char command[50];
			sprintf(command,"(date +%HH%M) >> /root/reading_status_gpio/pin%d_release.txt",pinList[i]);
			system(command);
		}
		delay(50);
	}
}
 
return 0;
}

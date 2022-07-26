#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

struct Process {
  int pid; 
  int files[2];
  bool deadlock;
  int ET;
  int ES;
  
} process[20];




// find file name of file from arguements given from terminal
const int getFileName(char* argv[] , int size, FILE** readFile) /* pointer pointer to allow pointer to be changed */
 {
   bool checktemp=false;
   for(int i=1; i<=size ; i++){
	
	char *str=strstr( argv[i], "-f" );
	if(str!=NULL)
	{
		checktemp=true;	
		break;
	}
   }
 
 if( checktemp )
   for(int i=1; i<=size ; i++){
	
	char *str=strstr( argv[i], ".txt" );
	if(str!=NULL)
	{
		*readFile = fopen(argv[i],"r");
		printf("\nFile '%s' successfully opened \n",argv[i]);
		return i+1;
		break;
	}
   }

  return -1;
}


bool isDeadlockExist(int begin, int x , int size, int iter, int temp){
	
	if(iter!=0 && begin==x){
		
		return true;
	}
	else{
	for(int j=0;j<size;j++){
		
		if(x!=j & temp==0){
			if( process[x].files[1] == process[j].files[0]){
				temp=1;
			      bool find = isDeadlockExist(begin,j,size,iter+1,temp);
			      
			      if(find){
			      		process[j].deadlock=true;
			      		return true;
			      }	
			}
		 }
		 else{
			if(x!=j && j<x){
			
			      if( process[x].files[1] == process[j].files[0]){
			      temp=1;
			      bool find = isDeadlockExist(begin,j,size,iter+1,temp);
			          if(find){
			      		process[j].deadlock=true;
			      		return true;
			          }	
			      }
			} 
		 } //else closed
		 
	       } // for loop closed
	     
	     } //1st else closed
		
	
	return false;
} //function closing bracket

void searchTerminateProcess(int deadlockId[]){
	int siz=0;
	siz=sizeof(&deadlockId)/sizeof(deadlockId[0]);
	int min=-1;
	min=deadlockId[0];
	
	// find process with minimum id
	
	for(int l=1; l<siz;l++){
		if(deadlockId[l] < min && deadlockId[l]!=0)
			min=deadlockId[l];
		
	}
	printf(" %d",min);   // terminate the process whose id is minimum
	
}





// execution starts from here

int main(int argc,char* argv[]){
	int size=20;

FILE *fptr;  // file type variable

if(argv[2]==NULL)
	argv[2]="a";
if(argv[3]==NULL)
	argv[3]="a";
if(argv[4]==NULL)
	argv[4]="a";

int filenameindex=0;
    
filenameindex = getFileName(argv , strlen(*argv) , &fptr );


	if (fptr == NULL){
            	printf("Error: could not open file\n");
            	return 0;
            	}
        
	
    	int n=-1,i=0;
    	int temp=0;
    	char ch[5];
    	int processes=0;
    	int files=0;
    	
    	//------------file reading--------
    	
    	while(!feof(fptr)){
    	
    		if(i==0){
                    fscanf (fptr, "%d", &n);   // read data only once at start
		}
		process[i].pid=n;
		fscanf (fptr, "%d", &n);
		process[i].files[0]=n;
		fscanf (fptr, "%d", &n);
		process[i].files[1]=n;
		fscanf (fptr, "%d", &n);		
		process[i].deadlock=false;
		i++;
	}
	
	
	printf("\n -----------Task 1-----------\n");
	
	printf("\n ==> Processes: %d\n",i);
    	fclose(fptr);
	for(int j=0;j<i;j++){
		process[j].ES=-1;
		process[j].ET=-1;
	}	
    	
    	
    	int holderSize=i*2;   //processes will always double than the number of projects
    	i--;   	
	int holder[holderSize];
	
	bool deadlock=false;
	
	for(int j=0;j<=i;j++){
		
		processes++;
		holder[temp]=process[j].files[0];
		holder[temp+1]=process[j].files[1];
		temp=temp+2;
	}
	i++;
	
	int length = sizeof(holder)/sizeof(holder[0]);    // size of array
        int dup=0;
        //Searches for duplicate element    
    	
    	for(int i = 0; i < length; i++) {    
        	for(int j = i + 1; j < length; j++) {    
        	    if(holder[i] == holder[j]){    
                	dup++;
                	break;
                    }
                }    
    	}    

	files=(i*2)-dup;    //total files minus duplicate files
	
	printf(" ==> Files: %d\n", (files));
    	
    	
    	int storage[i];
    	int execTime[i];
    	
    	int add1=0,add2=0;
    	
    	// -------------Task 2 begins here--------------
	// only if '-e' arguement is passed from terminal     	
    	
    if( !strcmp(argv[1], "-e") || !strcmp(argv[2], "-e") || !strcmp(argv[3], "-e") || !strcmp(argv[4], "-e") ){	
    	
    	printf("\n -----------Task 2-----------\n");
    	
    	for(int n=0;n<i;n++ ){
    		
    		add1=0;add2=0;
    		for(int k=0;k<i;k++){
    			if(process[n].files[1]==process[k].files[0]){
    				add1++;
    				
    			}
    		}
    		
    		for(int d=0;d<n;d++){
    			if( process[n].files[1]==process[d].files[1])
    					add2+=1;
    			}
    			
    		
    		if(add1==0 && add2==0)
    			execTime[n]=2;
    		else
    			execTime[n]=add1+add2+2;
    			
    	}
    	
    	int exectime=execTime[0];
    	for(int h=0;h<i;h++){
    		if( exectime < execTime[h])
    			exectime=execTime[h]; 
    	}
    
    	printf("\n ==> Execution time: %d\n", exectime);
    	
    }  //task2  if statement closing bracket
	
	
	
	//----------------------------------Task 3,4 begin here----------------------------
	
	// Identify the deadlock
	
	
	printf("\n ---------Task 3 & 4---------\n");
	
	int deadlockId[i];
	int counter=0;
	int check=0,f=0;
	int h=0;
	while(h<i){
	
	     if(process[h].deadlock!=true){
		
		bool isExist=isDeadlockExist(h,h,i,0,0);
			
		     if(isExist){
			 if(check==0){
			    printf("\n ==> Deadlock detected\n     Terminate : ");
			  }
				
			 check=1;
			 for(f=h;f<i;f++){
			    if(process[f].deadlock==1){
				deadlockId[counter]=process[f].pid;
				counter++;	
			    }
			 }
			 
			 searchTerminateProcess(deadlockId); // identify the processes which should terminate
			 h=counter-1;
			 counter=0;
		     }	
	     }
	      h++;	
	}
	
	
	//---------Task 3 and 4 ended-----------------
	
	
	
	//----------Task 5 begins here-----------
	//will execute only if '-c' arguement is passed from terminal
	
	
	if( !strcmp(argv[1], "-c") || !strcmp(argv[2], "-c") || !strcmp(argv[3], "-c") || !strcmp(argv[4], "-c") ){
	   
	   printf("\n\n -----------Task 5-----------\n");
	   
	   int CT=0;  // current time	
	   int TE=0;  // total number of executions
	   
	   printf("\n Time\tPid\tFile1\tFile2\n");
	   
	   int temp1=i,d=0;
	   
	   while(TE<temp1){
	  
	     for(d=0;d<i;d++){
		
		int check1=0,check2=0;
		
		if(process[d].ES==-1){
		    for(int s=0;s<d;s++){
			
			if(process[d].files[1]==process[s].files[0]){
				
				if(process[s].ET==CT){
					check1=1;
				}
			
			}
			if(process[d].files[0]==process[s].files[1]){
			
				if(process[s].ET==CT)
				{
					check2=1;
				}	
			
			}

		 }
		if( check1==0 && check2==0 ){ // execute
			process[d].ET=CT;
			process[d].ES=1;
			TE++;
			printf(" %d\t%d\t%d\t%d\t\n",CT,process[d].pid,process[d].files[0],process[d].files[1]);
			
		}
		}
	
	  }
		
	CT+=1;
	
	}
    	
    	printf("\n ==> Simulation Time: %d\n",CT);
	
	
	} //task 5 if statement closing bracket 
	
	
	//-------------Task 5 ended---------------
	
	
	
	} //main ended	
	
	
	
	
	

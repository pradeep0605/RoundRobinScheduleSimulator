
#include<iostream>
#include<stdlib.h>
#include "PKRThread.cpp"
#include <stdio.h>

using namespace std;

class process: public PKRThread
{   
    public:
    unsigned int processID;
    bool IO;
    short burst; // for every second.
    process *next;
    process()
    {
 	    processID=burst=0;
            IO=false;    
            next=NULL;
    }
    
    process(unsigned int pid, unsigned int burst)
    {
         processID=pid;
         this->burst=burst;
    }
    
    void run()
    {
            IO=true;
            int sleepTime=0;
            while( (sleepTime=rand()%11000) < 5500 );
            sleep(sleepTime);
            IO=false;
    }
};


class processor:public PKRThread
{     
      public:
      short maxProcesses;
      short processCount;
      process *currentProcess;
      process *last,*first;
      short quantam;
      
      processor()
      {
          maxProcesses=quantam=processCount=0;
          currentProcess=first=last=NULL;
      }
      
      processor(short maxProcess, short quantam)
      {
          this->maxProcesses=maxProcess;
          this->quantam=quantam;
          currentProcess=first=last=NULL;
      }
      
      int addProcess(process p)
      {
           if(processCount>=maxProcesses)
              return -1;
              
           process *n=new process(p);
           
           processCount++;
           
           if(last==NULL)
           {
               last=n;
               n->next=n;
               currentProcess=n;
               first=n;
               return 0;
           }
           
           n->next=last->next;
           last->next=n;
           last=n;
           
           //n->start();
      }
      
      void Delete()
      {
              process *temp=currentProcess;
           while(temp->next!=currentProcess)
           {
		temp=temp->next;                
           }   
           temp->next=currentProcess->next;
           if(last==currentProcess)
           {
              last=currentProcess->next;
           }
           if(first==currentProcess)
           {
              first=currentProcess->next;              
           }
           
           processCount--;
      } 
      
      
      
      void display()
      {     
            cout<<"Number of processes in the system :"<<processCount<<endl;
            cout<<"Quantam time :"<<quantam<<endl;
            
            
	    bool current=true;
            process *temp=first; 
            
            while((temp!=first || current==true) && temp->IO==false)
            {
                 current=false;
                 printf("=============");                 
                 temp=temp->next;
            } 
            cout<<endl;
 
            current=true;
            temp=first; 
            while((temp!=first || current==true) && temp->IO==false)
            {
                 current=false;
                 printf("| pid:%5d |",temp->processID);                 
                 temp=temp->next;
            } 
            cout<<endl;
            
            temp=first;
            current=true;
            while((temp!=first || current==true) && temp->IO==false)
            {
                 current=false;
                 if(temp->IO==true)
                    printf("| IO        |");
                 else
                    printf("| CPU       |");
                 temp=temp->next;
            } 
            cout<<endl;
            
            temp=first;
            current=true;
            while((temp!=first || current==true)  && temp->IO==false)
            {
                    current =false;
                    printf("| brst:%4d |",temp->burst);
                 temp=temp->next;
            }
            //under line
            current=true;
            temp=first; 
            cout<<endl;
            while((temp!=first || current==true)  && temp->IO==false)
            {
                 current=false;
                 cout<<"=============";
                 temp=temp->next;
            }
            cout<<endl;
            
             
            
            temp=first;
            cout<<"\n\n";
            while(temp!=currentProcess  && temp->IO==false)
            {
                 cout<<"             ";
                 temp=temp->next;
            } 
            cout<<"     /\\\n";



            temp=first;
            while(temp!=currentProcess  && temp->IO==false)
            {
                 cout<<"             ";
                 temp=temp->next;
            } 
            cout<<"    //\\\\\n";

            temp=first;
            while(temp!=currentProcess  && temp->IO==false)
            {
                 cout<<"             ";
                 temp=temp->next;
            } 
            cout<<"     ||\n";            

            temp=first;
            while(temp!=currentProcess  && temp->IO==false)
            {
                 cout<<"             ";
                 temp=temp->next;
            } 

            cout<<"     ||\n";               
            
            /*to display cpu*/            
            temp=first;
            while(temp!=currentProcess && temp->IO==false)
            {
                 cout<<"             ";
                 temp=temp->next;
            } 
            cout<<"  processor\n";            


            cout<<endl<<endl<<endl;
      }
};     



int main()
{   
   short n=0,quant=0,pid=0,maxBurstTime=0;
   cout<<"Enter the processes limit:";
   cin>>n;
   if(n<=0)
   {
       cout<<"Number of processes cannot be -Negative or zero!!!";
       return 1;
   }
   cout<<"Enter the quantam :";
   cin>>quant;
   if(quant<=0)
   {
       cout<<"Quantam cannot be -Negative (as we cannot go in past)\n";
       return 1;
   }
   
   cout<<"Enter the maximum burst time for processes:";
   cin>>maxBurstTime;
   if(maxBurstTime<=0)
   {

       cout<<"Burst time cannot be zero or -Negative\n";
       return 1;
   }   
     
   processor pr=processor(n,quant);
   
     while(1)
     {
         int quantCount=0;
         int brstTime=0;
         do
         {
 	     brstTime=(unsigned int)(rand()+rand())%(maxBurstTime+1);               
         }while( brstTime==0);
         
         process *ps=new process(pid++, brstTime);
         if( pr.addProcess(*ps)==-1)
             pid--;


        if(pr.currentProcess->IO==false)
        {
        
            if(rand()%3==0)
            {
               int sleepTime=0;
                 
              do
              {  
                sleepTime=rand()%quant;
              }
              while(  (sleepTime >= pr.currentProcess->burst));
              
               cout<<"Sleep time "<<sleepTime<<endl;
              
               if(pr.currentProcess->burst>=quant)
               {
		     sleep(sleepTime);
                     pr.currentProcess->start();               
               }
               pr.currentProcess->burst=pr.currentProcess->burst - sleepTime;           
          }
          else
          {      
          
		  if(pr.currentProcess->burst>=quant)
		     sleep(quant);
		  else
		     sleep(pr.currentProcess->burst);

				
		   if(pr.currentProcess->burst>=quant)
		   {
		        pr.currentProcess->burst=pr.currentProcess->burst - quant;            
		        if(pr.currentProcess->burst==0)
		        pr.Delete();		          
		   }     
		   else
		   {
		      pr.currentProcess->burst=0;
		      pr.Delete();
		   }       
		     pr.currentProcess=pr.currentProcess->next;
           }  
        } 
        else
        {
           pr.currentProcess=pr.currentProcess->next;
        }
          system("clear");	      
          pr.display();
     }
   return 0;
}






















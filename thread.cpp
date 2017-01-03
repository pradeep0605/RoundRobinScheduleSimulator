#include<iostream>
#include "PKRThread.cpp"

using namespace std;
class mythread : public PKRThread
{
    int Id;
    public:

    mythread(int id)
    {
       Id=id;
    }
    
    void run()
    {
         cout<<"IN the thread";
         sleep(10000);
    }
};

int main() 
{
     mythread td=mythread(1);
     for(int i=0;i<100;i++)
     {
          
               td.start();         
     }   
     td.join();
     
    return 0;
}


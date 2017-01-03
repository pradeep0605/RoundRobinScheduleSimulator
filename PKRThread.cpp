#include <iostream>
#include <pthread.h>

using namespace std;

void * callRun(void *);
class PKRThread
{
    pthread_t thrd;
    pthread_attr_t attr;

    protected:
    void sleep(unsigned int i)
	{
	   usleep(1000*i);
        }
        
        void msleep(unsigned int i)
        {
           usleep(i);
        }
    
    public:
        PKRThread()
        {
           pthread_attr_init(&attr);
        }  
        
        void start()
        {
            pthread_create(&thrd,&attr,callRun,(void*)(this));
	}
	
	void join()
	{
	   pthread_join(thrd,NULL);
	}
	
	virtual void run()
	{}
};
    
void * callRun(void *arg)
{   
    PKRThread *t=(PKRThread *) arg;
    t->run();
}   

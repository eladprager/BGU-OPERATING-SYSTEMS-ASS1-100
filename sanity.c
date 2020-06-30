#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "perf.h"

int main()
{
    int status=0;
    printf(1,"PID\tPS_PRIORITY\tSTIME\tRETIME\tRTIME\n");
    for (int j = 1; j <= 3; j++)
    {
        
        if (fork()==0) {  
            struct perf performance;      
            switch (j)
            {
            case 1:
                set_ps_priority(10);
                set_cfs_priority(3);
                break;
            case 2:
                set_ps_priority(5);
                set_cfs_priority(2);
                break;
            case 3:
                set_ps_priority(1);
                set_cfs_priority(1);
                break;
            default:
                break;
            }
            // printf(1,"Child\n");
            int i = 10000000;
            long long dummy = 0; 
            while(i--)
                dummy+=atoi("1000000")+i;
            proc_info(&performance);
            printf(1,"%d\t%d\t\t%d\t%d\t%d\n",getpid(),performance.ps_priority,performance.stime,performance.retime,performance.rtime);
            exit(status);
        }
    }

    for (int i = 0; i < 3; i++){
        wait(&status);
    }
    exit(0);
    return 0;
}
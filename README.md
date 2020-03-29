#Multilevel Queue Scheduling Algorithm

Multilevel queue scheduling algorithms is an algorithm that is efficient when handling processes of various categories. Usually processes are of three types, System processes are the highest priority processes that can be executed in a computer. System processes are the important processes as they look after the various aspects of the system and thus, they are considered of higher priority. Then comes interactive processes like the programs we run for our use in our computers like word processing programs or games that we play on our computer. They are called interactive processes since we are directly interacting with those processes with our inputs and getting desirable output, but they are of mid priority since for urgent system level processes the interactive processes can wait and thus their priority comes after the system processes. After that comes the Batch processes or the background processes, usually they are the background services for the applications that we have installed in our computer. For instance, if we have an antivirus installed in our computer it always searched for the latest virus definitions from its server and thus this task is done by the background process associated with that antivirus program. This is the reason these processes are of lower priority than the rest of the processes because they don’t play a role that is too much necessary for the operating system to run and manage resources properly.
 
In this scheduling methodology of multilevel queue scheduling algorithm on different queues different scheduling algorithms are used. For the highest priority queue round robin algorithm is considered, for the middle priority queue priority scheduling algorithm is used for the scheduling process and finally for the lowest priority queue first come first serve algorithm is used for scheduling. This scheduling methodology is very efficient when it comes to the scheduling of processes of different types and of different priorities. This ensures proper resource management of the system and optimal running of the system.

Algorithm:
1.	Take user input about various processes that is to be executed 
2.	Take input for each parameter like arrival time, burst time and priority.
3.	Separate the processes and categorize them into 3 types based on their priority.
4.	Queue 1 for batch processes. Priority 1 to 3.
5.	Queue 2 for interactive processes Priority 4 to 6.
6.	Queue 3 for system processes. Priority 7 to 9.
7.	Perform first come first serve algorithm on queue 1.
8.	Perform priority scheduling on queue 2.
9.	Perform round robin on queue 3.
10.	Calculate waiting time and turnaround time simultaneously.

Complexity of the code:
1.	Taking user input is of complexity O(n).
2.	Waiting time calculation O(n).
3.	Turnaround time calculation O(n).
4.	FCFS algorithm O(n2).
5.	Priority Scheduling algorithm O(n2).
6.	Round robin algorithm O(n).
7.	Showing output O(n).

Overall time complexity is O(n2).

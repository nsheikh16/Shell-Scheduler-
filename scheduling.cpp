#include <string>
#include <fstream>
#include <iostream>
#include <queue>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "scheduling.h"

using namespace std;

pqueue_arrival read_workload(string filename)
{
  pqueue_arrival workload;
  ifstream fileStream;
  fileStream.open(filename.c_str());
  int a,d;
  
  while(fileStream >> a >> d) {
   
    Process pro;
    pro.first_run = -1;
    pro.completion = -1;
    pro.arrival = a;
    pro.duration = d;
    workload.push(pro);

  }

  return workload;
}

void show_workload(pqueue_arrival workload)
{
  pqueue_arrival xs = workload;
  cout << "Workload:" << endl;
  while (!xs.empty())
  {
    Process p = xs.top();
    cout << '\t' << p.arrival << ' ' << p.duration << endl;
    xs.pop();
  }
}

void show_processes(list<Process> processes)
{
  list<Process> xs = processes;
  cout << "Processes:" << endl;
  while (!xs.empty())
  {
    Process p = xs.front();
    cout << "\tarrival=" << p.arrival << ", duration=" << p.duration
         << ", first_run=" << p.first_run << ", completion=" << p.completion << endl;
    xs.pop_front();
  }
}

list<Process> fifo(pqueue_arrival workload)
{
  list<Process> complete;
  //for each Process p in workload
  //upadte p.first_run, p.coompleteation
  //add p to the list
  // YOUR CODE HERE
  int t =0;
  while (!workload.empty()){
    Process p = workload.top();
    workload.pop();
    p.first_run = t;
    t += p.duration;
    p.completion = t;
    complete.push_back(p);
  }
  return complete;
}

list<Process> sjf(pqueue_arrival workload)
{
  list<Process> complete;
  int t=0;
  pqueue_duration d; 
  while (!workload.empty()){

    while (!workload.empty() && workload.top().arrival <= t){
      d.push(workload.top());
      workload.pop();
    }
      while(!d.empty()){
          Process p = d.top();
          d.pop();
          p.first_run = t;
          t += p.duration;
          p.completion = t;
          complete.push_back(p);
    }

  }
  return complete;
}

list<Process> stcf(pqueue_arrival workload)
{
  list<Process> complete;
  // int t=0;
  // int completion1 = c1;
  // int completion2 = c2;
  // pqueue_duration d;
  // while (!workload.empty()){

  //   while (!workload.empty() && workload.top().arrival <= t && completion1 <= completion2 ){
  //     d.push(workload.top());
  //     workload.pop();
  //   }
  return complete;
}

list<Process> rr(pqueue_arrival workload)
{
  list<Process> complete;
  vector<Process> anotha;
  // YOUR CODE HERE
  
  pqueue_arrival temp = workload;
  pqueue_duration d; 
  bool fin;
  int t=0;
  int quantum,size;
  size=workload.size();
  int time1;
  int array1[size];
  Process n;


  while(!temp.empty()){
     n = temp.top();
    temp.pop();
    array1[time1] = n.duration;
    n.first_run= -1;
    anotha.push_back(n);
    time1++;
  }
  quantum =1;
  while(true){
    fin =true;;
    for (int i=0; i<size;i++){
      if (array1[i]> 0){
        n = anotha.at(i);
        if (n.first_run == -1){
          n.first_run == i;
          fin = false;
        if(array1[i]>quantum){
          t+=quantum;
          n.completion =t;
          complete.push_back(n);
          array1[i]=0;
        }
        }
      }
      if (fin) {
        break;
    }
  }


}
return complete;
}

float avg_turnaround(list<Process> processes)
{ // comp - arrival then find average
  float sum =0;
  list<Process> :: iterator piter;

  for(piter = processes.begin();piter != processes.end();piter++){
    //Process p = piter;
    sum+= piter->completion - piter->arrival;
  }
  return sum / processes.size();
}

float avg_response(list<Process> processes)
{
  float sum =0;
  list<Process> :: iterator piter;

  for(piter = processes.begin();piter != processes.end();piter++){
    //Process p =piter;
    sum+= piter->first_run - piter->arrival;
  }
  return sum / processes.size();
}



void show_metrics(list<Process> processes)
{
  float avg_t = avg_turnaround(processes);
  float avg_r = avg_response(processes);
  show_processes(processes);
  cout << '\n';
  cout << "Average Turnaround Time: " << avg_turnaround(processes) << endl;
  cout << "Average Response Time:   " << avg_response(processes) << endl;
}

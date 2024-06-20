#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Process
{
public:
    int pid, at, bt, remaining_bt, ct, tat, wt;

    void update_after_ct()
    {
        tat = ct - at;
        wt = tat - bt;
    }

    void display()
    {
        cout << pid << "\t" << at << "\t" << bt << "\t" << ct << "\t" << tat << "\t" << wt << endl;
    }
};

float average(vector<Process> P, string varName)
{
    float total = 0;
    for (int i = 0; i < P.size(); i++)
    {
        if (varName == "wt")
            total += P[i].wt;
        else if (varName == "tat")
            total += P[i].tat;
    }
    return total / P.size();
}

void runRoundRobinScheduler(vector<Process> P, int time_quantum)
{
    vector<Process> temp = P;
    queue<int> q;
    int time = 0, i = 0;

    cout << "pid\tat\tbt\tct\ttat\twt" << endl;

    for (int i = 0; i < P.size(); i++)
    {
        q.push(i);
    }

    while (!q.empty())
    {
        int pid = q.front();
        q.pop();

        if (temp[pid].remaining_bt > time_quantum)
        {
            time += time_quantum;
            temp[pid].remaining_bt -= time_quantum;
            q.push(pid);
        }
        else
        {
            time += temp[pid].remaining_bt;
            temp[pid].ct = time;
            temp[pid].update_after_ct();
            temp[pid].display();
            temp[pid].remaining_bt = 0;
        }
    }

    cout << "Average waiting time: " << average(temp, "wt") << endl;
    cout << "Average turnaround time: " << average(temp, "tat") << endl;
}

void runPSRJFScheduler(vector<Process> P)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<Process> temp = P;
    int time = 0, i = 0;

    cout << "pid\tat\tbt\tct\ttat\twt" << endl;

    while (i < P.size() || !pq.empty())
    {
        while (i < P.size() && P[i].at <= time)
        {
            pq.push({P[i].bt, P[i].pid});
            P[i].remaining_bt = P[i].bt;
            i++;
        }

        if (pq.empty())
        {
            time = P[i].at;
            continue;
        }

        int pid = pq.top().second;
        int bt = pq.top().first;
        pq.pop();

        if (bt > 1)
        {
            temp[pid - 1].remaining_bt = bt - 1;
            pq.push({temp[pid - 1].remaining_bt, pid});
        }
        else
        {
            temp[pid - 1].ct = time + 1;
            temp[pid - 1].update_after_ct();
            temp[pid - 1].display();
        }

        time++;
    }

    cout << "Average waiting time: " << average(temp, "wt") << endl;
    cout << "Average turnaround time: " << average(temp, "tat") << endl;
}

void runFCFSScheduler(vector<Process> P)
{
    sort(P.begin(), P.end(), [](Process a, Process b)
         { return a.at < b.at; });

    cout << "pid\tat\tbt\tct\ttat\twt" << endl;
    P[0].ct = P[0].at + P[0].bt;
    P[0].update_after_ct();
    P[0].display();

    for (int i = 1; i < P.size(); i++)
    {
        if (P[i].at < P[i - 1].ct)
        {
            P[i].ct = P[i - 1].ct + P[i].bt;
        }
        else
        {
            P[i].ct = P[i].at + P[i].bt;
        }
        P[i].update_after_ct();
        P[i].display();
    }

    cout << "Average waiting time: " << average(P, "wt") << endl;
    cout << "Average turnaround time: " << average(P, "tat") << endl;
}

void runSRJFScheduler(vector<Process> P)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<Process> temp = P;
    int time = 0, i = 0;
    bool flag = false;

    cout << "pid\tat\tbt\tct\ttat\twt" << endl;

    while (i < P.size() || !pq.empty())
    {
        while (i < P.size() && P[i].at <= time)
        {
            pq.push({P[i].bt, P[i].pid});
            i++;
        }

        if (pq.empty())
        {
            time = P[i].at;
            continue;
        }

        int pid = pq.top().second;
        int bt = pq.top().first;
        pq.pop();

        if (flag)
        {
            temp[pid - 1].ct = time + bt;
            temp[pid - 1].update_after_ct();
            temp[pid - 1].display();
        }
        else
        {
            temp[pid - 1].ct = time + bt;
            temp[pid - 1].update_after_ct();
            temp[pid - 1].display();
            flag = true;
        }

        time += bt;
    }

    cout << "Average waiting time: " << average(temp, "wt") << endl;
    cout << "Average turnaround time: " << average(temp, "tat") << endl;
}

int main()
{
    vector<Process> P;
    int n, time_quantum;

    cout << "Enter the number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        Process p;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> p.at >> p.bt;
        p.pid = i + 1;
        p.remaining_bt = p.bt;
        P.push_back(p);
    }

    cout << "Enter the process: \n1: First Come First Serve (FCFS) \n2: Shortest Job First (Preemptive)\n3: Shortest Job First (Non Preemtptive)\n4: Round Robin" << endl;
    int xd;
    cin >> xd;
    if (xd == 1)
    {
        runFCFSScheduler(P);
    }
    else if (xd == 2)
    {
        runPSRJFScheduler(P);
    }
    else if (xd == 3)
    {
        runSRJFScheduler(P);
    }
    else if (xd == 4)
    {
        cout << "Enter the time quantum: ";
        cin >> time_quantum;
        runRoundRobinScheduler(P, time_quantum);
    }
    return 0;
}
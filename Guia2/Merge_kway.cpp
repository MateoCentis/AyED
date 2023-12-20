#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*Dado un vector de colas ordqs, obtener la cola merged resultante de la fusión de todas
las colas en una sola, de fomra de que los elementos siguen ordenados*/

void show_queue(queue<int> &q)
{
    while (!q.empty())
    {
        cout << " " << q.front();
        q.pop();
    }
}
void merge_kway(vector<queue<int>> &qords, queue<int> &merged)
{
    for (int i = 0; i < qords.size(); ++i)
    {
        while (!qords[i].empty())
        {
            merged.push(qords[i].front());
            qords[i].pop();
        }
    }
    vector<int> aux;
    while (!merged.empty())
    {
        aux.push_back(merged.front());
        merged.pop();
    }
    int aux;
    for (int i = 0; i < aux.size(); ++i)
    {
    }
}
int main()
{
    queue<int> merged;
    queue<int> q;
    q.push(1);
    q.push(3);
    q.push(5);
    q.push(6);
    vector<queue<int>> qords;
    qords.push_back(q); //(0, 3, 5, 8), (6, 9, 10)};
    queue<int> q2;
    q2.push(0);
    q2.push(3);
    q2.push(5);
    q2.push(8);
    qords.push_back(q2);
    merge_kway(qords, merged);
    show_queue(merged);
}
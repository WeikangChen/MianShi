#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

/*
Design and implement a method that can calculate the following as if it were in a library for other teams at Amazon to use.

== Given ==
Shipments, where a Shipment has the following attributes

Shipment
- shipment_id // a number
- warehouse_id // a string
- priority // a number; a LOWER priority is a BETTER priority
- hold_date // a date
- weight // a number
- // etc.

== Want ==
For each warehouse,
    find the top 5 "best" shipments based on priority.

*/

struct Shipment {
    int shipment_id;
    string warehouse_id;
    int priority;
    int hold_date;
    int weight;
    
    Shipment(int s_id = 0, string w_id = "", int p = 0):
        shipment_id(s_id),
        warehouse_id(w_id),
        priority(p),
        hold_date(0),
        weight(0) {}
    
    friend bool operator<(const Shipment &rhs, const Shipment &lhs) {
        if(rhs.priority == lhs.priority)
            return rhs.hold_date < lhs.hold_date;
        return rhs.priority < lhs.priority;
    }

    friend bool operator>(const Shipment &rhs, const Shipment &lhs) {
        if(rhs.priority == lhs.priority)
            return rhs.hold_date > lhs.hold_date;
        return rhs.priority > lhs.priority;
    }

    void print() const {
        cout << "  Shipment: " << warehouse_id << ", " << shipment_id << ", " << priority << endl;
    }
};

//typedef unordered_map<string, priority_queue<Shipment, vector<Shipment>, decltype(&compare)> > HASH_HEAP;
typedef priority_queue<Shipment, vector<Shipment>, less<Shipment> > PQ;
typedef unordered_map<string, PQ> HASH_HEAP;


HASH_HEAP Find5Best(const vector<Shipment> &ships)
{
    HASH_HEAP hh;
    for(auto sh: ships)
    {
        HASH_HEAP::iterator it = hh.find(sh.warehouse_id); 
        if (it == hh.end()) {
            PQ que;
            que.push(sh);
            hh[sh.warehouse_id] = que;
        } else {
            PQ &que = it->second;
            if (que.size() < 5) {
                que.push(sh);
            }
            else if(sh < que.top()) {
                que.pop();
                que.push(sh);
            }
        }
    }
    return hh;
}

int main(int argc, char ** argv)
{
    srand(time(NULL));
    vector<Shipment> ships;
    for(int i = 0; i < 20; ++i) {
        int priA = rand() % 10;
        int priB = rand() % 10;
        ships.push_back(Shipment(10+i, "A", priA));
        ships.push_back(Shipment(20+i, "B", priB));
    }

    HASH_HEAP res = Find5Best(ships);

    for (auto it = res.begin(); it != res.end(); ++it) {
        PQ &que = it->second;
        cout << "On Warehouse " << it->first << ", the 5 best are "<< endl;
        for (int i = 0; i < 5; i++) {
            que.top().print();
            que.pop();
        }
    }
    return 0;
}

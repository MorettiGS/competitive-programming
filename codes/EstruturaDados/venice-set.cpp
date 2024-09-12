#include <bits/stdc++.h>
using namespace std;

struct VeniceSet {
    multiset<int> St;
    int water_level = 0;

    void add(int x) { St.insert(x + water_level); }

    void remove(int x)
    {
        auto it = St.find(x + water_level);
        if (it != St.end()) {
            St.erase(it);
        }
        else {
            cout << "Element " << x
                 << " not found for removal." << endl;
        }
    }

    void updateAll(int x) { water_level += x; }

    int size() { return St.size(); }
};

int main()
{
    VeniceSet vs;

    // Add elements to the VeniceSet
    vs.add(10);
    vs.add(20);
    vs.add(30);

    // Print size of the set
    cout << "Size of the set: " << vs.size() << endl;

    // Decrease all by 5
    vs.updateAll(5);

    // Remove an element
    // This removes 5 (present height) + 5 (water level) = 10
    vs.remove(5);

    // Attempt to remove an element that does not exist
    vs.remove(40);

    // Print size of the set
    cout << "Size of the set: " << vs.size() << endl;

    return 0;
}

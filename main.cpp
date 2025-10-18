#include <bits/stdc++.h>
#include <queue>

using namespace std;

vector<vector<int>> inputGraph(int& num_rooms) {
    
    cout << "--- Emergency Path Finder Setup ---" << endl;
    while (true) {
        cout << "Enter the total number of rooms (nodes) in the building: ";
        if (cin >> num_rooms && num_rooms > 1) {
            break;
        }
        cout << "Invalid input. Please enter a number greater than 1." << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }
    
   
    vector<vector<int>> AM(num_rooms, vector<int>(num_rooms, 0));
    
    cout << "\n--- Defining Connections ---" << endl;
    cout << "Enter room connections (edges). Rooms are numbered 0 to " << num_rooms - 1 << "." << endl;
    cout << "Enter 'room_A room_B' to connect them (e.g., '0 1')." << endl;
    cout << "Enter '-1 -1' to finish adding connections." << endl;

    int u, v;
    while (true) {
        cout << "Connection (Room A Room B, or -1 -1 to finish): ";
        
        if (!(cin >> u >> v)) {
            cout << "Invalid input format. Please enter two numbers." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (u == -1 && v == -1) {
            break;
        }
        
        if (u < 0 || u >= num_rooms || v < 0 || v >= num_rooms) {
            cout << "Error: Room numbers must be between 0 and " << num_rooms - 1 << ". Try again." << endl;
        } else if (u == v) {
            cout << "Skipping connection: A room cannot be connected to itself." << endl;
        } else {
            if (AM[u][v] == 1) {
                cout << "Connection already exists between " << u << " and " << v << ". Skipping." << endl;
            } else {
                AM[u][v] = 1; 
                AM[v][u] = 1; 
                cout << "Connection established between Room " << u << " and Room " << v << "." << endl;
            }
        }
    }
    
    return AM;
}

vector<int> Path_Reconstruction(vector<int> &arr, int start, int exit)
{
    vector<int> reconstructed_path;

    int current = exit;
    reconstructed_path.push_back(current);
    while (arr[current] != -2)
    {
        reconstructed_path.push_back(arr[current]);
        current = arr[current];
    }
    reverse(reconstructed_path.begin(), reconstructed_path.end());
    return reconstructed_path;
}


void Shortest_Path(vector<vector<int>> &AM, int start, int exit)
{

    vector<int> parent_Arr(AM.size(), -1);
    parent_Arr[start] = -2;
    queue<int> visited;

    visited.push(start);
    while (!visited.empty())
    {
        int current = visited.front();
        visited.pop();
        if (current == exit)
        {
            cout << "exit path found" << endl;
            break;
        }
        for (int v = 0; v < AM.size(); v++)
        {
            if (AM[current][v] == 1 && parent_Arr[v] == -1)
            {
                parent_Arr[v] = current; 
                visited.push(v);
            }
        }
    }
    if (parent_Arr[exit] == -1)
    {
        cout << "no viable path found" << endl;
        return;
    }

    vector<int> sp = Path_Reconstruction(parent_Arr, start, exit);
    for (int i = 0; i < sp.size()-1;i++){
        cout << sp[i] << "->";
    }
    cout << sp[sp.size() - 1];
    cout << endl;
}


int main()
{
    int num_Rooms;
    vector<vector<int>> LayoutBuilding = inputGraph(num_Rooms);

    int startRoom;
    cout << "enter starting room" << endl;
    cin >> startRoom;
    int exit;
    cout << "enter emergency exit room" << endl;
    cin >> exit;

    Shortest_Path(LayoutBuilding, startRoom, exit);

    return 0;
}
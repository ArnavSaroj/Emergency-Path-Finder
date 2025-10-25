#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> buildGraphStructure(int &total_nodes)
{

    cout << "\n*** Building Evacuation Path Simulator ***\n";
    while (true)
    {
        cout << "How many rooms are in your building layout? ";
        if (cin >> total_nodes && total_nodes > 1)
        {
            break;
        }
        cout << "Not valid format of input. Please enter a number greater than 1.";
        cin.sync();
        cin.ignore(INT_MAX, '\n');
    }

    vector<vector<int>> layout_Room(total_nodes, vector<int>(total_nodes, 0));

    cout << "\n--- Defining the Connections ---" << endl;
    cout << "Enter room connections (edges). Rooms are numbered 0 to " << total_nodes - 1 << "." << endl;
    cout << "Enter 'room_A room_B' to connect them (e.g., '0 1')." << endl;
    cout << "Enter '-1 -1' to finish adding connections." << endl;

    int node_from, node_to;
    while (true)
    {
        cout << "Connection (Room A Room B, or -1 -1 to finish): ";

        if (!(cin >> node_from >> node_to))
        {
            cout << "Not valid format of input. You must enter two numbers." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (node_from == -1 && node_to == -1)
        {
            break;
        }

        if (node_from < 0 || node_from >= total_nodes || node_to < 0 || node_to >= total_nodes)
        {
            cout << "Error: Room numbers must be between 0 and " << total_nodes - 1 << ". Try again." << endl;
        }
        else if (node_from == node_to)
        {
            cout << "Skipping connection: A room cannot be connected to itself." << endl;
        }
        else
        {
            if (layout_Room[node_from][node_to] == 1)
            {
                cout << "Connection already exists between " << node_from << " and " << node_to << ". Skipping." << endl;
            }
            else
            {
                layout_Room[node_from][node_to] = 1;
                layout_Room[node_to][node_from] = 1;
                cout << "Connection established between Room " << node_from << " and Room " << node_to << endl;
            }
        }
    }

    return layout_Room;
}

vector<int> reconstructRoute(vector<int> &predecessor_array, int origin, int destination)
{
    vector<int> route_list;

    int current_node = destination;
    route_list.push_back(current_node);
    while (predecessor_array[current_node] != -2)
    {
        route_list.push_back(predecessor_array[current_node]);
        current_node = predecessor_array[current_node];
    }
    reverse(route_list.begin(), route_list.end());
    return route_list;
}

void findOptimalRoute(const vector<vector<int>> &graph_matrix, int origin, int destination)
{

    vector<int> predecessor_array(graph_matrix.size(), -1);
    predecessor_array[origin] = -2;
    queue<int> exploration_queue;

    exploration_queue.push(origin);
    while (!exploration_queue.empty())
    {
        int current_node = exploration_queue.front();
        exploration_queue.pop();
        if (current_node == destination)
        {
            cout << "exit path found" << endl;
            break;
        }
        for (int nb = 0; nb < graph_matrix.size(); nb++)
        {
            if (graph_matrix[current_node][nb] == 1 && predecessor_array[nb] == -1)
            {
                predecessor_array[nb] = current_node;
                exploration_queue.push(nb);
            }
        }
    }
    if (predecessor_array[destination] == -1)
    {
        cout << "no viable path found" << endl;
        return;
    }

    vector<int> optimal_route = reconstructRoute(predecessor_array, origin, destination);
    for (int jkf = 0; jkf < optimal_route.size() - 1; jkf++)
    {
        cout << optimal_route[jkf] << "->";
    }
    cout << optimal_route[optimal_route.size() - 1];
    cout << endl;
}

int main()
{
    int total_nodes;
    vector<vector<int>> building_graph = buildGraphStructure(total_nodes);

    int origin_room;
    cout << "enter starting room" << endl;
    cin >> origin_room;
    int destination_room;
    cout << "enter emergency exit room" << endl;
    cin >> destination_room;

    findOptimalRoute(building_graph, origin_room, destination_room);

    return 0;
}
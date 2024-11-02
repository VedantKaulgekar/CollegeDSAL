#include <iostream>
#include <climits>
#include <vector>
#include <stack>

using namespace std;

#define MAX_CITIES 100 // Define the maximum number of cities

// Struct to store information about each node in the BFS queue
struct QueueNode
{
    int stops;        // Number of stops made so far
    int node;         // Current city (node)
    int cost;         // Total cost to reach the current city
    vector<int> path; // Stores the path taken to reach the current city
};

// Class to represent the flight network as a graph
class Graph
{
private:
    int n;                               // Number of cities (nodes)
    int flights[MAX_CITIES][MAX_CITIES]; // Adjacency matrix to store flight prices

public:
    // Constructor to initialize the graph with n cities
    Graph(int n) : n(n)
    {
        // Initialize the adjacency matrix with high value (infinity)
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                flights[i][j] = (i == j) ? 0 : INT_MAX; // No cost to fly from a city to itself
            }
        }
    }

    // Function to add a flight between two cities
    void addFlight(int src, int dest, int price)
    {
        flights[src][dest] = price; // Set the flight price between src and dest
    }

    // Function to get the price of a flight from source to destination
    int getFlightPrice(int src, int dest)
    {
        return flights[src][dest];
    }

    // Function to get the number of cities in the graph
    int getCityCount()
    {
        return n;
    }
};

// Class to solve the problem of finding the cheapest price
class Solution
{
public:
    // Function to find the cheapest price from src to dst within k stops
    int findCheapestPrice(Graph &graph, int src, int dst, int k, vector<int> &route)
    {
        int price[MAX_CITIES]; // Array to store minimum prices to each city
        for (int i = 0; i < graph.getCityCount(); ++i)
        {
            price[i] = INT_MAX; // Initialize prices to infinity
        }
        price[src] = 0; // Starting city has a price of 0

        // BFS queue
        QueueNode queue[MAX_CITIES * (k + 1)];
        int front = 0, rear = 0;
        queue[rear++] = {0, src, 0, {src}}; // Start from the source city

        // BFS traversal
        while (front < rear)
        {
            int stops = queue[front].stops;
            int node = queue[front].node;
            int cost = queue[front].cost;
            vector<int> path = queue[front].path; // Get the current path
            front++;

            // If stops exceed k, no need to explore further
            if (stops > k)
                continue;

            // Explore the neighbors (flights)
            for (int next = 0; next < graph.getCityCount(); ++next)
            {
                if (graph.getFlightPrice(node, next) != INT_MAX)
                {
                    int nextCost = graph.getFlightPrice(node, next);

                    // If the new cost is cheaper, update and explore further
                    if (cost + nextCost < price[next])
                    {
                        price[next] = cost + nextCost;
                        vector<int> newPath = path; // Copy current path
                        newPath.push_back(next);    // Add the next city to the path
                        queue[rear++] = {stops + 1, next, price[next], newPath};

                        // If we reach the destination, update the route
                        if (next == dst)
                        {
                            route = newPath; // Store the final path in the route
                        }
                    }
                }
            }
        }

        // If no price was found for the destination, return -1
        return (price[dst] == INT_MAX) ? -1 : price[dst];
    }
};

// Function to display the main menu options
void displayMenu()
{
    cout << "=== Flight Pricing System ===" << endl;
    cout << "1. Add Flight" << endl;
    cout << "2. Find Cheapest Price" << endl;
    cout << "3. Exit" << endl;
    cout << "Choose an option: ";
}

int main()
{
    int n; // Number of cities
    cout << "Enter the number of cities: ";
    cin >> n;

    // Check if the number of cities is valid
    if (n <= 0 || n > MAX_CITIES)
    {
        cout << "Invalid number of cities. Please restart the program." << endl;
        return 1; // Exit with error
    }

    Graph graph(n);
    Solution solution;
    int choice;

    while (true)
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int src, dest, price;
            cout << "Enter source city (0 to " << n - 1 << "): ";
            cin >> src;

            if (src < 0 || src >= n)
            {
                cout << "Invalid source city. Please try again." << endl;
                break;
            }

            cout << "Enter destination city (0 to " << n - 1 << "): ";
            cin >> dest;

            if (dest < 0 || dest >= n)
            {
                cout << "Invalid destination city. Please try again." << endl;
                break;
            }

            cout << "Enter flight price: ";
            cin >> price;

            if (price < 0)
            {
                cout << "Invalid flight price. Please try again." << endl;
                break;
            }

            graph.addFlight(src, dest, price);
            cout << "Flight added successfully!" << endl;
            break;
        }
        case 2:
        {
            int src, dst, k;
            vector<int> route; // Vector to store the route
            cout << "Enter source city (0 to " << n - 1 << "): ";
            cin >> src;

            if (src < 0 || src >= n)
            {
                cout << "Invalid source city. Please try again." << endl;
                break;
            }

            cout << "Enter destination city (0 to " << n - 1 << "): ";
            cin >> dst;

            if (dst < 0 || dst >= n)
            {
                cout << "Invalid destination city. Please try again." << endl;
                break;
            }

            cout << "Enter maximum stops allowed: ";
            cin >> k;

            if (k < 0)
            {
                cout << "Invalid number of maximum stops. Please try again." << endl;
                break;
            }

            // Find the cheapest price and the route
            int cheapestPrice = solution.findCheapestPrice(graph, src, dst, k, route);
            if (cheapestPrice == -1)
            {
                cout << "No flights found within " << k << " stops." << endl;
            }
            else
            {
                cout << "The cheapest price from city " << src << " to city " << dst << " is: " << cheapestPrice << endl;
                cout << "The route is: ";
                for (int city : route)
                {
                    cout << city << " ";
                }
                cout << endl;
            }
            break;
        }
        case 3:
            cout << "Exiting the program. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

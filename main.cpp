#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <array>

using namespace std;

class ParkingSpot
{
public:
    char size;    // Size of the spot
    int occupied; // Indicates if the spot is occupied (1 for occupied, 0 for unoccupied)
    int priority;

    ParkingSpot(char s, int o)
    {
        this->size = s;
        this->occupied = o;
         if (s == 'S')
        {
            priority = 1;
        }
        else if (s == 'M')
        {
            priority = 2;
        }
        else if (s == 'L')
        {
            priority = 3;
        }
    }
};

class ParkingLot
{
public:
    ParkingSpot ***lot; // Private pointer to a 2D array of ParkingSpot
    int rows;
    int columns;

    // Default constructor to read occupancy status from a file
    ParkingLot()
    {
        // Open a file for reading occupancy status
        ifstream file("occupancy.txt");
        if (!file)
        {
            cerr << "Error opening file for reading." << endl;
            return;
        }

        // Read occupancy status and initialize the parking lot
        rows = 10;    // You can adjust this based on your file structure
        columns = 10; // You can adjust this based on your file structure

        lot = new ParkingSpot **[rows];
        for (int i = 0; i < rows; ++i)
        {
            lot[i] = new ParkingSpot *[columns];
            for (int j = 0; j < columns; ++j)
            {
                int occupancy_status;
                file >> occupancy_status;

                char size;
                if (j >= 0 && j <= 3)
                {
                    size = 'S';
                }
                else if (j >= 4 && j <= 6)
                {
                    size = 'M';
                }
                else
                {
                    size = 'L';
                }
                lot[i][j] = new ParkingSpot(size, occupancy_status); // Initialize with ParkingSpot objects
            }
        }

        file.close(); // Close the file
    }

    void printSpotSizes()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                cout << lot[i][j]->occupied;
            }
            cout << endl;
        }
    }

    // linear searchs
    vector<array<int, 2> >  filterEmptySpots(char vehicleSize)
    {
        vector<array<int, 2> > emptySpots;

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                if (lot[i][j]->occupied == 0 && lot[i][j]->size == vehicleSize)
                {
                    array<int, 2> coords = {i, j};
                    emptySpots.push_back(coords);
                }
            }
        }
        return emptySpots;
    }

//binary serach
vector<array<int, 2> > filterEmptySpotsBinarySearch(char vehicleSize)
    {
        vector<array<int, 2> > emptySpots;

        int vehiclePriority;
        if (vehicleSize == 'S')
        {
            vehiclePriority = 1;
        }
        else if (vehicleSize == 'M')
        {
            vehiclePriority = 2;
        }
        else if (vehicleSize == 'L')
        {
            vehiclePriority = 3;
        }
        else
        {
            // Handle invalid size
            return emptySpots;
        }

        for (int i = 0; i < rows; ++i)
        {
            int left = 0;
            int right = columns - 1;

            while (left <= right)
            {
                int mid = left + (right - left) / 2; // Calculate the middle column index

                if (lot[i][mid]->occupied == 0 && lot[i][mid]->size == vehicleSize)
                {
                    array<int, 2> coords = {i, mid};
                    emptySpots.push_back(coords);

                    int tleft=mid-1;
                    while (tleft >= 0 &&lot[i][tleft]->size == vehicleSize && lot[i][tleft]->occupied == 0) {
                        array<int, 2> coords = {i, tleft};
                        emptySpots.push_back(coords);
                        tleft--;
                    }
                    int tright=mid+1;
                    while (tright <10 &&lot[i][tright]->size == vehicleSize && lot[i][tright]->occupied == 0) {
                        array<int, 2> coords = {i, tright};
                        emptySpots.push_back(coords);
                        tright++;
                    }
                    break;

                }
                else if (lot[i][mid]->priority < vehiclePriority)
                {
                    left = mid + 1; // Search the right half
                }
                else
                {
                    right = mid - 1; // Search the left half
                }
            }
        }

        return emptySpots;
    }

    // Destructor to write occupancy status to a file
    ~ParkingLot()
    {
        ofstream file("occupancy.txt"); // Open a file for writing
        if (!file)
        {
            cerr << "Error opening file for writing." << endl;
            return;
        }

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                file << lot[i][j]->occupied << ' ';
            }
            file << endl;
        }

        file.close(); // Close the file
        cout << "Occupancy status written to file before destruction." << endl;

        // Deallocate memory
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                delete lot[i][j];
            }
            delete[] lot[i];
        }
        delete[] lot;
    }
};

int main()
{
    try
    {
        // Create a 10x10 parking lot with occupancy status read from the file
        ParkingLot parkingLot;

        parkingLot.printSpotSizes();

        // Take user input for vehicle size
        char vehicleSize;
        cout << "Enter your vehicle size (S for small, M for medium, L for large): ";
        cin >> vehicleSize;

        // Filter empty spots based on vehicle size
        vector<array<int, 2> > emptySpots = parkingLot.filterEmptySpotsBinarySearch(vehicleSize);

        // Display the filtered empty spots
        cout << "Empty spots for your vehicle size:" << endl;
        for (size_t i = 0; i < emptySpots.size(); ++i)
        {
            cout << "Row: " << emptySpots[i][0] << ", Column: " << emptySpots[i][1] << endl;
        }
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
 
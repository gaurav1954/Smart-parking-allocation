#include <iostream>
#include <fstream>
using namespace std;

class ParkingSpot
{
public:
    char size;    // Size of the spot
    int occupied; // Indicates if the spot is occupied (1 for occupied, 0 for unoccupied)

    ParkingSpot(char s, int o)
    {
        this->size = s;
        this->occupied = o;
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
                lot[i][j] = new ParkingSpot('S', occupancy_status); // Initialize with ParkingSpot objects
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

        // Modify the occupancy status
        parkingLot.lot[1][9]->occupied = 1; // Set as occupied (1)
        parkingLot.lot[9][9]->occupied = 0; // Set as unoccupied (0)
        parkingLot.printSpotSizes();
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}

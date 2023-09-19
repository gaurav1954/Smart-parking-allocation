#include <iostream>
using namespace std;

class ParkingSpot
{
public:
    char size;     // Size of the spot
    bool occupied; // Indicates if the spot is occupied

    ParkingSpot(char s)
    {
        this->size = s;
        this->occupied = false;
    }
};

class ParkingLot
{
private:
    ParkingSpot ***lot; // Private pointer to a 2D array of ParkingSpot
    int rows;
    int columns;

public:
    ParkingLot(int r, int c)
    {
        this->rows = r;
        this->columns = c;

        // Initialize the parking lot with the specified size
        lot = new ParkingSpot **[rows];
        for (int i = 0; i < rows; ++i)
        {
            lot[i] = new ParkingSpot *[columns];
            for (int j = 0; j < columns; ++j)
            {
                if (j < 5)
                    lot[i][j] = new ParkingSpot('S'); // Initialize with ParkingSpot objects
                else if (j < 10)
                    lot[i][j] = new ParkingSpot('M');
            }
        }
    }
    void printSpotSizes()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                cout << lot[i][j]->size;
            }
            cout << endl;
        }
    }

    // Destructor to free memory
    ~ParkingLot()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                delete lot[i][j]; // Delete each ParkingSpot object
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
        ParkingLot parkingLot(10, 10); // Create a 10x10 parking lot
        parkingLot.printSpotSizes();
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}

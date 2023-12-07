//
//  Location.h
//  
//
//  Created by Shreya Wagley 
//

#ifndef Location_h
#define Location_h

// Class definition for Location, representing a charging station
class Location {
public:
    // Properties of a Location
    int index;           // Key
    string locationName; // Name of the charging station
    bool chargerInstalled; // Indicates whether a charger is installed at the location
    double chargingPrice;  // Charging price per kilowatt-hour

    // Method to print location information
    void printLocation() {
        // Display formatted information about the location
        cout << setw(6) << index << setw(20) << locationName << setw(15);
        
        // Check if a charger is installed and display "yes" or "no"
        if (chargerInstalled)
            cout << "yes";
        else
            cout << "no";

        // Display charging price information based on conditions
        if (chargerInstalled && chargingPrice == 0)
            cout << setw(28) << "free of charge" << endl;
        else if (!chargerInstalled)
            cout << setw(17) << "N/A" << endl;
        else
            cout << setw(15) << "$" << setprecision(2) << chargingPrice << "/kWh" << endl;
    }

    // Overloaded less than operator to compare charging prices
    bool operator<(const Location& l) const {
        return chargingPrice < l.chargingPrice;
    }
};

#endif /* Location_h */

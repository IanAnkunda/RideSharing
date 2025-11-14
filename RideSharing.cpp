#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>

class Ride {
protected:
    std::string rideID;
    std::string pickupLocation;
    std::string dropoffLocation;
    double distance;
    double fareBase;
    double perMile;

public:
    Ride(std::string id, std::string pickup, std::string dropoff, double dist, double base, double pm)
        : rideID(std::move(id)), pickupLocation(std::move(pickup)), dropoffLocation(std::move(dropoff)),
          distance(dist), fareBase(base), perMile(pm) {}

    virtual ~Ride() = default;

    virtual double fare() const = 0; 
    virtual std::string type() const = 0;

    virtual void rideDetails() const {
        std::cout << "[" << type() << "] "
                  << "RideID: " << rideID
                  << " | From: " << pickupLocation
                  << " | To: " << dropoffLocation
                  << " | Distance: " << distance << " mi"
                  << " | Fare: $" << std::fixed << std::setprecision(2) << fare()
                  << std::endl;
    }

    double getDistance() const { return distance; }
    std::string getID() const { return rideID; }
};

class StandardRide : public Ride {
public:
    StandardRide(std::string id, std::string pickup, std::string dropoff, double dist)
        : Ride(std::move(id), std::move(pickup), std::move(dropoff), dist, /*base*/2.50, /*perMile*/1.50) {}

    double fare() const override {
        return fareBase + perMile * getDistance();
    }

    std::string type() const override {
        return "StandardRide";
    }
};

class PremiumRide : public Ride {
public:
    PremiumRide(std::string id, std::string pickup, std::string dropoff, double dist)
        : Ride(std::move(id), std::move(pickup), std::move(dropoff), dist, /*base*/5.00, /*perMile*/2.75) {}

    double fare() const override {
		//Added 10% for premium
        double raw = fareBase + perMile * getDistance();
        return raw * 1.10;
    }

    std::string type() const override {
        return "PremiumRide";
    }
};

class Driver {
private:
    std::string driverID;
    std::string name;
    double rating; 
    std::vector<std::shared_ptr<Ride>> assignedRides; 

public:
    Driver(std::string id, std::string n, double r)
        : driverID(std::move(id)), name(std::move(n)), rating(r) {}

    void addRide(const std::shared_ptr<Ride>& ride) {
        assignedRides.push_back(ride);
    }

    void getDriverInfo() const {
        std::cout << "Driver: " << name << " (ID: " << driverID << ")"
                  << " | Rating: " << rating << " | Completed Rides: "
                  << assignedRides.size() << "\n";
        for (const auto& r : assignedRides) {
            r->rideDetails();
        }
    }

    std::string getName() const { return name; }
    double getRating() const { return rating; }
};

class Rider {
private:
    std::string riderID;
    std::string name;
    std::vector<std::shared_ptr<Ride>> requestedRides; // Encapsulated

public:
    Rider(std::string id, std::string n) : riderID(std::move(id)), name(std::move(n)) {}

    void requestRide(const std::shared_ptr<Ride>& ride) {
        requestedRides.push_back(ride);
    }

    void viewRides() const {
        std::cout << "Rider: " << name << " (ID: " << riderID << ") Ride History:\n";
        for (const auto& r : requestedRides) {
            r->rideDetails();
        }
    }
};

int main() {
    std::cout << "=== Ride Sharing System Demo (C++) ===\n";

    std::vector<std::shared_ptr<Ride>> rides;
    rides.push_back(std::make_shared<StandardRide>("R-1001", "Downtown", "Airport", 12.3));
    rides.push_back(std::make_shared<PremiumRide>("R-1002", "Uptown", "Stadium", 7.8));
    rides.push_back(std::make_shared<StandardRide>("R-1003", "Campus", "Mall", 3.5));
    rides.push_back(std::make_shared<PremiumRide>("R-1004", "Hotel", "Conference Center", 2.2));

    Driver d("D-42", "Alex Morgan", 4.9);
    Rider r("U-77", "Jamie Lee");

    for (auto& ride : rides) {
        d.addRide(ride);
        r.requestRide(ride);
    }

    std::cout << "\n--  fare() and rideDetails() polymorphically --\n";
    double total = 0.0;
    for (const auto& ride : rides) {
        ride->rideDetails();  // virtual dispatch -> specific class implementation
        total += ride->fare();
    }
    std::cout << "Total fares (all rides): $" << std::fixed << std::setprecision(2) << total << "\n\n";

    // Show driver and rider info
    d.getDriverInfo();
    std::cout << "\n";
    r.viewRides();

    std::cout << "\n=== End Demo ===\n";
    return 0;
}

Object subclass: #Ride
    instanceVariableNames: 'rideID pickupLocation dropoffLocation distance fareBase perMile'
    classVariableNames: ''
    package: 'RideSharing'.

Ride >> initializeWith: anId pickup: pickup dropoff: dropoff dist: dist base: base perMile: pm [
    rideID := anId.
    pickupLocation := pickup.
    dropoffLocation := dropoff.
    distance := dist.
    fareBase := base.
    perMile := pm.
]

Ride >> type [ ^ 'Ride' ]
Ride >> distance [ ^ distance ]
Ride >> rideID [ ^ rideID ]

Ride >> fare [ self subclassResponsibility ]
Ride >> rideDetails [
    Transcript
        show: '[' , self type , '] ';
        show: 'RideID: ' , rideID , ' | From: ' , pickupLocation , ' | To: ' , dropoffLocation;
        show: ' | Distance: ' , distance asString , ' mi | Fare: $' , (self fare printString).
    Transcript cr.
]

Ride subclass: #StandardRide
    instanceVariableNames: ''
    classVariableNames: ''
    package: 'RideSharing'.

StandardRide class >> from: anId pickup: p dropoff: d dist: dist [
    ^ (self new)
        initializeWith: anId pickup: p dropoff: d dist: dist base: 2.5 perMile: 1.5;
        yourself.
]

StandardRide >> type [ ^ 'StandardRide' ]
StandardRide >> fare [ ^ fareBase + (perMile * self distance) ]

Ride subclass: #PremiumRide
    instanceVariableNames: ''
    classVariableNames: ''
    package: 'RideSharing'.

PremiumRide class >> from: anId pickup: p dropoff: d dist: dist [
    ^ (self new)
        initializeWith: anId pickup: p dropoff: d dist: dist base: 5.0 perMile: 2.75;
        yourself.
]

PremiumRide >> type [ ^ 'PremiumRide' ]
PremiumRide >> fare [
    | raw |
    raw := fareBase + (perMile * self distance).
    ^ raw * 1.10
]

Object subclass: #Driver
    instanceVariableNames: 'driverID name rating assignedRides'
    classVariableNames: ''
    package: 'RideSharing'.

Driver >> initializeWith: anId name: aName rating: aRating [
    driverID := anId.
    name := aName.
    rating := aRating.
    assignedRides := OrderedCollection new.
]

Driver >> addRide: aRide [
    assignedRides add: aRide.
]

Driver >> getDriverInfo [
    Transcript show: 'Driver: ', name, ' (ID: ', driverID, ') | Rating: ', rating asString, ' | Completed Rides: ', assignedRides size asString; cr.
    assignedRides do: [:r | r rideDetails].
]

Object subclass: #Rider
    instanceVariableNames: 'riderID name requestedRides'
    classVariableNames: ''
    package: 'RideSharing'.

Rider >> initializeWith: anId name: aName [
    riderID := anId.
    name := aName.
    requestedRides := OrderedCollection new.
]

Rider >> requestRide: aRide [
    requestedRides add: aRide.
]

Rider >> viewRides [
    Transcript show: 'Rider: ', name, ' (ID: ', riderID, ') Ride History:'; cr.
    requestedRides do: [:r | r rideDetails].
]

"Demo script"
| rides d r |
Transcript show: '=== Ride Sharing System Demo (Smalltalk) ==='; cr.
rides := OrderedCollection new.
rides add: (StandardRide from: 'R-2001' pickup: 'Downtown' dropoff: 'Airport' dist: 10.2).
rides add: (PremiumRide  from: 'R-2002' pickup: 'Uptown'   dropoff: 'Stadium' dist: 6.7).
rides add: (StandardRide from: 'R-2003' pickup: 'Campus'   dropoff: 'Mall'    dist: 4.1).

d := Driver new.
d initializeWith: 'D-77' name: 'Taylor Reed' rating: 4.8.

r := Rider new.
r initializeWith: 'U-55' name: 'Morgan Yu'.

rides do: [:ride | d addRide: ride. r requestRide: ride ].

Transcript show: '-- fare() and rideDetails() polymorphically --'; cr.
rides do: [:ride | ride rideDetails].

d getDriverInfo.
r viewRides.
Transcript show: '=== End Demo ==='; cr.

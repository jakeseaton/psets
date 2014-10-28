/**
 * service.js
 *
 * Computer Science 50
 * Problem Set 8
 *
 * Implements a shuttle service. Extra features: Points, Accelerate, Decelerate, populatefar
 */

// default height
var HEIGHT = 0.8;

// default latitude
var LATITUDE = 42.3745615030193;

// default longitude
var LONGITUDE = -71.11803936751632;

// default heading
var HEADING = 1.757197490907891;

// default number of seats
var SEATS = 10;

// default velocity
var VELOCITY = 50;

// maximum velocity
var MAXVELOCITY = 100;

// global reference to shuttle's marker on 2D map
var bus = null;

// global reference to 3D Earth
var earth = null;

// global reference to 2D map
var map = null;

// global reference to shuttle
var shuttle = null;

// global points
var points = 100;

// load version 1 of the Google Earth API
google.load("earth", "1");

// load version 3 of the Google Maps API
google.load("maps", "3", {other_params: "sensor=false"});

// once the window has loaded
$(window).load(function() {

    // listen for keydown anywhere in body
    $(document.body).keydown(function(event) {
        
        // update announcements
        $("#announcements").html("No announcements.");
        $("#announcements2").html("Try not to do that again");
        
        // return
        return keystroke(event, true);
    });

    // listen for keyup anywhere in body
    $(document.body).keyup(function(event) {
        return keystroke(event, false);
    });

    // listen for click on Drop Off button
    $("#dropoff").click(function(event) {
        dropoff();
    });

    // listen for click on Pick Up button
    $("#pickup").click(function(event) {
        pickup();
    });

    // load application
    load();
});

// unload application
$(window).unload(function() {
    unload();
});

/*
*   Ensures passengers are not outside their building
*/
function populatefar(house)
{
    // select a random building
    var building = BUILDINGS[Math.floor(Math.random() * BUILDINGS.length)];
    
    // chech it against their house
    if (building.lat == HOUSES[house].lat && building.lng == HOUSES[house].lng)
    {
        // choose a new one
        populatespread(house);
    }
    else
    {
        return building;
    }
}

/* 
* Updates and announces score.
*/
function score(x)
{
    // update points
    points += x;
    
    // update chart
    chart();
    
    if (points > 0)
    {
        // need design/style points
        var change = (x >= 0) ? "gained " : "lost ";

        // announce score change
        $("#announcements2").html("You " + change + x + " points");

        // if game is won
        if (points >= 1000)
        {
            alert("YOU WON!!!");
        }
    }
    else 
    {
         alert("YOU LOSE :(");
    }
    
}

/**
 * Renders seating chart.
 */
function chart()
{
    // initialize html chart with point counter at the top
    var html = ("Points: " + points + "<br/><ol start='0'>");
    
    // iterate over shuttle seats
    for (var i = 0; i < SEATS; i ++)
    {
        // if seat is empty
        if (shuttle.seats[i] == null)
        {
            // add an empty seat
            html += "<li>Empty Seat</li>";
        }
        else
        {
            // fill the seat
            html += "<li>" + shuttle.seats[i]["name"] + " " + shuttle.seats[i]["house"] + "</li>";
        }
    }
    
    // end the chart
    html += "</ol>";
    $("#chart").html(html);    
}

/**
 * Drops up passengers if their stop is nearby.
 */
function dropoff()
{
    // initialize counters
    var housesnear = 0;
    var onshuttle = 0;

    // iterate through houses
    for (var house in HOUSES)
    {
        // determine location of each house
        var lat = HOUSES[house].lat;
        var lng = HOUSES[house].lng;
        
        // store in temporary variable
        var d = shuttle.distance(lat, lng);

        // initialize counter
        var droppedoff = 0;

        // if house within 30 meters
        if (d <= 30)
        {
            // increment counter
            housesnear ++;

            // iterate over passengers on the bus
            for (var j = 0; j < SEATS; j++)
            {
                // if not an empty seat
                if (shuttle.seats[j] != null)
                {
                    // increment counter
                    onshuttle ++;

                    // if their house
                    if (shuttle.seats[j].house === house)
                    {
                        // announce
                        $("#announcements").html("You dropped " + shuttle.seats[j]["name"] +  " off at " + shuttle.seats[j]["house"]);

                        // drop them off
                        shuttle.seats[j] = null;

                        // increment counters
                        onshuttle ++;
                        droppedoff ++;

                        // increase score
                        score(100);
                    }
                }
                
            }

            // update chart
            chart();
            
            // if no one needed to go there
            if (droppedoff == 0)
            {
                // announce
                $("#announcements").html("None of your passengers need to go there!");
                
                // deduce points
                score(-10);
            }  
        }
    }

    // if there were no houses near
    if (housesnear == 0)
    {
        // announce
        $("#announcements").html("No houses near enough!");

        // deduct points
        score(-10);
    }

    // if there was no one on the shuttle
    if (onshuttle = 0)
    {
        // announce
        $("#announcements").html("There is no one on your shuttle!");
        
        // deduct points
        score(-10);

    }
}

/**
 * Called if Google Earth fails to load.
 */
function failureCB(errorCode) 
{
    // report error unless plugin simply isn't installed
    if (errorCode != ERR_CREATE_PLUGIN)
    {
        alert(errorCode);
    }
}

/**
 * Handler for Earth's frameend event.
 */
function frameend() 
{
    shuttle.update();
}

/**
 * Called once Google Earth has loaded.
 */
function initCB(instance) 
{
    // retain reference to GEPlugin instance
    earth = instance;

    // specify the speed at which the camera moves
    earth.getOptions().setFlyToSpeed(100);

    // show buildings
    earth.getLayerRoot().enableLayerById(earth.LAYER_BUILDINGS, true);

    // disable terrain (so that Earth is flat)
    earth.getLayerRoot().enableLayerById(earth.LAYER_TERRAIN, false);

    // prevent mouse navigation in the plugin
    earth.getOptions().setMouseNavigationEnabled(false);

    // instantiate shuttle
    shuttle = new Shuttle({
        heading: HEADING,
        height: HEIGHT,
        latitude: LATITUDE,
        longitude: LONGITUDE,
        planet: earth,
        seats: SEATS,
        velocity: VELOCITY
    });

    // synchronize camera with Earth
    google.earth.addEventListener(earth, "frameend", frameend);

    // synchronize map with Earth
    google.earth.addEventListener(earth.getView(), "viewchange", viewchange);

    // update shuttle's camera
    shuttle.updateCamera();

    // show Earth
    earth.getWindow().setVisibility(true);

    // render seating chart
    chart();

    // populate Earth with passengers and houses
    populate();
}

/**
 * Handles keystrokes.
 */
function keystroke(event, state)
{
    // ensure we have event
    if (!event)
    {
        event = window.event;
    }

    // left arrow
    if (event.keyCode == 37)
    {
        shuttle.states.turningLeftward = state;
        return false;
    }

    // up arrow
    else if (event.keyCode == 38)
    {
        shuttle.states.tiltingUpward = state;
        return false;
    }

    // right arrow
    else if (event.keyCode == 39)
    {
        shuttle.states.turningRightward = state;
        return false;
    }

    // down arrow
    else if (event.keyCode == 40)
    {
        shuttle.states.tiltingDownward = state;
        return false;
    }

    // A, a
    else if (event.keyCode == 65 || event.keyCode == 97)
    {
        shuttle.states.slidingLeftward = state;
        return false;
    }

    // D, d
    else if (event.keyCode == 68 || event.keyCode == 100)
    {
        shuttle.states.slidingRightward = state;
        return false;
    }
  
    // S, s
    else if (event.keyCode == 83 || event.keyCode == 115)
    {
        shuttle.states.movingBackward = state;     
        return false;
    }

    // W, w
    else if (event.keyCode == 87 || event.keyCode == 119)
    {
        shuttle.states.movingForward = state;    
        return false;
    }
    
    // Space
    else if (event.keyCode == 32)
    {
        if (shuttle.velocity < MAXVELOCITY)
        {
            shuttle.velocity += 10;
        }
    }

    // B, b
    else if (event.keyCode == 66 || event.keyCode == 98)
    {
        if (shuttle.velocity > 0)
        {
            shuttle.velocity -= 10;
        }
    }
    return true;
}

/**
 * Loads application.
 */
function load()
{
    // embed 2D map in DOM
    var latlng = new google.maps.LatLng(LATITUDE, LONGITUDE);
    map = new google.maps.Map($("#map").get(0), {
        center: latlng,
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        scrollwheel: false,
        zoom: 17,
        zoomControl: true
    });

    // prepare shuttle's icon for map
    bus = new google.maps.Marker({
        icon: "https://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/bus.png",
        map: map,
        title: "you are here"
    });

    // embed 3D Earth in DOM
    google.earth.createInstance("earth", initCB, failureCB);
}

/**
 * Picks up nearby passengers.
 */
function pickup()
{    
    // initialize counter
    var pickedup = 0;

    // iterate over PASSENGERS
    for (var i = 0; i < PASSENGERS.length; i++)
    {
        // if not already picked up
        if (PASSENGERS[i].placemark != null)
        {
            // calculate location of placemark
            var lat = PASSENGERS[i].placemark.getGeometry().getLatitude();
            var lng = PASSENGERS[i].placemark.getGeometry().getLongitude();

            // store distance to passenger in d
            var d = shuttle.distance(lat, lng);

            // if within 15 meters
            if (d <= 15)
            {
                    // initialize counter
                    var notfrosh = 0;

                    // iterate over passengers
                    for (var house in HOUSES)
                    {
                        // if there are in any of the houses
                        if (PASSENGERS[i].house === house)
                        {
                           notfrosh ++;
                        }

                    }

                    // if they weren't in any of the houses
                    if (notfrosh = 0)
                    {
                        // announce
                        $("#announcements").html("You can't pick them up");
                        score(-10);
                    }

                    // initialize counter
                    var emptyseats = 0;

                    // iterate over seats
                    for (var j = 0; j < SEATS; j++)
                    {
                        // if there is an empty seat
                        if (shuttle.seats[j] === null)
                        {
                            // increment counters
                            emptyseats ++;
                            pickedup ++;

                            // give them the seat
                            shuttle.seats[j] = PASSENGERS[i];

                            // removed placemark from 3d Map
                            var features = earth.getFeatures();
                            features.removeChild(PASSENGERS[i].placemark);
                            
                            // remove marker from 2d map
                            PASSENGERS[i].marker.setMap(null);

                            // set placemark to null
                            PASSENGERS[i].placemark = null;

                            // update the seating chart
                            chart();

                            break;
                        }

                    }
                    
                    // if there were no empty seats
                    if (emptyseats == 0)
                    {
                        // announce
                        $("#announcements").html("Not enough seats!");
                        
                        // deduct points
                        score(-10);
                    }
            }
        }

            
    }

    // if there were no passengers
    if (pickedup == 0)
    {
        // announce
        $("#announcements").html("No one close Enough!");
        
        // deduct points
        score(-10);
    }
}


/**
 * Populates Earth with passengers and houses.
 */
function populate()
{
    // mark houses
    for (var house in HOUSES)
    {
        // plant house on map
        new google.maps.Marker({
            icon: "https://google-maps-icons.googlecode.com/files/home.png",
            map: map,
            position: new google.maps.LatLng(HOUSES[house].lat, HOUSES[house].lng),
            title: house
        });
    }

    // get current URL, sans any filename
    var url = window.location.href.substring(0, (window.location.href.lastIndexOf("/")) + 1);

    // scatter passengers
    for (var i = 0; i < PASSENGERS.length; i++)
    {
        // select a random building that is not the passenger's house.
        var building = populatefar(PASSENGERS[i]["house"]);

        // prepare placemark
        var placemark = earth.createPlacemark("");
        placemark.setName(PASSENGERS[i].name + " to " + PASSENGERS[i].house);
        
        // prepare icon
        var icon = earth.createIcon("");
        icon.setHref(url + "/img/" + PASSENGERS[i].username + ".jpg");

        // prepare style
        var style = earth.createStyle("");
        style.getIconStyle().setIcon(icon);
        style.getIconStyle().setScale(4.0);

        // prepare stylemap
        var styleMap = earth.createStyleMap("");
        styleMap.setNormalStyle(style);
        styleMap.setHighlightStyle(style);

        // associate stylemap with placemark
        placemark.setStyleSelector(styleMap);

        // prepare point
        var point = earth.createPoint("");
        point.setAltitudeMode(earth.ALTITUDE_RELATIVE_TO_GROUND);
        point.setLatitude(building.lat);
        point.setLongitude(building.lng);
        point.setAltitude(0.0);

        // associate placemark with point
        placemark.setGeometry(point);

        // add placemark to Earth
        earth.getFeatures().appendChild(placemark);

        // add marker to map
        var marker = new google.maps.Marker({
            icon: "https://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/man.png",
            map: map,
            position: new google.maps.LatLng(building.lat, building.lng),
            title: PASSENGERS[i].name + " at " + building.name
        

        });
        
        // story placemark in passenger
        PASSENGERS[i].placemark = placemark; 
        
        // store marker in passenger
        PASSENGERS[i].marker = marker;

    }
}

/**
 * Handler for Earth's viewchange event.
 */
function viewchange() 
{
    // keep map centered on shuttle's marker
    var latlng = new google.maps.LatLng(shuttle.position.latitude, shuttle.position.longitude);
    map.setCenter(latlng);
    bus.setPosition(latlng);
}

/**
 * Unloads Earth.
 */
function unload()
{
    google.earth.removeEventListener(earth.getView(), "viewchange", viewchange);
    google.earth.removeEventListener(earth, "frameend", frameend);
}


#include "Map.hpp"
#include <SFML/Graphics.hpp>
#include <random>

// -----------------------------------------------------------------------
// Helper: tree
// -----------------------------------------------------------------------
void Map::addTree(float x, float y)
{
    sf::RectangleShape trunk(sf::Vector2f(10.f, 40.f));
    trunk.setFillColor(sf::Color(101, 67, 33));
    trunk.setPosition(sf::Vector2f(x - 5.f, y));
	trunk.setOutlineColor(sf::Color(60, 40, 20));
	trunk.setOutlineThickness(1.f);
    treeTrunks.push_back(trunk);

    sf::CircleShape top(20.f);
    top.setFillColor(sf::Color(34, 100, 34));
    top.setOrigin(sf::Vector2f(20.f, 20.f));
    top.setPosition(sf::Vector2f(x, y));
	top.setOutlineThickness(1.f);
	top.setOutlineColor(sf::Color(20, 60, 20));
    treeTops.push_back(top);
}

// -----------------------------------------------------------------------
// Helper: small house
// -----------------------------------------------------------------------
void Map::addHouse(float x, float y, sf::Color wallColor)
{
    sf::RectangleShape wall(sf::Vector2f(55.f, 45.f));
    wall.setFillColor(wallColor);
    wall.setOutlineColor(sf::Color(80, 60, 40));
    wall.setOutlineThickness(1.5f);
    wall.setPosition(sf::Vector2f(x, y));
    houseWalls.push_back(wall);

    sf::RectangleShape door(sf::Vector2f(12.f, 20.f));
    door.setFillColor(sf::Color(90, 55, 25));
    door.setPosition(sf::Vector2f(x + 21.f, y + 25.f));
    houseDoors.push_back(door);

    sf::RectangleShape window(sf::Vector2f(12.f, 10.f));
    window.setFillColor(sf::Color(173, 216, 230));
    window.setOutlineColor(sf::Color(80, 60, 40));
    window.setOutlineThickness(1.f);
    window.setPosition(sf::Vector2f(x + 6.f, y + 8.f));
    houseWindows.push_back(window);

    sf::ConvexShape roof;
    roof.setPointCount(3);
    roof.setPoint(0, sf::Vector2f(27.f, 0.f));
    roof.setPoint(1, sf::Vector2f(-3.f, 25.f));
    roof.setPoint(2, sf::Vector2f(58.f, 25.f));
    roof.setFillColor(sf::Color(153, 0, 0));
    roof.setOutlineColor(sf::Color(80, 30, 30));
    roof.setOutlineThickness(1.f);
    roof.setPosition(sf::Vector2f(x, y - 25.f));
    houseRoofs.push_back(roof);
}

// -----------------------------------------------------------------------
// Helper: dark grass patch
// -----------------------------------------------------------------------
void Map::addGrassPatch(float x, float y, float w, float h)
{
    sf::RectangleShape patch(sf::Vector2f(w, h));
    patch.setFillColor(sf::Color(50, 120, 50));
    patch.setPosition(sf::Vector2f(x, y));
    darkGrassPatches.push_back(patch);
}

// -----------------------------------------------------------------------
// Helper: Bryan Hall clock tower
//
// Building anatomy (all coords relative to x, y = top-left of main body):
//
//              [  tower cap  ]          y - 128
//              [ tower top   ]          y - 118  (belfry / white)
//              [  tower mid  ]          y - 88   (crimson with arched windows)
//  ___________ [ tower base  ] ___________
// |           main hip roof            |  y - 25  (gray trapezoid)
// |         MAIN BUILDING BODY         |  y to y+70
// |  windows  [  entrance  ]  windows  |
// |___________|____________|___________|
//
// -----------------------------------------------------------------------
void Map::addClockTower(float x, float y)
{
    const sf::Color crimson(155, 38, 30);   // WSU crimson brick
    const sf::Color darkGray(58, 58, 63);   // slate roof
    const sf::Color cream(230, 220, 195);   // white/cream trim & belfry
    const sf::Color glassBlue(173, 216, 230);   // window glass

    // ------------------------------------------------------------------
    // 1. MAIN BUILDING BODY  (170 x 70)
    // ------------------------------------------------------------------
    sf::RectangleShape mainBody(sf::Vector2f(170.f, 70.f));
    mainBody.setFillColor(crimson);
    mainBody.setPosition(sf::Vector2f(x, y));
    ctBrick.push_back(mainBody);

    // ------------------------------------------------------------------
    // 2. MAIN HIP ROOF  (trapezoid, gray slate)
    //    Wider at base (flush with building sides + 5px overhang)
    //    Narrows toward a ridge line 25px above building top
    // ------------------------------------------------------------------
    sf::ConvexShape mainRoof;
    mainRoof.setPointCount(4);
    mainRoof.setPoint(0, sf::Vector2f(x + 30.f, y - 25.f));   // ridge left
    mainRoof.setPoint(1, sf::Vector2f(x + 140.f, y - 25.f));   // ridge right
    mainRoof.setPoint(2, sf::Vector2f(x + 175.f, y));  // eave right
    mainRoof.setPoint(3, sf::Vector2f(x - 5.f, y));  // eave left
    mainRoof.setFillColor(darkGray);
    ctRoofs.push_back(mainRoof);

    // ------------------------------------------------------------------
    // 3. WHITE CORNICE TRIM  (thin strip at roofline)
    // ------------------------------------------------------------------
    sf::RectangleShape cornice(sf::Vector2f(180.f, 5.f));
    cornice.setFillColor(cream);
    cornice.setPosition(sf::Vector2f(x - 5.f, y - 5.f));
    ctTrim.push_back(cornice);

    // ------------------------------------------------------------------
    // 4. CLOCK TOWER BASE  (50 x 95, centered, rises above roof)
    //    Center of building = x + 85, so tower left = x + 60
    // ------------------------------------------------------------------
    float tx = x + 60.f;   // tower left edge
    float ty = y - 95.f;   // tower top (above roof)

    sf::RectangleShape towerBase(sf::Vector2f(50.f, 95.f));
    towerBase.setFillColor(crimson);
    towerBase.setPosition(sf::Vector2f(tx, ty));
    ctBrick.push_back(towerBase);

    // Thin white trim strip between tower and main roof
    sf::RectangleShape towerCornice(sf::Vector2f(58.f, 5.f));
    towerCornice.setFillColor(cream);
    towerCornice.setPosition(sf::Vector2f(tx - 4.f, ty + 87.f));
    ctTrim.push_back(towerCornice);

    // ------------------------------------------------------------------
    // 5. BELFRY / TOWER TOP SECTION  (58 x 20, cream colored)
    //    Slightly wider than tower, with white/cream color like the real
    //    white-painted upper section of Bryan Hall's tower
    // ------------------------------------------------------------------
    sf::RectangleShape belfry(sf::Vector2f(58.f, 20.f));
    belfry.setFillColor(cream);
    belfry.setOutlineColor(sf::Color(180, 170, 150));
    belfry.setOutlineThickness(1.f);
    belfry.setPosition(sf::Vector2f(tx - 4.f, ty - 20.f));
    ctBrick.push_back(belfry);

    // ------------------------------------------------------------------
    // 6. TOWER HIP ROOF (small gray trapezoid on top of belfry)
    // ------------------------------------------------------------------
    sf::ConvexShape towerRoof;
    towerRoof.setPointCount(4);
    towerRoof.setPoint(0, sf::Vector2f(tx + 22.f, ty - 38.f));  // ridge left
    towerRoof.setPoint(1, sf::Vector2f(tx + 28.f, ty - 38.f));  // ridge right
    towerRoof.setPoint(2, sf::Vector2f(tx + 56.f, ty - 20.f));  // eave right
    towerRoof.setPoint(3, sf::Vector2f(tx - 6.f, ty - 20.f));  // eave left
    towerRoof.setFillColor(darkGray);
    ctRoofs.push_back(towerRoof);

    // Small finial/spire on very top
    sf::RectangleShape finial(sf::Vector2f(4.f, 10.f));
    finial.setFillColor(sf::Color(80, 80, 85));
    finial.setPosition(sf::Vector2f(tx + 23.f, ty - 48.f));
    ctBrick.push_back(finial);

    // ------------------------------------------------------------------
    // 7. CLOCK FACE  (white circle centered in belfry)
    // ------------------------------------------------------------------
    sf::CircleShape clock(9.f);
    clock.setFillColor(sf::Color::White);
    clock.setOutlineColor(sf::Color(60, 60, 60));
    clock.setOutlineThickness(1.5f);
    clock.setOrigin(sf::Vector2f(9.f, 9.f));
    clock.setPosition(sf::Vector2f(tx + 25.f, ty - 10.f));
    ctClockFace.push_back(clock);

    // Clock hands (two thin rectangles crossing center)
    sf::RectangleShape hourHand(sf::Vector2f(3.f, 10.f));
    hourHand.setFillColor(sf::Color(30, 30, 30));
    hourHand.setOrigin(sf::Vector2f(0.75f, 7.f));
    hourHand.setPosition(sf::Vector2f(tx + 25.f, ty - 10.f));
    hourHand.setRotation(sf::degrees(-40.f));
    ctHands.push_back(hourHand);

    sf::RectangleShape minHand(sf::Vector2f(3.f, 10.f));
    minHand.setFillColor(sf::Color(30, 30, 30));
    minHand.setOrigin(sf::Vector2f(0.5f, 8.f));
    minHand.setPosition(sf::Vector2f(tx + 25.f, ty - 10.f));
    minHand.setRotation(sf::degrees(20.f));
    ctHands.push_back(minHand);

    // ------------------------------------------------------------------
    // 8. ARCHED WINDOWS on tower face (3 small windows, cream colored)
    // ------------------------------------------------------------------
    for (int i = 0; i < 3; i++)
    {
        sf::RectangleShape tw(sf::Vector2f(10.f, 14.f));
        tw.setFillColor(glassBlue);
        tw.setOutlineColor(cream);
        tw.setOutlineThickness(1.f);
        tw.setPosition(sf::Vector2f(tx + 7.f + i * 13.f, ty + 55.f));
        ctWindows.push_back(tw);
    }

    // ------------------------------------------------------------------
    // 9. MAIN BUILDING WINDOWS
    //    Two rows of 5 windows each across the front face
    // ------------------------------------------------------------------
    for (int row = 0; row < 2; row++)
    {
        float wy = y + 10.f + row * 26.f;
        for (int col = 0; col < 5; col++)
        {
            // Skip windows that overlap the clock tower footprint
            float wx = x + 8.f + col * 31.f;
            if (wx + 14.f > tx - 2.f && wx < tx + 52.f) continue;

            sf::RectangleShape win(sf::Vector2f(14.f, 16.f));
            win.setFillColor(glassBlue);
            win.setOutlineColor(cream);
            win.setOutlineThickness(1.5f);
            win.setPosition(sf::Vector2f(wx, wy));
            ctWindows.push_back(win);
        }
    }

    // ------------------------------------------------------------------
    // 10. CENTRAL ENTRANCE PORTICO
    //     Small protruding block at base center + pediment above it
    // ------------------------------------------------------------------
    sf::RectangleShape porticoBody(sf::Vector2f(40.f, 22.f));
    porticoBody.setFillColor(sf::Color(140, 33, 25));  // slightly darker brick
    porticoBody.setPosition(sf::Vector2f(x + 65.f, y + 48.f));
    ctBrick.push_back(porticoBody);

    // Entrance door
    sf::RectangleShape door(sf::Vector2f(16.f, 18.f));
    door.setFillColor(sf::Color(30, 20, 10));
    door.setPosition(sf::Vector2f(x + 77.f, y + 52.f));
    ctDoors.push_back(door);

    // Pediment (small triangle above entrance)
    sf::ConvexShape pediment;
    pediment.setPointCount(3);
    pediment.setPoint(0, sf::Vector2f(x + 85.f, y + 40.f));   // peak
    pediment.setPoint(1, sf::Vector2f(x + 63.f, y + 50.f));   // left
    pediment.setPoint(2, sf::Vector2f(x + 107.f, y + 50.f));  // right
    pediment.setFillColor(cream);
    ctPortico.push_back(pediment);

    // White trim strip across entrance top
    sf::RectangleShape entranceTrim(sf::Vector2f(44.f, 3.f));
    entranceTrim.setFillColor(cream);
    entranceTrim.setPosition(sf::Vector2f(x + 63.f, y + 48.f));
    ctTrim.push_back(entranceTrim);

    // ------------------------------------------------------------------
    // 11. DECORATIVE SHRUBS along the base (like in the photo)
    // ------------------------------------------------------------------
    for (int i = 0; i < 6; i++)
    {
        sf::CircleShape shrub(7.f);
        shrub.setFillColor(sf::Color(30, 90, 30));
        shrub.setOrigin(sf::Vector2f(7.f, 7.f));
        shrub.setOutlineColor(sf::Color(20, 60, 20));
        shrub.setOutlineThickness(1.0f);
        // Skip where the entrance door is
        float sx = x + 10.f + i * 27.f;
        if (sx > x + 60.f && sx < x + 110.f) continue;
        shrub.setPosition(sf::Vector2f(sx, y + 70.f));
        treeTops.push_back(shrub);  // reuse treetops vector for shrubs
    }
}

// -----------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------
Map::Map()
{
    generateGrassDetail(); // do this FIRST so it draws under everything
    // ---- Base background ----
    background.setSize(sf::Vector2f(1200.f, 900.f));
    background.setFillColor(sf::Color(85, 155, 75));

    // ================================================================
    // DARK GRASS PATCHES
    // ================================================================
    addGrassPatch(0.f, 260.f, 200.f, 230.f);
    addGrassPatch(20.f, 700.f, 110.f, 60.f);
    addGrassPatch(670.f, 200.f, 140.f, 80.f);
    addGrassPatch(645.f, 660.f, 100.f, 60.f);
    addGrassPatch(645.f, 460.f, 100.f, 60.f);
    addGrassPatch(885.f, 290.f, 200.f, 85.f);  // lawn in front of Bryan Hall
    addGrassPatch(950.f, 540.f, 250.f, 160.f);
    addGrassPatch(355.f, 500.f, 90.f, 70.f);

    // ================================================================
    // TREES
    // ================================================================
    // Zone A - far left strip
    addTree(110.f, 710.f);
    addTree(125.f, 720.f);
    addTree(45.f, 720.f);
    // ===============================================================
    // TREES NEXT TO HOUSES AND PATH AT START
	// ===============================================================
    addTree(105.f, 260.f);
    addTree(90.f, 310.f);
    addTree(103.f, 370.f);
	addTree(90.f, 440.f);

    //// Zone B - small top-center pocket
    addTree(425.f, 545.f);

    //// Zone C - upper right-center
    addTree(645.f, 220.f);
	// In front of Bryan Hall (Zone E)
    addTree(890.f, 320.f);
    addTree(1070.f, 330.f);

    //// Zone F - lower far-right
    addTree(1060.f, 545.f);
    addTree(1095.f, 555.f);
    addTree(1040.f, 585.f);
    addTree(1080.f, 620.f);

    //// Zone H - left-center pocket
    addTree(75.f, 800.f);
    addTree(30.f, 800.f);
    addTree(50.f, 855.f);
    addTree(100.f, 855.f);
    addTree(150.f, 855.f);
    addTree(200.f, 855.f);
    addTree(250.f, 855.f);
    addTree(300.f, 855.f);
    addTree(350.f, 855.f);
    addTree(400.f, 855.f);
    addTree(450.f, 855.f);
    addTree(500.f, 855.f);
    addTree(550.f, 855.f);
    addTree(600.f, 855.f);
    addTree(650.f, 855.f);
    addTree(700.f, 855.f);

    // ================================================================
	// SCHRUBS (small bushes along the base of houses, tower, path and Bryan Hall)
    // ================================================================
	addSchrub(980.f, 595.f);
    addSchrub(990.f, 600.f);
	addSchrub(1172.f, 585.f);
    addSchrub(1180.f, 595.f);
    addSchrub(1165.f, 595.f);
    addSchrub(1125.f, 595.f);
    addSchrub(985.f, 670.f);
    addSchrub(980.f, 680.f);
    addSchrub(990.f, 680.f);
    addSchrub(1000.f, 680.f);
    addSchrub(1175.f, 680.f);
    addSchrub(1120.f, 670.f);
    addSchrub(1125.f, 680.f);

    // ================================================================
    // HOUSES
    // ================================================================
    // Zone A
    addHouse(20.f, 310.f, sf::Color(20, 160, 700));
	addHouse(20.f, 250.f, sf::Color(200, 500, 987));
	addHouse(20.f, 370.f, sf::Color(10, 670, 16));
	addHouse(20.f, 430.f, sf::Color(203, 18, 165));

    //// Zone C
    addHouse(678.f, 210.f, sf::Color(653, 912, 310));
    addHouse(748.f, 210.f, sf::Color(843, 999, 752));

    //// Zone D
    addHouse(670.f, 450.f, sf::Color(272, 845, 145));
    addHouse(670.f, 650.f, sf::Color(666, 667, 437));

    //// Zone F
    addHouse(1120.f, 550.f, sf::Color(500, 500, 500));
    addHouse(980.f, 550.f, sf::Color(255, 1, 255));
    addHouse(980.f, 635.f, sf::Color(49, 185, 139));
    addHouse(1120.f, 635.f, sf::Color(200, 100, 120));

    //// Zone H
    addHouse(365.f, 500.f, sf::Color(200, 185, 160));
    // ================================================================
    // BRYAN HALL CLOCK TOWER  (Zone E, upper far-right)
    addClockTower(900.f, 280.f);
    addTallTower(40.f, 575.f);  // Zone A, far left strip
    // ================================================================
    // PATHS (unchanged)
    // ================================================================
    paths.push_back(Path({ 200.f, 75.f }, { 0.f,    100.f }, sf::Color::Yellow));
    paths.push_back(Path({ 75.f,  600.f }, { 200.f,  100.f }, sf::Color::Yellow));
    paths.push_back(Path({ 400.f, 75.f }, { 200.f,  700.f }, sf::Color::Yellow));
    paths.push_back(Path({ 75.f,  400.f }, { 525.f,  300.f }, sf::Color::Yellow));
    paths.push_back(Path({ 200.f, 75.f }, { 400.f,  300.f }, sf::Color::Yellow));
    paths.push_back(Path({ 75.f,  300.f }, { 400.f,   50.f }, sf::Color::Yellow));
    paths.push_back(Path({ 700.f, 75.f }, { 450.f,   50.f }, sf::Color::Yellow));
    paths.push_back(Path({ 75.f,  400.f }, { 1100.f,  50.f }, sf::Color::Yellow));
    paths.push_back(Path({ 300.f, 75.f }, { 800.f,  375.f }, sf::Color::Yellow));
    paths.push_back(Path({ 75.f,  400.f }, { 800.f,  375.f }, sf::Color::Yellow));
    paths.push_back(Path({ 400.f, 75.f }, { 800.f,  775.f }, sf::Color::Yellow));

    // ================================================================
    // WAYPOINTS (unchanged)
    // ================================================================
    waypoints = {
        {   0.f,  137.5f },
        { 237.5f, 137.5f },
        { 237.5f, 737.5f },
        { 562.5f, 737.5f },
        { 562.5f, 337.5f },
        { 437.5f, 337.5f },
        { 437.5f,  87.5f },
        {1137.5f,  87.5f },
        {1137.5f, 412.5f },
        { 837.5f, 412.5f },
        { 837.5f, 812.5f },
        {1200.f,  812.5f }
    };
}

// -----------------------------------------------------------------------
// Draw  — strict back-to-front layer order
// -----------------------------------------------------------------------
void Map::draw(sf::RenderWindow& window)
{
    // 1. Base grass
    window.draw(background);

    // 2. Dark grass patches
    for (auto& g : darkGrassPatches) window.draw(g);

    // 4. Yellow paths (always on top of terrain)
    for (auto& path : paths) window.draw(path);

    // 5. Regular houses
    for (auto& wall : houseWalls)    window.draw(wall);
    for (auto& door : houseDoors)    window.draw(door);
    for (auto& win : houseWindows)  window.draw(win);
    for (auto& roof : houseRoofs)    window.draw(roof);

    // 6. Bryan Hall clock tower (drawn as its own layered group)
    for (auto& b : ctBrick)     window.draw(b);    // brick walls
    for (auto& r : ctRoofs)     window.draw(r);    // slate roofs
    for (auto& t : ctTrim)      window.draw(t);    // white cornice + clock hands
    for (auto& w : ctWindows)   window.draw(w);    // windows
    for (auto& d : ctDoors)     window.draw(d);    // entrance door
    for (auto& p : ctPortico)   window.draw(p);    // entrance pediment
    for (auto& c : ctClockFace) window.draw(c);    // clock face circle
	for (auto& h : ctHands)     window.draw(h);    // clock hands

    for (auto& w : ttWalls)        window.draw(w);
    for (auto& b : ttBase)         window.draw(b);
    for (auto& t : ttTrim)         window.draw(t);
    for (auto& w : ttWindows)      window.draw(w);

    // 7. Trees + shrubs (always in front of buildings)
    for (auto& trunk : treeTrunks) window.draw(trunk);
    for (auto& top : treeTops)   window.draw(top);

    // 8. Debug waypoint lines
    for (size_t i = 0; i < waypoints.size() - 1; i++)
    {
        sf::Vertex line[2];
        line[0].position = waypoints[i];
        line[0].color = sf::Color::Red;
        line[1].position = waypoints[i + 1];
        line[1].color = sf::Color::Red;
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }
}

const std::vector<sf::Vector2f>& Map::getWaypoints() const
{
    return waypoints;
}

void Map::generateGrassDetail() // AI Help: Generates hundreds of tiny grass slivers scattered across the map for visual detail
{
    // Fixed seed = same result every run, no randomness at gameplay time
    std::mt19937 rng(60);

    std::uniform_real_distribution<float> xPos(0.f, 1200.f);
    std::uniform_real_distribution<float> yPos(0.f, 900.f);
    std::uniform_real_distribution<float> width(4.f, 22.f);
    std::uniform_real_distribution<float> height(2.f, 8.f);
    std::uniform_int_distribution<int>    colorVar(0, 120);

    for (int i = 0; i < 10000; i++)
    {
        float px = xPos(rng);
        float py = yPos(rng);
        float pw = width(rng);
        float ph = height(rng);
        int   cv = colorVar(rng);

        sf::RectangleShape sliver(sf::Vector2f(pw, ph));

        // Slight color variation so each sliver looks different
        sliver.setFillColor(sf::Color(
            45 + cv / 3,   // red channel (keep low)
            100 + cv,        // green channel (main variation)
            40 + cv / 4    // blue channel (keep low)
        ));

        sliver.setPosition(sf::Vector2f(px, py));
        darkGrassPatches.push_back(sliver);
    }
}

void Map::addTallTower(float x, float y)
{
    const sf::Color concrete(195, 185, 165);  // warm tan/gray concrete
    const sf::Color darkConcrete(160, 152, 135);  // shadow sides / recessed panels
    const sf::Color windowGlass(90, 120, 155);  // slightly reflective blue-gray
    const sf::Color windowFrame(170, 162, 145);  // concrete window surrounds
    const sf::Color cream(210, 205, 190);  // lighter trim bands

    // ------------------------------------------------------------------
    // 1. LOW PODIUM / BASE  (wider than tower, sits at ground level)
    //    Represents the lower 1-2 storey base section visible in photo
    // ------------------------------------------------------------------
    sf::RectangleShape podium(sf::Vector2f(90.f, 20.f));
    podium.setFillColor(darkConcrete);
    podium.setOutlineColor(sf::Color(120, 112, 100));
    podium.setOutlineThickness(1.f);
    podium.setPosition(sf::Vector2f(x - 10.f, y + 140.f));
    ttBase.push_back(podium);

    // Steps up to podium
    sf::RectangleShape steps(sf::Vector2f(50.f, 8.f));
    steps.setFillColor(sf::Color(175, 168, 152));
    steps.setPosition(sf::Vector2f(x + 15.f, y + 150.f));
    ttBase.push_back(steps);

    // Small step 2
    sf::RectangleShape steps2(sf::Vector2f(34.f, 5.f));
    steps2.setFillColor(sf::Color(185, 178, 162));
    steps2.setPosition(sf::Vector2f(x + 23.f, y + 155.f));
    ttBase.push_back(steps2);

    // ------------------------------------------------------------------
    // 2. LEFT WING / SHOULDER  (slight protrusion left of main tower)
    //    Matches the lower left section visible in the photo
    // ------------------------------------------------------------------
    sf::RectangleShape leftWing(sf::Vector2f(15.f, 50.f));
    leftWing.setFillColor(darkConcrete);
    leftWing.setPosition(sf::Vector2f(x - 5.f, y + 90.f));
    ttWalls.push_back(leftWing);

    // ------------------------------------------------------------------
    // 3. MAIN TOWER BODY  (tall narrow concrete slab, ~12 storeys)
    //    70 wide x 145 tall at position (x, y)
    // ------------------------------------------------------------------
    sf::RectangleShape tower(sf::Vector2f(70.f, 145.f));
    tower.setFillColor(concrete);
    tower.setOutlineColor(sf::Color(140, 132, 118));
    tower.setOutlineThickness(1.f);
    tower.setPosition(sf::Vector2f(x, y));
    ttWalls.push_back(tower);

    // Left edge shadow strip (brutalist towers have strong vertical shadows)
    sf::RectangleShape leftShadow(sf::Vector2f(6.f, 145.f));
    leftShadow.setFillColor(darkConcrete);
    leftShadow.setPosition(sf::Vector2f(x, y));
    ttTrim.push_back(leftShadow);

    // Right edge shadow strip
    sf::RectangleShape rightShadow(sf::Vector2f(6.f, 145.f));
    rightShadow.setFillColor(darkConcrete);
    rightShadow.setPosition(sf::Vector2f(x + 64.f, y));
    ttTrim.push_back(rightShadow);

    // ------------------------------------------------------------------
    // 4. HORIZONTAL FLOOR BANDS  (brutalist detail - each floor has a
    //    slight concrete ledge/spandrel band between window rows)
    // ------------------------------------------------------------------
    int numFloors = 11;
    float floorHeight = 145.f / numFloors;

    for (int i = 0; i <= numFloors; i++)
    {
        sf::RectangleShape band(sf::Vector2f(70.f, 2.5f));
        band.setFillColor(cream);
        band.setPosition(sf::Vector2f(x, y + i * floorHeight));
        ttTrim.push_back(band);
    }

    // ------------------------------------------------------------------
    // 5. WINDOW GRID
    //    4 columns x 11 rows of windows across the tower face
    //    Each window: 10w x 8h with concrete frame
    // ------------------------------------------------------------------
    for (int row = 0; row < numFloors; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            float wx = x + 10.f + col * 14.f;
            float wy = y + 4.f + row * floorHeight;

            // Window frame (concrete surround, slightly recessed look)
            sf::RectangleShape frame(sf::Vector2f(12.f, 10.f));
            frame.setFillColor(darkConcrete);
            frame.setPosition(sf::Vector2f(wx - 1.f, wy - 1.f));
            ttTrim.push_back(frame);

            // Glass pane
            sf::RectangleShape win(sf::Vector2f(10.f, 8.f));
            win.setFillColor(windowGlass);
            win.setPosition(sf::Vector2f(wx, wy));
            ttWindows.push_back(win);
        }
    }

    // ------------------------------------------------------------------
    // 6. ROOF TOP  (flat roof with small mechanical penthouse box
    //    and two small antenna spires, visible in photo)
    // ------------------------------------------------------------------

    // Roof parapet
    sf::RectangleShape parapet(sf::Vector2f(74.f, 5.f));
    parapet.setFillColor(darkConcrete);
    parapet.setPosition(sf::Vector2f(x - 2.f, y - 5.f));
    ttTrim.push_back(parapet);

    // Mechanical penthouse (small box on roof)
    sf::RectangleShape penthouse(sf::Vector2f(30.f, 12.f));
    penthouse.setFillColor(darkConcrete);
    penthouse.setPosition(sf::Vector2f(x + 20.f, y - 17.f));
    ttWalls.push_back(penthouse);

    // Left antenna
    sf::RectangleShape ant1(sf::Vector2f(2.f, 10.f));
    ant1.setFillColor(sf::Color(80, 80, 85));
    ant1.setPosition(sf::Vector2f(x + 27.f, y - 27.f));
    ttTrim.push_back(ant1);

    // Right antenna
    sf::RectangleShape ant2(sf::Vector2f(2.f, 8.f));
    ant2.setFillColor(sf::Color(80, 80, 85));
    ant2.setPosition(sf::Vector2f(x + 40.f, y - 25.f));
    ttTrim.push_back(ant2);
}

void Map::addSchrub(float x, float y)
{
    sf::CircleShape shrub(7.f);
    shrub.setFillColor(sf::Color(30, 90, 30));
    shrub.setOrigin(sf::Vector2f(7.f, 7.f));
    shrub.setOutlineColor(sf::Color(20, 60, 20));
    shrub.setOutlineThickness(1.0f);
    shrub.setPosition(sf::Vector2f(x, y));
	treeTops.push_back(shrub);  // reuse treetops vector for shrubs
}

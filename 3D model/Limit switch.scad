xNotchPos = 41.5;
xNotchSize = 1.8;
yNotchSize = 2;
zNotchSize = 5;

xRampPos = 16.5;
xTotal = xNotchPos+5;
yTotal = 7.6;
zLeft = -13.6;
zRight = -16.7;

xInnerSlotSize = 32;
xInnerSlotPos = 6.5;
yInnerSlotSize = 6.5;
yInnerSlotPos = -.1; //(yTotal - yInnerSlotSize)/2;
zInnerSlotSize = 6.3;

xTabSize = 3;
xOuterSlotSize = xInnerSlotSize - 2 * xTabSize;
xOuterSlotPos = xInnerSlotPos+xTabSize;

zSlotPos = 8;

xNubSize = 10;
xNubPos = 25;
zNubSize = 10;

xleftLugSize = 12.5;
yLeftLugSize = 1.5;
zLeftLugPos = -6.75;

xWiringPos = xRampPos+1;
xWiringSize = 5;
yWiringSize = 1.5;
yWiringPos = yTotal-yWiringSize+0.1;
zWiringSize = 3; //zSlotPos+zInnerSlotSize;

zMore = 20;



module main() {

    difference() {
        outer();
        inner_slot();
        outer_slot();
        notch();
        nub();
        left_lug();
        wiring();
        }

}

module outer() {
    rotate([90,0,0])
        translate([0,0,-yTotal])
            linear_extrude(height=yTotal)
                polygon([[0,0], [xTotal,0], [xTotal,zRight], [xRampPos,zRight], [0,zLeft]]);
}

module notch() {
    translate([xNotchPos, yTotal-yNotchSize, -zMore])
        cube([xNotchSize, yNotchSize+.1, zMore+.1]);
    translate([xNotchPos, -0.1, zRight-.1])
        cube([xNotchSize, yTotal+.2, zNotchSize+.1]);
}

module inner_slot() {
    translate([xInnerSlotPos, yInnerSlotPos, -zSlotPos])
        cube([xInnerSlotSize, yInnerSlotSize, zInnerSlotSize]);
}

module outer_slot() {
    translate([xOuterSlotPos, -1, -zSlotPos+.1])
        cube([xOuterSlotSize, 5, zSlotPos+.1]);
}

module nub() {
    translate([xNubPos, -.1, zRight-.1])
        cube([xNubSize,yTotal+.2,zNubSize]);
}

module left_lug() {
    translate([-.1, -.1, zLeftLugPos-10])
        cube([xleftLugSize+.1, yLeftLugSize+.1, 10]);
}

module wiring() {
    // vertical
    translate([xWiringPos, yWiringPos, zInnerSlotSize-zSlotPos-zMore-.1])
        cube([xWiringSize, yWiringSize, zMore+.1]);
    // horizontal
    translate([xWiringPos, -0.1, zRight-.1])
        cube([xWiringSize, yWiringPos+.2, zWiringSize+.1]);
}
main();
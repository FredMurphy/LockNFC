$fn=50;
pcbThick = 1.65;
pcbX = 60;
pcbY = 100;
pcbZ = 1;

fit = .2;

wallThick = 3;
wallSlot=1;
wallInner = wallThick-wallSlot;

cutY = wallThick+1;

boxX = pcbX + 2* wallInner;
boxY = pcbY + 2* wallInner;
boxZ = 20;

fixZ = boxZ-7;
fixY = 7;

module main() {
    difference() {
        cube([boxX, boxY, boxZ]);

        translate([wallThick, wallThick+fixY, wallThick])
            cube([boxX-2*wallThick, boxY-2*wallThick-fixY, boxZ]);

        translate([wallThick, wallThick, fixZ])
            cube([boxX-2*wallThick, boxY-2*wallThick, boxZ]);

        slot();

        cable();
        mounting();
        translate([15,-0.1,10]) m3screw();
        translate([boxX-15,-0.1,10]) m3screw();
    }
}

module upper() {
    difference() {
        main();
        translate ([-1,-1,-1]) cube([boxX+2, cutY+1, boxZ+2]);
    }
}

module fixture() {
    cube([boxX,cutY+fixY,fixZ]);
}

module m3screw() {
    rotate([-90,0,0]) {
        cylinder(r=3,h=2);
        cylinder(r=1.75,h=cutY+.1);
        cylinder(r=1.4,h=cutY+fixY+1);
    }
}

module cable() {
    translate([boxX/2,boxY/2,-1])
        cylinder(r=7.5,h=boxZ);
}

module mounting() {
    translate([boxX/2,boxY/2+35,-1]) cylinder(r=2,h=boxZ);
    translate([boxX/2,boxY/2-35,-1]) cylinder(r=2,h=boxZ);
}

module lower() {
    translate([0,0,-boxZ-1]) { // Move so you can see both
        difference() {
            main();
            translate ([-1,cutY,-1]) cube([boxX+2, boxY, boxZ+2]);
        }

    }
}

module PCB() {
    translate([wallInner+fit, wallInner+fit,boxZ-pcbZ-pcbThick])
        cube([pcbX,pcbY,pcbThick]);
}

module slot() {
       minkowski() {
            translate([0,0,-fit/2]) cylinder(r=fit, h=fit);
            PCB();
       }
}

upper();
//lower();
//%PCB();

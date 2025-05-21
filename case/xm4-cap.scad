//
// Right outside cup for WH1000-XM4
//

$fa = 1;
$fs = 0.2;

// Render the main body
show_cap = true;

// No custom additions, an OEM-adjacent design
oem_cap = false;

// Expose USB port
with_usb = true;

// Print only bottom ring
test_fit_print = false;

// Cut away part of the endcap for internal visibility
test_clearance_print = false;

// Cutaway view
half_view = false;

// Render PCB (run make in pcb/)
show_pcb = true;

// Replace the fancy render with a placeholder for test fits
dummy_pcb = false;

// Render buttons
show_buttons = true;
mounted_buttons = false;

// Render the microphone grill
show_grill = true;
mounted_grill = false;

// Maybe we can just stick a length of TPU filament in there?

gasket_thickness=1.75;

// mm between the button and the button hole
button_clearance = 0.1;

// Oversize the mic grill to make it stick
mic_grill_friction_fit = 0.05;

case_thickness = 0.9;
rim_width = 2.6;


outside_width = 69;
outside_height = 80;
outside_max_depth = 17.1;
top_circle_diameter = 57.5;
top_circle_angle_x = 1.9;
top_circle_angle_y = 5;
top_circle_off_x = 1;
top_circle_off_y = 1;
top_circle_off_z_c = 14.5;
inside_depth_c = top_circle_off_z_c - case_thickness;



pcb_thickness = 0.6;
usb_board_h = 4.5;

// The centers of the round radii of the mic hole

mic_hole_x1 = 6.27;
mic_hole_y1 = 39.39;

mic_hole_x2 = 11.96;
mic_hole_y2 = 37.49;

//mic_hole_xc = (mic_hole_x1 + mic_hole_x2) / 2;
mic_hole_xc = 17.34 - 9;
mic_hole_yc = (mic_hole_y1 + mic_hole_y2) / 2;
mic_hole_zc = 8;

// Mic hole frame protrusion to meet the mic
mic_hole_inside_protrude = 0.8;

// Actual opening
mic_hole_height = 2.5;

// The hole in the case
mic_hole_cut_height = 4;

// Actual opening
mic_hole_width = 8;
mic_hole_cc = mic_hole_width - mic_hole_height;


// Set mic_hole_feeler and tweak until the red panel just breaks the outside edge of the casing
mic_hole_feeler = false;
mic_hole_angle_x = 31.8;
mic_hole_angle_z = -1;
mic_hole_angle_y = -5;
mic_hole_distance = 36.4;
mic_grill_alignment = -1.2;
//mic_hole_angle_z = atan((mic_hole_y2 - mic_hole_y1) / (mic_hole_x2 - mic_hole_x1));




// Heading to the mic hole from the origin
mic_hole_dir_z = -atan((mic_hole_xc) / (mic_hole_yc));
mic_hole_dir_x = asin(mic_hole_zc / mic_hole_distance);


module bottom_outer_edge() {
    import("xm4-cap-outline-centered.svg", center=true);
}

module edge_with_rounding(radius) {
    
    difference() {
        minkowski() {
            resize([outside_width - 2*radius, outside_height - 2*radius, 0], true)
            linear_extrude(0.01, center=true)
                import("xm4-cap-outline-centered.svg", center=true);
            
            
            sphere(r=radius);
        }
        
        translate([0, 0, -radius])
        scale([outside_width*2, outside_height*2, radius*2])
        cube(center=true);
    }
}


module bottom_gasket(thickness=gasket_thickness,
                     center_width=outside_width - (rim_width),
                     center_height=outside_height - rim_width) {

    // Give the cutout it a little bit of a lip, to maybe hold on to the rubber gasket
    translate([0, 0, thickness/5])
    minkowski() {
        // A thin, flat sliver of the proper shape
        difference() {
            
            linear_extrude(0.01, center=true)
            resize([center_width+0.01, center_height+0.01, 0], true)
                bottom_outer_edge();
                
            
            linear_extrude(0.1, center=true)
            resize([center_width-0.01, center_height-0.01, 0], true)
                bottom_outer_edge();
        }
        
        sphere(d=thickness);
        
    }
}

// Position an element relative to the center of the PCB board's floor,
// i.e. center of the inside of the top circular cap
module inside_top_center() {
        translate([top_circle_off_x, top_circle_off_y, inside_depth_c])
        rotate([top_circle_angle_x, top_circle_angle_y, 0])
        children();
}

module top_circle() {
    translate([top_circle_off_x, top_circle_off_y, 0])
    translate([0, 0, top_circle_off_z_c])
    rotate([top_circle_angle_x, top_circle_angle_y, 0])
        linear_extrude(0.001, center=false)
        circle(d = top_circle_diameter);
}

module top_circle_with_rounding(radius, off_z_c, cap_radius_modifier=0) {
    translate([top_circle_off_x, top_circle_off_y, 0])
    translate([0, 0, off_z_c])
    rotate([top_circle_angle_x, top_circle_angle_y, 0])
    translate([0, 0, -radius])
    rotate_extrude() {
        translate([top_circle_diameter/2 - radius + cap_radius_modifier, 0, 0])
        circle(radius);
    }
}


module standard_cup_shape (width, height, depth_c=top_circle_off_z_c, rounding=1.75, cap_radius_modifier=0){

    
    hull() {
    
        // Slightly smaller, to prevent interference with hinge fork
        resize([width-0.2, height-0.2, 0], true)
        translate([0, 0, 3.1])
            edge_with_rounding(1.75);
    
        resize([width, height, 0], true)
        linear_extrude(0.01, center=false)
            bottom_outer_edge();
 
        
        top_circle_with_rounding(rounding, depth_c, cap_radius_modifier=cap_radius_modifier);
       
    }
}

module case_rim() {
    linear_extrude(7, center=false)
    difference() {
        bottom_outer_edge();
        
        resize([outside_width - 2*rim_width, outside_height - 2*rim_width, 0], true)
        bottom_outer_edge();
    }
    

}

module standard_case (cut=false) {
    
    if (!cut) {
        // The shell itself
        standard_cup_shape(outside_width, outside_height, top_circle_off_z_c);
        
    } else {
        // The inside cavity of the case
        
       
        // Naive approach. Scale the cup down in all directions to make
        // the cavity. This doesn't give a uniformly thick end cap,
        // so in slicing it may give a weird effect on the inside surface.
        translate([0, 0, -0.01])
        standard_cup_shape(outside_width-2*case_thickness, outside_height-2*case_thickness, inside_depth_c, rounding=0.5, cap_radius_modifier=-(case_thickness/2));
        
        // Route down the inside cap so it's perfectly flat (compared to the outside)
        inside_top_center() {
            translate([0, 0, -5])
            cylinder(5, top_circle_diameter/2-2, top_circle_diameter/2-1);
        }

    }
}


module screw_post(diameter, height, do_inner_support, inner_support_clearance, inner_support_length) {

        translate([0, 0, height/2])
        difference() {
                cylinder(h=height, r=diameter/2, center=true);
                cylinder(h=height*2, r=1.5/2, center=true);
        }
        
        // Outside support
        translate([0, diameter/2 - 0.2, 0.5])
        resize([1.2, diameter, height-1])
            translate([0, 0.5, 0.5])
            cube(1, center=true);
        
        if (do_inner_support) {
            // Inside support
            translate([0, -(diameter/2 - 0.2), inner_support_clearance])
            resize([1.2, inner_support_length + 0.2, height-inner_support_clearance])
                translate([0, -0.5, 0.5])
                cube(1, center=true);
        }
}

module peg(clearance=3, tip_radius=0.6, height=outside_max_depth, support=4) {
    union() {
    
        translate([0, 0, -(clearance - tip_radius)])
        sphere(tip_radius);
        
        translate([0, 0, -(clearance - tip_radius)])
        cylinder(h=height, r1= tip_radius, r2=tip_radius*1.2);
        
        // The support
        //translate([-tip_radius, 0, 0])
        //resize([tip_radius*2, support, height-clearance,])
        //cube();
        linear_extrude(height-clearance)
        polygon([
            [-tip_radius, 0],
            [tip_radius, 0],
            [2*tip_radius, support],
            [-2*tip_radius, support]
        ]);
    }
}

module screw_posts_and_pegs() {
    translate([0, 0, 2.9])
    union() {
        // Bottom front post
        translate([23.1, -20.2, 0])
        rotate([0, 0, 240])
        screw_post(3.5, outside_max_depth, true, 4.1, 1.2);
        
        // Bottom front peg
        translate([27.8, -12.1, 0.1])
        rotate([0, 0, -110])
        peg(support=4);
        
        // Bottom rear post
        translate([-19.5, -23.2, 0])
        rotate([0, 0, 130])
        screw_post(3.5, outside_max_depth, true, 7.2, 3);
        
        // Top front post
        translate([18.1, 28.3, 0])
        rotate([0, 0, -30])
        screw_post(3.5, outside_max_depth, false, 0, 0);
        
        // Top rear post
        translate([-17.1, 28.7, 0])
        rotate([0, 0, 10])
        screw_post(3.5, outside_max_depth, false, 0, 0);
        
        // Top rear peg
        translate([-20.5, 26.54, 0.1]) {
            rotate([0, 0, -57])
            peg(support=3.3);
            
            rotate([0, 0, 33])
            peg(support=3.7);
        }
        
    }
}

module flat_pill(cc, diameter) {
    hull() {
        translate([cc/2, 0, 0])
        circle(d = diameter);

        translate([-cc/2, 0, 0])
        circle(d = diameter);
    }
}

module rounded_cube(w, h, d, center=true, radius=0.2) {

    minkowski() {
        cube([w-2*radius, h-2*radius, d-2*radius], center=center);
        
        sphere(radius);
    }
}

module grill(cc, diameter, thickness, hole_r=2.9, hole_cc=2) {

    n_w = round((cc+diameter) / hole_cc) + 1;
    n_h = round(diameter / hole_cc) + 1;
    difference() {
        linear_extrude(thickness)
            flat_pill(cc, diameter);
            
        union() {
            for (y = [ -round(n_h/2):1:round(n_h/2) ]) {
                translate([0, y*hole_cc, 0])
                for (x = [ -round(n_w/2):1:round(n_w/2) ]) {
                    translate([ x*hole_cc, 0, 0 ])
                    rotate([0, 0, 45])
                    cube([sqrt(hole_r)/2, sqrt(hole_r)/2, 4], center=true);
                    
                    translate([ hole_cc/2, hole_cc/2, 0])
                    translate([ x*hole_cc, 0, 0 ])
                    rotate([0, 0, 45])
                    cube([sqrt(hole_r)/2, sqrt(hole_r)/2, 4], center=true);
                }
            }
        
        }
    }
}

module mic_cover() {

    total_depth = 1.2 + mic_hole_inside_protrude;
    
    // Print face down
    translate([0, 0, mic_hole_inside_protrude])
    rotate([180, 0, 0]) {
         //translate([0, 0, case_thickness-0.5])
         grill(mic_hole_cc, mic_hole_cut_height+mic_grill_friction_fit, 0.2);
         

         
         difference() {
         
                // The frame around the hole
                difference() {
                    union() {
                        linear_extrude(total_depth)
                        flat_pill(mic_hole_cc, mic_hole_cut_height+mic_grill_friction_fit);
                        
                        // A stopper to keep it from falling out of the hole
                        translate([0, 0, mic_hole_inside_protrude-0.4])
                        linear_extrude(0.4)
                        flat_pill(mic_hole_cc, mic_hole_cut_height+0.5);
                    }
                    
                    // Chamfer around the outside opening
                    translate([0, 0, total_depth-0.2])
                    hull() {
                        translate([0, 0, 0.5])
                        linear_extrude(0.01)
                        flat_pill(mic_hole_cc, mic_hole_cut_height);
                        
                        
                        linear_extrude(0.01)
                        flat_pill(mic_hole_cc, mic_hole_height);
                    }
                }

                union() {
                
               
                    // The small sound hole through the frame
                    translate([0, 0, -case_thickness])
                    linear_extrude(rim_width*3)
                    flat_pill(mic_hole_cc, mic_hole_height);
                }
         }
    }
}

module mic_hole(cut=false) {



    rotate([mic_hole_dir_x, 0, 0])
    rotate([0, 0, mic_hole_dir_z])
    translate([0, mic_hole_distance, 0])
    rotate([mic_hole_angle_x, 0, 0])
    rotate([0, 0, mic_hole_angle_z])
    rotate([0, mic_hole_angle_y, 0])
    rotate([90, 0, 0])

    if (cut) {
         // The big hole in the casing
         translate([0, 0, -case_thickness])
         linear_extrude(rim_width*3)
         flat_pill(mic_hole_cc, mic_hole_cut_height);
         
    } else {
    
        if (mic_hole_feeler) {
            // Indicator for mic_hole_distance. This should only just cut the outside of the case. Then comment it out.
            #linear_extrude(0.01)
            flat_pill(mic_hole_cc, mic_hole_cut_height+0.5);
        }
    
        if (show_grill && mounted_grill) {
            //rotate([180, 0, 0])
            translate([0, 0, -mic_grill_alignment])
            mic_cover();
        }

    }

}

module fork() {

    fork_round_r=0.4;

    translate([30.3, -2.4, 0])
    union() {
    
        
        hull() {
            translate([-1, 0, 0])
            cube([(1.4-fork_round_r) + 1.3 + 1.4, 5, 1]);
        
            // Round corners
            translate([-1, fork_round_r, 0])
            cylinder((1.4-fork_round_r), fork_round_r, fork_round_r);

            translate([-1, 5-fork_round_r, 0])
            cylinder((1.4-fork_round_r), fork_round_r, fork_round_r);
            
            translate([0, 0, 10])
            cube([1.3, 5, 0.1]);
        }

        translate([0, 0, -2.7])
        difference() {
            cube([1.3, 5, 2.7]);
         
            translate([0, 5/2, -(2 - (3.5-2.8))])
            rotate([0, 90, 0])
            //cylinder(3, 2, 2, center=true);
            cube([4,6,3], center=true);
        }
    }
}

module pcb_key() {
    

    inside_top_center()
    translate([0, -53/2, 0])
    translate([0, 0, 0]) {
        translate([0, 0.8/2, -0.5])
        cube([10.5, 0.8, 1], true);
        
        translate([0, 1, -0.5])
        cube([5.8, 2, 1], true);
    }
}



module oem_pcb() {

    color("#037A5E")
    inside_top_center()
    translate([0, 0, -pcb_thickness])
    difference() {
        linear_extrude(pcb_thickness)
        circle(d=53);
        
        
        union() {
        
            // Cutout for key
            #translate([0, (-53/2) +0.1, 0]) {
                translate([0, -(5 - 0.8), 0])
                cube([27, 10, 4], true);
                
                translate([0, 1, 0])
                cube([6, 2, 2], true);
            }
            
            // Weird angle cut at the top
            translate([0, (53/2)-2.2, 0])
            translate([0, 3, 0])
            cube([27, 6, 4],true);
        }
    }
}

module cad_pcb() {
    // This is exported from kicad
    include <../dist/pcb/tobo.scad>
}


module dummy_pcb() {

    color("#037A5E")
    inside_top_center()
    translate([0, 0, -pcb_thickness-0.01])
    
    union() {
        // Main PCB body
        difference() {
        
            linear_extrude(pcb_thickness)
                circle(25.5);
        
            union() {
                // Top cut
                translate([0, (20/2)+24, 0])
                cube([outside_width, 20, 3*pcb_thickness], center=true);
            
                // Bottom cut
                translate([0, -(20/2)-22.5, 0])
                cube([outside_width, 20, 3*pcb_thickness], center=true);
            }
        }
        
        // USB board
        translate([0, -37/2, pcb_thickness/2])
        cube([12.5, 37, pcb_thickness], center=true);
        
        // Button board
        difference() {
            linear_extrude(pcb_thickness)
            circle(32);
            
            union() {
                // Top edge
                rotate([0, 0, -5])
                translate([-35/2,35/2,pcb_thickness/2])
                cube([35, 35, 3*pcb_thickness], center=true);
                
                // Bottom edge
                rotate([0, 0, 44.9])
                translate([-35/2,-35/2,pcb_thickness/2])
                cube([35, 35, 3*pcb_thickness], center=true);
                
                // Off side
                translate([70/2, 0, pcb_thickness/2])
                cube([70, 70, 3*pcb_thickness], center=true);
            }
        }
    }
    /*
        inside_top_center()
        translate([-3.25, -6.5, -pcb_thickness/2]) // Offset the board origin
        rotate([0, 180, 0])
        linear_extrude(pcb_thickness, center=true)
        import("../dist/pcb/tobo-outline.svg", center=true);
    */
}

module pcb() {

    
    if (dummy_pcb) {
        //oem_pcb();
        dummy_pcb();
    } else {
    
        inside_top_center()
        translate([-3.25, -6.5, -pcb_thickness/2]) // Offset the board origin
        rotate([0, 180, 0])
        cad_pcb();
    }

    
}


module standard_cup() {

    intersection() {
    
        union() {
            difference() {
                union() {
                    difference() {
                        standard_case(false);
                        standard_case(true);
                    }
                    
                    screw_posts_and_pegs();
                    
                    // The bottom rim, which is wider
                    case_rim();
                    
                    // The protruding fork, which indexes to the hinge
                    fork();
                    
                    // A little quirky pi shape that helps locate the PCB
                    pcb_key();

                }
                
                union() {
                    if (gasket_thickness > 0) {
                        bottom_gasket();
                    }
                    
                    // Cut the big hole in the casing
                    mic_hole(true);
                }
            }
        }
        
        // Cut anything that fell outside the cup
        union() {
            standard_cup_shape(outside_width, outside_height, top_circle_off_z_c);
            
            mirror([0, 0, 1])
            standard_cup_shape(outside_width, outside_height, top_circle_off_z_c);
        }
    
    }
                                    
    // Insert the grill and embellishment
    mic_hole(false);

}

module keycap(cut=false, type=0, radius=2, length=7, depth=2, clearance=0.1) {

    pill_rot = [ -15, -10, 0, 10, 15 ];
    vert_offset = (length - 7.2)/2 +0.3;

    rotate([pill_rot[type], 0, 0])
    translate([0, 0, -1])
    if (!cut) {
    
        rotate([0, 90, 0])
        translate([vert_offset, 0, 0])
        difference() {
            // Basic pill shape
            linear_extrude(depth)
            flat_pill(length-(radius), radius-clearance);
            
            
            // Some sort of texture
            if (type == 2) {
                for (x = [ -6:1:6 ])
                    translate([x*0.7, 0, depth-0.1])
                    cube([0.4, radius*2, 0.4], center=true);
            
            }
            
        }
        
        
    } else {
        rotate([0, 90, 0])
        translate([vert_offset, 0, 0])
        linear_extrude(depth*5,center=true)
        flat_pill(length-radius, radius);
    }



}

module radial_button(cut=false, angle=180, cap_type=0, distance=32.25, vertical_center=pcb_thickness + 1.7, tipped_down=false) {

    peg_length=0.5;
    guide_length=0.7;
    cap_length = 2;
    
    tip_angle = tipped_down ? -90: 0;
    

    rotate([0, 0, angle])
    translate([distance, 0, -vertical_center])
    rotate([0, tip_angle, 0 ])
    {
        // Peg touching the actual switch
        translate([0, -1, -1])
        cube([peg_length+0.1,2,2], center=false);
        
        // A lip to keep the button from falling out
        translate([peg_length, 0, 0])
        rotate([0, 90, 0])
        if (!cut) {
            cylinder(guide_length, 2.2, 2.1);
        } else {
            translate([0, 0, -3*guide_length])
            cylinder(4*guide_length, 2.5, 2.1);
        }
        
        
        if (!cut) {
            // The visible button itself
            translate([peg_length+guide_length, 0, 0])
            keycap(false, cap_type, depth=cap_length, clearance=button_clearance);


        } else {
            translate([peg_length+guide_length, 0, 0])
            //rotate([0, 90, 0])
            keycap(true, cap_type, clearance=button_clearance);
        }
    }    
}

module buttons(cut=false, mounted=false, distance=32.25, vertical_center=pcb_thickness+1.7) {

    btn_angle = [ 180, 180+10, 180+20, 180+30, 180+40 ];

    inside_top_center()
    {
    
        if (mounted || cut) {
            
            // The buttons in their proper places
            for (i=[0:1:4]) {
                radial_button(cut, angle=btn_angle[i],    cap_type=i, distance=distance, vertical_center=vertical_center);
            }

        } else {
        
            if (!cut) {
                // The same buttons, but off to the side for printing
                for (i=[0:1:4]) {
                    radial_button(false, angle=btn_angle[i], cap_type=i, distance=distance + 8, tipped_down=true);
                }
            }
        }
    }
}

module button_box_cut(outer_radius=34.8, height=7.3, top_angle=180-5.5, bottom_angle=180+46.5) {
    
    rounding = 0.2;
    
    hull() {
    
        
        rotate([0, 0, top_angle])
        {
        
        
            // Outside face
            translate([0, 0, -rounding]) {
            
                // Bottom edge
                rotate_extrude(angle=bottom_angle - top_angle) {
                    translate([outer_radius - rounding-2.5, 0, 0])    
                    circle(rounding);
                }
                
                // Top edge
                translate([0, 0, -height-rounding])
                rotate_extrude(angle=bottom_angle - top_angle) {
                    translate([outer_radius - rounding-2.5, 0, 0])    
                    circle(rounding);
                }

            }
        }
        

        translate([0, 0, -rounding])
        sphere(rounding);

    }
}

module button_box(outer_radius=34.8, height=7, top_angle=180-5.5, bottom_angle=180+46.5) {
    
 
    rounding = 1;
    hull() {
    
        
        rotate([0, 0, top_angle])
        {
        
        
            // Outside face
            translate([0, 0, case_thickness-rounding]) {
            
                // Cap edge
                rotate_extrude(angle=bottom_angle - top_angle) {
                    translate([outer_radius - rounding, 0, 0])    
                    circle(rounding);
                }
                
                // Inside edge
                translate([0, 0, -height-rounding])
                rotate_extrude(angle=bottom_angle - top_angle) {
                    translate([outer_radius - rounding, 0, 0])    
                    circle(rounding);
                }

            }
        }
        

        // Imaginary corners inside the case, to make it less boxy
         rotate([0, 0, top_angle-10])
        {      
            
            // Cap edge
            rotate([0, 0, -5])
            translate([0, 0, case_thickness-rounding])
            rotate_extrude(angle=bottom_angle - top_angle+25) {
                translate([outer_radius-10 - rounding, 0, 0])    
                circle(rounding);
            }


            // Inside edge
            rotate([0, 16, 0])
            translate([0, 0, -height+1.5-rounding])
            rotate_extrude(angle=bottom_angle - top_angle+15) {
                translate([outer_radius-5 - rounding, 0, 0])    
                circle(rounding);
            }
            
            // Bottom ball cap
            //rotate([0, 0, bottom_angle - top_angle+30])
            //translate([outer_radius-10, 0, -5])
            //sphere(5.5);
            /*
            rotate([0, 0, bottom_angle - top_angle+30])
            translate([30, 0, -10])
            rotate([0, -20, 0])
            linear_extrude(10)
                circle(0.5);
            */
            /*
            // Top ball cap
            rotate([0, 0, 0])
            translate([outer_radius-10, 0, -5])
            sphere(5.5);
            */

        }
    }
}

module usb_box(cut=false) {

    clearance = 0.1;
    board_width = 12.5;
    cavity_width = board_width + clearance;
    cavity_depth = 13.4;
    groove_depth = 2;

    if (!cut) {
    
        translate([0, 0, -9/2])
        translate([0, -top_circle_diameter/2, 0])
        translate([0, 0, case_thickness])        // Align to the cup on the outside
        rounded_cube(13.5 + 2*case_thickness,
                     18+case_thickness,
                     9,
                     center=true, radius=1);
    
    } else {
    
        rotate([0, 0, 180])
        translate([0, top_circle_diameter/2, 0])
        {       // Align to the outer board edge and make room for USBC feet


             translate([0, -5, 0])
             {
            
                // The main cavity for the board and connector
                // Pulled back by 5mm to also cut the PCB key
                translate([-cavity_width/2, 0, -usb_board_h])
                cube([cavity_width, cavity_depth-groove_depth, usb_board_h], center=false);
                
                
                // It goes full depth inside the grooves
                translate([-(cavity_width-2)/2, 0, -usb_board_h])
                cube([cavity_width-2, cavity_depth, usb_board_h], center=false);
            
                // A shaped cavity at the inside of the USB box, which has grooves
                // to grab the PCB itself    
                translate([-cavity_width/2, 0, -pcb_thickness-4*clearance])
                cube([cavity_width, cavity_depth, pcb_thickness+4*clearance], center=false);
                
                // Cut above the groove
                //translate([-cavity_width/2, 0, -usb_board_h])
                //cube([cavity_width, cavity_depth, usb_board_h-pcb_thickness-clearance-0.5], center=false);
            }
            
            
            
                
            // A deeper trough in the center, to give the port's feet some clearance
            // The bottom has a ramp, to let the
            // PCB slide over more easily on assembly.
            translate([-5.25, -1, 0])
            hull() {
                translate([0, 1, 0.4])
                linear_extrude(0.01)
                square([10.5, 5.5/*ramp*/], center=false);
                
                translate([0, 0, -0.4])
                linear_extrude(0.01)
                square([10.5, 9], center=false);
            }
            
            // Expose the USB port itself
            translate([0, 0, -pcb_thickness-1.65])
            rotate([-90, 0, 0])
            linear_extrude(14)
            flat_pill(6, 3.1);

        }    
    }
}

module pcb_clip(width=2, depth=0.8, grab=0.4, clearance=0.05) {
    roots = 0.1;
    ramp_height = 1;
    support = 0.1;
    total_height = roots + pcb_thickness + clearance + ramp_height;

    // A ramp tooth
    //translate([width/2, -depth, -(total_height-ramp_height)])
    rotate([-90, 0, 0])
    rotate([0, -90, 0])
    linear_extrude(width, center=true)
    #polygon([
        [0,0],                  // Origin, 
        [0, pcb_thickness + clearance - support],     // Below inner corner support
        [support, pcb_thickness + clearance],     // Inner corner
        [grab,pcb_thickness + clearance],   // Bottom of tip
        [grab,pcb_thickness + clearance + ramp_height/3],    // Top of tip
        [-depth,total_height],   // Top of ramp
        [-depth,-roots],         // bottom back corner
        [0, -roots]              // bottom front corner
    ]);

}

module pcb_clips() {
        
        // Bottom rear
        translate([-10, -22.5, 0])
        rotate([0, 0, 0])
        pcb_clip();
        
        // Bottom front
        translate([10, -22.5, 0])
        rotate([0, 0, 0])
        pcb_clip();
        
        
        // Top
        translate([0, 24, 0])
        rotate([0, 0, 180])
        pcb_clip(width=10);
        
        // Front edge
        for (a=[-1:1:1]) {
            rotate([0, 0, 30*a])
            translate([25.5, 0, 0])
            rotate([0, 0, 90])
            pcb_clip(width=3);
        }
        
        // Rear edge
        for (a=[-25, -40]) {
            rotate([0, 0, a])
            translate([-25.5, 0, 0])
            rotate([0, 0, -90])
            pcb_clip(width=3);
        }
}

module cup_mod_interior_features() {
    // Added features on the inside of the cup
    
    
    inside_top_center() {
    
        // An origin pin
        /*
        if (show_pcb) {
            translate([0, 0, -1.5])
            cylinder(3, 0.2, 0.2, center=true);
        }
        */
        
        pcb_clips();
    }
    

}

module cup_mod_exterior_features() {
    difference() {
    
    
        // All these features are relative to the center of the PCB
        inside_top_center() {
        
            if (with_usb) {
                // Casing wraps around the USB port
                usb_box(false);
            }
            
            
            // Casing around the button cluster
            button_box();

        }
        
        
        union() {
            // Hollow out the inside
            // This way, exterior features can just extend into
            // the original cap and we trim them neatly.
            standard_case(true);

        }
    
    }

}

module cap_surface_cut() {
    inside_top_center() {
        translate([0, 0, 5+case_thickness-0.01])
        cube([outside_width, outside_height, 10], center=true);
    }
}



module cup_mod_cuts() {

    

    
    // The hole for the USB board
    {

        inside_top_center() {
        
            if (with_usb) {
                usb_box(true);
            }
        }
    }
    

    inside_top_center() 
    button_box_cut();
            
    // Holes for the buttons
    buttons(cut=true, mounted=mounted_buttons);
    
    // Flatten the outside cap perfectly
    cap_surface_cut();
}




module custom_cup() {
    difference() {
        union() {
            standard_cup();
            cup_mod_exterior_features();
        }
        
        // Cuts into the standard cup
        cup_mod_cuts();
   }
               
    // Added features
    cup_mod_interior_features();
    
}



intersection() {

    union() {
        if (show_cap) {
            if (oem_cap) {
                standard_cup();
            } else {
                custom_cup();
            }
        }
                  
        // The buttons
        if (show_buttons) {
            buttons(cut=false, mounted=mounted_buttons);
        }
        
            
        // If we're printing the grill outside the cap,
        // Just flop it down outside where it goes normally
        if (show_grill && !mounted_grill) {
        
            translate([0, outside_height*0.75, 0])
            mic_cover();
        }
    }
    
    
    {
        if (test_fit_print) {
            cube([outside_width*2, outside_height*2, 13], center=true);
        }
        
        if (test_clearance_print) {
            difference() {
                cylinder(h=outside_max_depth*3, r=outside_height*2, center=true);
             
                cylinder(h=outside_max_depth*2, r=outside_width/4, center=true);
                    
            }
        }
    
        if (half_view) {
            translate([outside_width, 0, 0])
            cube([outside_width*2, outside_height*2, outside_max_depth * 2], center=true);
        }
    }
}

if (show_pcb) {
    pcb();
}



//edge_with_rounding(1.75);
//bottom_outer_edge();

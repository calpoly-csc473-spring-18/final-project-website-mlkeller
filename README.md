This is my soft shadows implementation for the final project. 
Mitchell Keller

I choose the soft shadows because I thought that it looked very realistic and would benefit my experience with dealing with shadows.

Both the pov files are stored in my resources tab on the github.


Describe Exsisting Software Design

Since I had to implent some of the base code for the last parts of the assignment I will talk about my existing software design before I transfered over. One of the most important features that I implemented in my ray tracer was the object oriented style. I had everything broken down into classes that allowed me to easily read and access pieces of my code. I had the main object class which all the objects such as spheres, planes, and triangles extended to. This object class included fucntions for calculating the surface normal which all objects needed to do for the purpses of the ray caster. I also had the parser class that included all the functions for parsing the pov files. This made it so that parsing was organized and if anything needed to be parsed it could all be accessed from this class. Overall the structure of having all the classes organized made designing new features on top of the existing features much easier. 

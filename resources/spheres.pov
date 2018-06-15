// csc473, assignment 1 sample file (RIGHT HANDED)

camera {
  location  <0, 0, 14>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}


light_source {<-200, 200, 200> color rgb <1.5, 1.5, 1.5>}

sphere { <0, 0, 0>, 2
  pigment { color rgb <.2, .2, .8>}
  finish {ambient 0.2 diffuse 0.4}
  translate <0, 0, 0>
}

sphere { <-6.5, 0, 0>, 2
  pigment { color rgb <1.0, 0.05, 0.05>}
  finish {ambient 0.2 diffuse 0.4}
  translate <0, 0, 0>
}

sphere { <6.5, 0, 0>, 2
  pigment { color rgb <.7, .7, .2>}
  finish {ambient 0.2 diffuse 0.4}
  translate <0, 0, 0>
}

plane {<0, 1, 0>, -4
      pigment {color rgb <0.2, 0.2, 0.8>}
      finish {ambient 0.4 diffuse 0.8}
}



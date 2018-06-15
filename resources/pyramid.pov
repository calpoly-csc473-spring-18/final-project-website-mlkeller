// csc473, assignment 1 sample file (RIGHT HANDED)

camera {
  location  <0, 0, 14>
  up        <0,  1,  0>
  right     <1.33333, 0,  0>
  look_at   <0, 0, 0>
}


light_source {<-200, 200, -200> color rgb <1.5, 1.5, 1.5>}

triangle {
  <-.001,1, 0 >,
  <-.001, -6,6 >,
  <5,-6, 0 >
  pigment {color rgb <0.9, 0.8, 0.3>}
  finish {ambient 0.3 diffuse 0.4}
}

triangle {
  <0,1, 0 >,
  <-5, -6,0 >,
  <0,-6, 6 >
  pigment {color rgb <0.9, 0.8, 0.3>}
  finish {ambient 0.3 diffuse 0.4}
}


plane {<0, 1, 0>, -4
      pigment {color rgb <0.2, 0.2, 0.8>}
      finish {ambient 0.4 diffuse 0.8}
}



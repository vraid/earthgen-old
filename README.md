Earthgen - An earth-like planet generator
=
![](http://i.imgur.com/nMu0IMF.png)

What does it do?
-
Earthgen is a tool for generating planets with random geographical features and a semi-realistic climate with seasonal variation of temperature, wind and humidity based on these features. [A look at the gui](http://i.imgur.com/EiSyVs2.png).

The geometry consists of pentagonal and hexagonal tiles based on a subdivided icosahedron, with the planet shown having 21872 tiles (though more is certainly possible, [here](http://i.imgur.com/wYoo3Bn.png) is one with 196832 tiles).

Topography
-

![](http://i.imgur.com/zr4AWFf.png)

The topography is created using a fractal algorithm that raises triangular parts of the surface over n iterations. The sea is currently contiguous, and can be set to cover anything from none to all of the surface.

Temperature
-

![](http://i.imgur.com/9E5pog6.png)

The temperature varies by season, latitude and elevation. Temperature on land will change more rapidly than on water.

Humidity
-

![](http://i.imgur.com/nsNW2X2.png)

Humidity follows the wind patterns across the planet. Wind, in turn, is assumed to flow in idealised circulatory cells, before being affected by the coriolis effect.

Aridity
-

![](http://i.imgur.com/V2ge1q2.png)

Aridity, determined by temperature and humidity. In essence the potential evapotranspiration, or how much additional water vapour the air could carry in absolute terms. This is currently what determines vegetation density.

Seasonal variation
-
![](http://i.imgur.com/75OBxyR.gif)

Each season is saved as a separate entry. Making an animation, here out of 32 seasons, we get a better picture of how the climate varies over time.

The world at large
-

![](http://i.imgur.com/ifOXhpx.png)

A [hammer projection](http://en.wikipedia.org/wiki/Hammer_projection) of the world.
[Larger version](http://i.imgur.com/PZ8TPBA.png).
The biggest problem that I ran into on this assignment was the same problem as my last assignment, My program was
producing extra unpopulated pixels and addinging them to the picture. last time I fixed it by running a check to 
see if the pixel was populated with negative numbers. But I now have a edit that would reduce the color value to
below zero. Also I had to set it back under the maximum color value from the file specifications of our file. To
solve my problem I created a new private variable in each pixel called _max_value that has setters and getters.
To utilize my new variable to the extreame with the random noise edit i first set the _max_value to the value
from the ppm document then when each pixel is being filled it will run a check to see if the number is below zero
and since my error check started at -1 it was reseting it to zero and therefore putting it into my ppm doc. So I 
made a change to my operator function to intialize them to whatever the negative _max_value minus 1 and then in 
my error check for below zero, because the amount that random noise adds or subtracts can never be set to a value 
that is bigger that its color value. This check filters out my unpopulated pixels again and keeps my program
able to remain fluid and not be hard coded for specific values. I could not figure out how to write a for loop
that would loop through all of a pixels values in pixel like an auto for loop. I tried to look up documentation, 
but gave up quickly because I found an answer for another problem for the milestone. I resulted to just making a
base function that changes the number value for one color and and called it for each color in another function,
just like how my function to make a pixel is just me calling my setter for all three of the color values. If you 
have a thought about something just look straight at the documentation and see if there is a any semblance of what
you are looking for. If there is then keep presuing it, and if not then oh well, but you may come into contact
with a cool little feature that could help you with something that you may be needing. The most fun of the 
assignment was getting to test and run the do-while loop and being able to make many different chains of effects
and just to see what would happen, I ended up adding random noise to the same picture 10 times saving it as a new
version each time. The most chalenging part of my assignment was trying to figure out how resolve my error of 
checking below and above the pixel. By making it based off the max color value it could be kept it abstract enough
to be useable aand not be hard-coded. The most difficult part of the assignment to understand was the random 
calculation on how to get it to be between -10 and 10, because modulo math is still abit confusing to me and then 
having to subtract 10 took me a minute or 2 to conceptualize. Maybe going over all the kinds of recursive
statements and loops on Cplusplus.com would be nice because I learned stuff that, 1. I not only havent really seen
in the book, but also 2. dont really remember it from the book. I think I remember do-while statements from 
chapter 3.
When I was working on my project the biggest problem I ran into was that my program wouldnt check to see if the
stream actually had numbers. It took me a while to find out where the issue was coming from, but in the end I
realized that pixels were being added, I could tell because there were more rows then the height said their 
should be. I figured out that because of my while loop in the open function of my PpmDoc class was reading only 
the space at the end of the file since it read a space it determined that the line was still good and would 
create a new pixel, which I would automatically assign to 0,0,0, and therefore add it without really meaning to.
So i reintialized the pixels to start at -1,-1,-1 and then run a boolean check on each pixel to see if it was 
assigned values correctly, and on the ones that it wouldn't change because it was just a space my bool would 
return false and therefore not add it to my vector of pixels. An issue that I couldnt solve is that I couldnt
a way to do this error check by analyzing what was next in the istringstream. When I tried to see if what was
next in the stream was just a space Visual Studio kept telling me that i was trying to compare an int to a 
constant char, and then I also couldn't use the .length() function but then I found I wasn't able to use the
== operator. I started to look through the istringstream documentation and thought that its .peek() function
would be my answer but again i wasnt able to use the == operator, and I was comparing an int to a constant char.
My advice to students doing this assignment in the future is that you should use you breakpoints and rigid 
testing. My break points kept me sane while I was going through my code and I would go through peices of my code
and when I ran into a problem i would slowly go through my code part by part until I could figure out what was 
wrong and find my solution. Going through your code bit by bit allows you to find the problem and see why it 
was occuring and then gives you a general idea on how to solve it. The thing i enjoy the most abou these 
assignments is that I get to think about the logic away from the computer, I have less stress on me, and I 
feel it is because I can just think about the logic abstactly without having to also devote some of my brain
power at that moment to also type it up. I feel like I can think more freely and bounce ideas around in my
head. The most challenging part of the assignment was trying to figure out how to get rid of the added pixel on
every line, I kept trying to check the istringstream before the pixel was made, because I though that it would
be less computation, but I had to resort to checking the pixel after it was done being created to see if it was
done properly. Currently the most difficult part for me to understand is why the istringstream would be
represented as an int, I really don't know why that is, it probably has something to do with the actual 
characters in the line, but I couldn't find anything so I'm not that sure. I honestly dont think you really need
to do anything differently. With the notes that we do in the lecture, to the book, and google this assignment was
fairly straightforward, and if big problems arrise then we can come and talk to you to see what is happening. So
no I think that everything is fine because you give use all of the tools to go out there and figure it out for
ourselves.
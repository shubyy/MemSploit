# MemSploit
Made with wxWidgets and some other system libraries..
To use the program, just run the program as sudo
To compile the program, just run the following compile command in your directory.
`"g++ main.cpp -o main -no-pie -std=c++17 -lstdc++fs `wx-config --cxxflags` `wx-config --libs`"

This is just a project I did in my free time (I'm 17 so I dont have much time on my hands). I didn't bother commenting anything or making descriptive variable names, The layout is really bad too as a result, but I plan to work on this in the future in addition to adding more features, such as not just only scanning the stack, but the heap, other segments too and searching strings. For the time being it only scans and sets Int values and just scans the stack segment of the program.

If you want to improve the program by adding more features and improving the layout, go ahead! If you wish to add thee changes, just add a commit and I'll include it.

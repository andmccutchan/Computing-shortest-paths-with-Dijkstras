# Computing-shortest-paths-with-Dijkstras
## How to Run
To run this program, first make sure you have a file with data to be read in this directory. There are already some files in here to test, but if you would like to test your own, the file should follow this format:
    n m
    ID_1 x_1 y_y
    ...
    ID_n x_n y_n
    u_1 v_1 w_1 (s_1)*
    u_m v_m w_m (s_m)*
In this format, n is the number of verteces and m is the number of edges. The following n lines are data for each vertex, ID being the node ID x and y being its coordinates. Then, the following m lines are edge pairs and their weights. U and V are node IDs and W is their respective weight. S is an optional parameter, a string for a name to be assiciated with the edge (e.g. street name). Our program however does not currently support a way to display street names yet.

To run the program, simply type "make run" in a terminal. You will then be prompted to insert a file name, if no such file exists in the directory, the program will quit and you will have to insert a file and run again, or run again and fix any typos you might have had. After this you will be prompted to enter a start coordinate from the given file and an end coordniate. If the coordinate doesn's exist, or it was entered incorrectly, you will be continuously prompted until you enter a corret one. After you enter a valid start and end, the shortest path between the two will be displayed as:
    The shortest path from (x_start, y_start) to (x_end, y_end) is:
    (x_start, y_start) -> ... -> (x_end, y_end) with a weight of: &lt;Path weight&gt;
You can then enter more coordinates or click q at anytime to quit.


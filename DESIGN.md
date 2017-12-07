  In designing my project, my chief aim was to create a base from which further additions would be able to be created easily without needing
to reinvent and recode the core structures over and over again. With this in mind, I began by laying out the broader framework and creating
the functions necessary to manipulate that framework. Specifically, I created a Database class which would be the encompassing object for
any given data set. Within that, each Database possesses a vector of column pointers using C++'s smart pointers in order to handle memory
management smoothly. 

  The choice to make a vector of columns as opposed to a vector of rows was my first true design choice, and I did some research to make
an informed decision which led me to the distinction between "column-major" and "row-major" databases. Given that the majority of the 
operations which I intended to perform with the data would primarily manipulate single variables, having all the data for a variable in 
contiguous memory was the most sensible choice, so I chose to implement mine as a "column-major" database. The next challenge was to consider
which types of data would be allowable in the database and how to accomodate that data in the same framework. The first question seemed
fairly clear to me as my experience doing data analysis showed me that strings and numerical data were by far the most common data to do
analysis on, followed very distantly by categorical data. However, how to accommodate both of these data types in a logical and cohesive
framework was a challenge which I took some time in solving. Initially, I created a Column base class with two derivate classes, Str_Column
and Num_Column, which would hold strings and doubles, respectively. This was promising as a solution because my vector of column pointers
in the Database class could hold both these types simultaneously; unfortunately, this solution meant that every operation on the data had
to be encoded separately for the different classes which would have significantly increased the complexity of the code. Instead of this,
I chose to use the Boost library which is fairly standard to C++ because it had a class entitled "Variant" which was effectively a 
type-safe, dynamic union. This served my needs perfectly because I could now have a single Column class which simply had a vector of 
Boost::variant<double, std::string> objects to house the data itself. 

  Once this general framework was setup, it was time to implement a means to actually utilize it. The first step to this was of course
data-entry because without any data you can't manipulate a database. The CSV format was chosen for this because it has a very structured
formatting and it is incredibly universal as a data format. In order to read CSV files, I implemented a function called "Read_CSV" which 
took in a string filename and returned a pointer to a database object containing the data from that CSV file. This function required
learning how to parse files and strings using C++, and I again chose to use a function from the boost library to simplify and tighten my
code. The boost library has a function called "Tokenizer" which takes a string as a parameter and effectively returns a vector of substrings
based on a delimiter. In this case, I chose to use commas as delimiters, and I had to account for escape characters and commas within the
data using the escaped_list_separator subclass. 

  Once I had the data properly inputted into my database, it was fairly straightforward to create functions to manipulate it with. First, I
created a function which iterated through the data row by row and printed it to the console so that the user could see the data that they
were working with. Next, I had time to create a function which outputted descriptive statistics including mean, standard deviation, and 
range. The one difficulty that I encountered in this section was accounting for missing data in CSV files. To do this, I had to implement 
exceptions in all of my functions for "N/A" values which I represented in doubles as the most negative double possible and in strings as 
"N/A". Once that was done, I cleaned up the formatting of the results using the settings in printf in order to make the interface more
user-friendly. 

  Moving forward, I hope to refine and improve on this program in a couple of ways. First of all, I would like to be able to have my 
program act as a shell so that multiple operations can be done on the same database sequentially in between viewings of the data.
Further, I would like to implement more analysis operations such as linear regression.

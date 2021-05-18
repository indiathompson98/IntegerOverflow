Readme File for BufferOverflow.cpp

This program simulates an Online/Smart Snack Shop. The user should be able to create an account, log into the account with their credentials and purchase snacks by adding the quantity and money owed. At the end of the program, once everything is purchased the user should be prompted to pick up their snacks from the warehouse. The user should be able to continue purchasing until they wish to exit the program.

The overall goal of a successful exploit is for the user to be able to purchase snacks for the cost of nothing.

This is not necessary to make the program run but if needed ASLR can be turned off by using the following commands:

cat /proc/sys/kernel/randomize_va_space
echo "0" >> /proc/sys/kernel/randomize_va_space


To compile and run the BufferOverflow.cpp application, insert the following commands into terminal:

g++ -g -fno-stack-protecter -o BufferOverflowTest BufferOverflow.cpp
./BufferOverflowTest

*Run this program in either 32 or 64 bit Kali Linux*
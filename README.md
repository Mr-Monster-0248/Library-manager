<h1>_**Welcome to our project's github folder!**_</h1>
---
This project's aim is to implement a little software (there may be a GUI) to manage a small library with two databases: users and books.

* Each book has a code with 3 letters and 3 digits to identify the book: XXX-YYY<br />(example: NOV-255 stands for the 255th novel of the library)

* There must be two types of users: employees of the library and clients of the library.
  * Clients must be able to borrow books (for a certain amount of time) if they are availble
  * Employees must be able to have the complete inventory of available books
  * Employees must be able to see which clients did not returned their books in time
---
<h2>We had a few ideas to improve the software:</h2>
* When launching the program, a login page will be displayed, with two options: login to your account or create a new account
* Depending on your groupID (if you work for the library or not), you will have access to clients or employees functionalities
* To avoid everyone to modify the storage files (the databases), they will be encrypted in arrays of integers using a function that we implemented ourselves (simple encryption)
* To have the current date, we will simply use the system date (we must search the functions to obtain the date for both Ubuntu 16.04 and Windows 10)

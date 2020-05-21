# Player-Profile-Database
Profile database made in C++

There are 4 commands avalable:
- *search* : Enter the player's name to search for, and the record will be displayed and stored for editing
- *edit* : After searching for a record, its name and score can be edited. The record will be overwritten on the data file
   - **WARNING**: Do not set two records to have the same name, as only one of them will be able to be searched for
- *create* : Create a new record by entering a name and score to assign to it. The record will be added to the end of the data file
   - **WARNING**: Do not set two records to have the same name, as only one of them will be able to be searched for
- *display* : Display all records in the database. They are displayed in the order they are stored, which is alphabetical

If the binary file 'data.bin' does not exit in the directory, one is created with 5 generic records. Note that while debugging, the directory is /Player-Profile-Database/PlayerProfileDatabase, not the debug folder.

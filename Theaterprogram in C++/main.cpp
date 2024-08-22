// Zabkiel Vinas, Roberto Andino
// 3/20/18
// 7-20 Programming Challenge

/*                 Seats
       123456789012345678901234567890
Row 1  ***###***###*########*****####
Row 2  ####*************####*******##
Row 3  **###**********########****###
Row 4  **######**************##******
Row 5  ********#####*********########
Row 6  ##############************####
Row 7  #######************###########
Row 8  ************##****############
Row 9  #########*****############****
Row 10 #####*************############
Row 11 #**********#################**
Row 12 #############********########*
Row 13 ###***********########**######
Row 14 ##############################
Row 15 ##############################

*/

#include <iostream>
#include <fstream>
// For colored text
#include <windows.h>

using namespace std;


const int COLS = 30;
const int ROWS = 15;


// User Menu
void mainMenu(double [ROWS],char [][COLS]);
void displaySeats(double [ROWS], char [][COLS], int value);

// Only runs when the prices aren't set
void setPrices(double [ROWS], char [][COLS]);

// To show ticket prices
void TicketPrices(double [ROWS], char [][COLS]);

// Where the user makes their purchase
void buySeat(double [ROWS], char [][COLS]);
void Checkout (double [ROWS], char [][COLS], double, int [][COLS]);

// Saves information
void savePrices(double [ROWS]);
void saveSeats(char [][COLS]);

//loads information
int loadSavedInfo(double [ROWS], char [][COLS]);

// Best lines of code here (validates int)
void validate(int);

void compareSeats(double prices[ROWS], char[][COLS], int [][COLS], int);
void reviewOrder(double [ROWS], char [][COLS], double, int [][COLS]);

//colors text
void textcolor(int);


///////////////////////////////////This line separates functions for easier locating//////////////////////////////////////////////////////////////////

int main()
{
    // Sets the background Black with white text
    system("Color 0F");

    // set default seats with prices at zero
    char seats[ROWS][COLS]=  {{'*','*','*','#','#','#','*','*','*','#','#','#','*','#','#','#','#','#','#','#','#','*','*','*','*','*','#','#','#','#'},
                              {'#','#','#','#','*','*','*','*','*','*','*','*','*','*','*','*','*','#','#','#','#','*','*','*','*','*','*','*','#','#'},
                              {'*','*','#','#','#','*','*','*','*','*','*','*','*','*','*','#','#','#','#','#','#','#','#','*','*','*','*','#','#','#'},
                              {'*','*','#','#','#','#','#','#','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#','#','*','*','*','*','*','*'},
                              {'*','*','*','*','*','*','*','*','#','#','#','#','#','*','*','*','*','*','*','*','*','*','#','#','#','#','#','#','#','#'},
                              {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','*','*','*','*','*','*','*','*','*','*','*','*','#','#','#','#'},
                              {'#','#','#','#','#','#','#','*','*','*','*','*','*','*','*','*','*','*','*','#','#','#','#','#','#','#','#','#','#','#'},
                              {'*','*','*','*','*','*','*','*','*','*','*','*','#','#','*','*','*','*','#','#','#','#','#','#','#','#','#','#','#','#'},
                              {'#','#','#','#','#','#','#','#','#','*','*','*','*','*','#','#','#','#','#','#','#','#','#','#','#','#','*','*','*','*'},
                              {'#','#','#','#','#','*','*','*','*','*','*','*','*','*','*','*','*','*','#','#','#','#','#','#','#','#','#','#','#','#'},
                              {'#','*','*','*','*','*','*','*','*','*','*','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','*','*'},
                              {'#','#','#','#','#','#','#','#','#','#','#','#','#','*','*','*','*','*','*','*','*','#','#','#','#','#','#','#','#','*'},
                              {'#','#','#','*','*','*','*','*','*','*','*','*','*','*','#','#','#','#','#','#','#','#','*','*','#','#','#','#','#','#'},
                              {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
                              {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}};

    double prices[ROWS] = {0.0};

    //If the prices haven't been set, then set them
    if (loadSavedInfo(prices, seats) == 0)
        setPrices(prices, seats);

    //Go to Main Menu
    mainMenu(prices, seats);

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mainMenu(double prices[], char seats[][COLS])
{
    //Load saved files
    loadSavedInfo(prices, seats);

    int choice = 0;

    // Clears the screen
    system("cls");

    //Menu
    cout << "---------------------------------------" << endl
         << "||   Welcome to The Console Theater  ||" << endl
         << "||-----------------------------------||" << endl
         << "|| Currently Playing:The ASCII Movie ||" << endl
         << "---------------------------------------" << endl
         << "      What would you like to do?" << endl
         << "            1. View Seats" << endl
         << "            2. Buy a seat" << endl
         << "            3. Show Ticket Prices" << endl
         << "            4. Exit" << endl
         << "Enter Choice: ";
    cin >> choice;
    cout << endl;

    //Input Validation (lifesaver)
    if (choice< 1|| choice > 3)
        validate(choice);

    //Outputs
    switch (choice)
    {
    case 1: displaySeats(prices, seats, 1);
            break;
    case 2: buySeat(prices, seats);
            break;
    case 3: TicketPrices(prices, seats);
            break;
    case 4: savePrices(prices);
            saveSeats(seats);
            exit(0);

    //Reset input
    default: cout << "Please enter a valid choice!" << endl;
             mainMenu(prices, seats);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Asks for the prices of each row
void setPrices(double prices[ROWS], char seats[][COLS])
{
    // loops to set prices
    for (int i = 0; i<ROWS; i++)
    {
        cout << "Please enter the price of row number " << i+1 << ": ";
        cin >> prices[i];
    }
    system("cls");

    // saves and returns to menu
    savePrices(prices);
    saveSeats(seats);
    mainMenu(prices, seats);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Displays the seating arrangements
void displaySeats(double prices [ROWS], char seats[][COLS], int value)
{
    // load the seats
    loadSavedInfo(prices, seats);
    if(value>-1)
    cout << endl << "Here are the available seats." << endl;
    cout << endl
         << "         -----------------------------------Screen---------------------------------------" << endl << endl
         << "         1 2 3 4 5 6 7 8 9 10 11 12 13 14 15"
         << " 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30" << endl;


    for (int i=0; i<ROWS; i++)
    {
        cout << "Row " << i+1 << ": ";
        if (i<9)
            cout << " ";

        for (int k =0; k<COLS; k++)
        {
            cout << ' ';
            if (k>9)
                cout << " ";
                if(seats[i][k]=='*')
                    textcolor(4);

                if(seats[i][k]=='#')
                    textcolor(2);

            cout << seats[i][k];
            textcolor(15);
        }
        cout << endl << endl;
        }
    cout << endl;
    cout << "Seats Available: "; textcolor(2);
    cout << "# "; textcolor(15);
    cout << "Seats Taken:"; textcolor(4);
    cout << "*   \n\n"; textcolor(15);

    // pauses the console
    system("pause");

    if (value == 1)
    mainMenu(prices, seats);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Allows for the purchasing of seats
void buySeat(double prices[ROWS], char seats[][COLS])
{
    double total= 0;
    int chosen[ROWS][COLS] = {0};
    int row= 0;
    int col=0;
    // used for asking in checkout
    char answer='y';
    int tickets=0;
    // Tickets in cart
    int tic=0;

    displaySeats(prices, seats, 0);


    cout << endl <<"How many seats would you like to buy?" << endl
         << "Enter seats: ";
    cin >> tickets;
        if (tickets>15||tickets<1)
            validate(tickets);

    // loop that asks for the seat location
    for (int i =0; i < tickets;)
    {
        cout << endl << "Which seat would you like to purchase?" << endl
            << "Enter row: ";
        cin >> row;
            if (row>15||row<1)
                validate(row);

        cout << "Enter column: ";
        cin >> col;
            if (col>30 || col <1)
                validate(col);


        if (seats[row-1][col-1] == '*')
            cout << endl << "Sorry that seat is taken." << endl;

        if (seats[row-1][col-1] == '#')
        {
            total += prices[row-1];
            chosen[row-1][col-1]= '#';
            // Adds one to tickets in cart
            tic ++;
            tickets--;
            cout << endl << "Your total is now $" << total << " (" << tic << " tickets in cart)." << endl;
        }
    }

    // If you have picked out a seat ask to go to checkout
    if (total>0)
    {
        cout << "Would you like to go to checkout? (y/n) (Not going to checkout will cancel your order)" << endl;
        cout << "Enter Choice: ";
        cin >> answer;

        if(answer == 'y' || answer == 'Y' || answer == '1')
            Checkout(prices, seats, total, chosen);
    }

    else
    {
        savePrices(prices);
        saveSeats(seats);
    }

    mainMenu(prices, seats);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Checkout the seats the user picked
void Checkout(double prices [ROWS], char seats[][COLS], double total, int chosen[][COLS])
{

    int choice = 0;

    do
    {
        system("cls");

        cout << "              This is the Checkout. " << endl << endl
            << "      You currently have $" << total << " in you cart." << endl
            << " Would you like to pay now or cancel your order?" << endl
            << "                   1. Pay Now"<< endl
            << "                   2. Review Order" << endl
            << "                   3. Cancel Order" << endl
            << "Enter Choice: ";
        cin >> choice;

        if(choice>4 || choice<1)
        validate(choice);

        switch(choice)
        {
            // Purchases the seats
            case 1:
                // Sets the seats to taken
                compareSeats(prices, seats, chosen, 1);

                // Outputs total
                cout << endl << "Your total was $" << total << "." << endl
                    << "Thank you for your purchase!" << endl;

                system("pause");
                mainMenu(prices, seats);

            // Displays the seats for review
            case 2:
                reviewOrder(prices, seats, total, chosen);

            // Returns to main menu
            case 3:
                mainMenu(prices,seats);

        }
        validate(choice);
    } while(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Self Explanatory
void savePrices(double prices[ROWS])
{
    ofstream saveFile;
    saveFile.open("Theater_Prices.txt");
    for (int i=0; i < ROWS; i++)
    {
        saveFile << prices[i] << endl;
    }

    saveFile.close();
}

// Self Explanatory
void saveSeats(char seats [][COLS])
{
    ofstream saveFile;
    saveFile.open("Theater_Seats.txt");

    for (int r=0; r<ROWS; r++)
    {
        for (int c=0; c<COLS;c++)
        {
            saveFile << seats [r][c];
        }

    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function is used to load the seats and prices text files
int loadSavedInfo(double prices[ROWS], char seats[][COLS])
{
    ifstream loadFile;
    loadFile.open("Theater_Prices.txt");

    if(loadFile.is_open())
    {
        for (int i=0; i < ROWS; i++)
        {
            loadFile >> prices[i];
        }
    }

    else
        return 0;

    loadFile.close();


    loadFile.open("Theater_Seats.txt");
    if(loadFile.is_open())
    {
        for (int r=0; r<ROWS; r++)
        {
            for (int c=0; c<COLS;c++)
            {
                loadFile >> seats [r][c];
            }
        }
    }
    else
        return 0;
    loadFile.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void validate(int input)
{
    while (!(cin >> input))
    {
        cout << "A valid number must be entered: ";
        cin.clear();
        cin.ignore();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reviewOrder(double prices[ROWS], char seats[][COLS], double total, int chosen[][COLS])
{
    compareSeats(prices, seats, chosen, 0);

    Checkout(prices, seats, total, chosen);

}

// Compares seats and change the status of the seat if purchased
void compareSeats(double prices[ROWS], char seats[][COLS], int chosen[][COLS], int purchased)
{

    //Checks for bought seats
    if (purchased == 0)
    {
        cout << endl <<"Your seats are in: " << endl;
        for(int r=0; r<ROWS;r++)
        {
            for(int c=0; c<COLS; c++)
            {
                if(seats[r][c] == chosen[r][c])
                cout << "Row " << r+1 << ", Column " << c+1 << "." << endl;
            }
        }
        displaySeats(prices, seats, -1);
    }

    else
        for(int r=0; r<ROWS;r++)
        {
            for(int c=0; c<COLS; c++)
            {
                if(seats[r][c] == chosen[r][c])
                seats[r][c] = '*';
            }
        }

    saveSeats(seats);
}

// Colors the text when called
void textcolor(int color)
{
    // Calls the object HANDLE and it gets set to the output
    HANDLE handle;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);

    //
    SetConsoleTextAttribute(handle, color);
}

void TicketPrices(double prices [ROWS], char seats[][COLS])
{
//    double prices[15];
    int value = 3;

    ifstream openfile;
    openfile.open("Theater_Prices.txt");
    int num;
    //double prices[ROWS];

    for(int count = 0; count < ROWS; count++)
    {
        cout << "Row " << (count + 1) << " tickets price: ";
             openfile >> prices[count];
        cout << prices[count] << endl;
    }

    cout << endl;

    openfile.close();

    system ("pause");
    if (value == 3);
    mainMenu(prices, seats);

}


#include "FEHLCD.h"
#include "FEHUtility.h"
#include "FEHImages.h"
#include "FEHRandom.h"
#include <string.h>
#include <time.h>
/*Houses the userFlip and RandomizeCard functions. The private variables are string
variables that will house the names of the flower image files (the randomization
function
does this). These strings are used in both of the class's functions. The public
variables
are used in the userFlip function and are in the class so they can be called in the
function for the statistics.*/
class Card {
private:
char card_image1[30], card_image2[30], card_image3[30], card_image4[30],
card_image5[30];
char card_image6[30], card_image7[30], card_image8[30], card_image9[30],
card_image10[30], card_image11[30];
char card_image12[30], card_image13[30], card_image14[30],
card_image15[30], card_image16[30], card_image17[30];
char card_image18[30], card_image19[30], card_image20[30],
card_image21[30], card_image22[30], card_image23[30];
char card_image24[30];
public:
int press_counter = 0, match = 0, elapsed_time = 0;
void userFlip(Card Cards);
void RandomizeCard(void);
};
void Menu(Card Cards);
int main() {
//Creates the Title Page
//create first background image
FEHImage background;
background.Open("background_game1.png");
background.Draw(0,0);
//Creates title
LCD.SetFontColor(DARKGREEN);
LCD.WriteAt("Memory Match", 85, 100);
//Creates touch to start text
LCD.SetFontColor(LIGHTGRAY);
LCD.WriteAt("Touch to Start", 75, 140);
LCD.Update(); //Updates screen
//opens up menu when touched anywhere
int x, y;
while (!LCD.Touch(&x, &y)) {};
while (LCD.Touch(&x, &y)) {};
Card Cards; //Creates an instance of the object
Menu(Cards); //Calls the menu function
while (1)
LCD.Update();
return 0;
}
/*Avi Maloo ~ The menu function creates the Main Menu and allows the user to
select a play, statistics, instructions, and credits button. The play button opens
all the necessary functions to play the game. The stats button shows the statistics
from the
previous game. The instructions button shows the simple instuctions.
The credits buttons displays the creators. Requires a Card object so that the stats
can
be properly updated.*/
void Menu(Card Cards)
{
//Opens up fresh background
LCD.Clear(); //Clears old background
FEHImage background;
background.Open("background_game1.png");
background.Draw(0,0);
//creates Icons that the user can select
FEHIcon:: Icon Play, Stats, Instructions, Credits, X, X1;
//creates play button
LCD.SetFontColor(LIGHTGRAY);
LCD.FillRectangle(123, 40, 70, 35);
Play.SetProperties("Play", 123, 40, 70, 35, LIGHTGRAY, DARKGREEN);
Play.Draw();
//creates stats button
LCD.SetFontColor(LIGHTGRAY);
LCD.FillRectangle(85, 80, 150, 35);
Stats.SetProperties("Statistics", 85, 80, 150, 35, LIGHTGRAY, DARKGREEN);
Stats.Draw();
//creates Instructions button
LCD.SetFontColor(LIGHTGRAY);
LCD.FillRectangle(75, 120, 170, 35);
Instructions.SetProperties("Instructions", 75, 120, 170, 35, LIGHTGRAY,
DARKGREEN);
Instructions.Draw();
//creates Credits button
LCD.SetFontColor(LIGHTGRAY);
LCD.FillRectangle(95, 160, 130, 35);
Credits.SetProperties("Credits", 95, 160, 130, 35, LIGHTGRAY, DARKGREEN);
Credits.Draw();
LCD.Update(); //Updates the screen
//checks
float a, b;
while (!LCD.Touch(&a, &b)) {};
while (LCD.Touch(&a, &b)) {};
while(true) {
//check if the play button is pressed
if (Play.Pressed(a,b,0)) {
//Clear old background and opens new one
LCD.Clear();
FEHImage background_2;
background_2.Open("background_2.png");
background_2.Draw(0,0);
//Creates game
Cards.RandomizeCard (); //Calls randomization function
LCD.Update();
Cards.userFlip (Cards); //calls the user flip function
}
//check if the Stats button is pressed
if (Stats.Pressed(a,b,0)) {
//Clear old background and open new one
LCD.Clear();
background.Open("background_3.png");
background.Draw(0,0);
//write Stats (shows time taken and amount of moves made)
LCD.SetFontColor(DARKGREEN);
LCD.WriteAt("Player Statistics", 60, 30);
LCD.WriteAt("Time Taken:", 10, 70 );
LCD.WriteAt(Cards.elapsed_time, 200,70);
LCD.WriteAt("s", 250, 70);
LCD.WriteAt("Moves Made:", 10, 120 );
LCD.WriteAt(Cards.press_counter/2, 200,120);
//return button
X1.SetProperties("X", 295,10, 20, 20, WHITE, DIMGRAY);
X1.Draw();
LCD.Update();
}
//check if the instructions button is pressed
if (Instructions.Pressed(a,b,0)) {
//open fresh background
LCD.Clear();
background.Open("background_3.png");
background.Draw(0,0);
//write instructions
LCD.SetFontColor(DARKGREEN);
LCD.WriteAt("Instructions", 80, 20);
LCD.WriteAt("Pick two cards!", 10, 50);
LCD.WriteAt("Match? They stay face up!", 10, 80 );
LCD.WriteAt("No match? They're flipped.", 10, 110 );
LCD.WriteAt("Can you match them all?", 10, 140);
//return button
X1.SetProperties("X", 295,10, 20, 20, WHITE, DIMGRAY);
X1.Draw();
LCD.Update();
}
//check if the Credits button is pressed
if (Credits.Pressed(a,b,0)){
//open fresh background
LCD.Clear();
background.Open("background_3.png");
background.Draw(0,0);
//write the credits to the screen
LCD.SetFontColor(DARKGREEN);
LCD.WriteAt("Creators:", 100, 70);
LCD.WriteAt("Avi Maloo", 100, 100);
LCD.WriteAt("&", 145, 120 );
LCD.WriteAt("Malia Weatherbie", 60, 140 );
//return button
X1.SetProperties("X", 295,10, 20, 20, WHITE, DIMGRAY);
X1.Draw();
LCD.Update();
}
float c, d;
while (!LCD.Touch(&c, &d)) {};
while (LCD.Touch(&c, &d)) {};
while(true) {
if (X1.Pressed(c,d,0))
{
LCD.Clear();
Menu(Cards);
LCD.Update();
}
}
}
}
/*Malia Weatherbie ~ The randomize card function randomizes the placement of the
cards
on the board. It does so by randomly generating a number from 0-11. Based on the
number, a string (corresponding to an image file) will be copied into a dummy
variable and it will update times_through. Based on the times_through, will
determine
which card image number the card image string will be copied in to. The multiple a
values simply ensure only two instances of the card will occur.*/
void Card :: RandomizeCard ()
{
//declare variables
int randNum, times_through = 0, a = 0, a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0;
int a6 = 0, a7 = 0, a8 = 0, a9 = 0, a10 = 0, a11 = 0;
char card_image[30];
FEHImage card; //creates card image
while (times_through < 24) {
randNum = Random.RandInt() % 12; //Returns a random int between 0-11
//deterimes which string to copy into card_image
if (randNum == 0 && a < 2) {
a++;
times_through++;
strcpy(card_image, "small_yellow.png");
}
else if (randNum == 1 && a1 < 2) {
a1++;
times_through++;
strcpy(card_image, "small_red.png");
}
else if (randNum == 2 && a2 < 2) {
a2++;
times_through++;
strcpy(card_image, "pink_weird.png");
}
else if (randNum == 3 && a3 < 2) {
a3++;
times_through++;
strcpy(card_image, "orange_string.png");
}
else if (randNum == 4 && a4 < 2) {
a4++;
times_through++;
strcpy(card_image, "dark_blue.png");
}
else if (randNum == 5 && a5 < 2) {
a5++;
times_through++;
strcpy(card_image, "blue_thorn.png");
}
else if (randNum == 6 && a6 < 2) {
a6++;
times_through++;
strcpy(card_image, "blue_spread_out.png");
}
else if (randNum == 7 && a7 < 2) {
a7++;
times_through++;
strcpy(card_image, "cornflower.png");
}
else if (randNum == 8 && a8 < 2) {
a8++;
times_through++;
strcpy(card_image, "orange_tulip.png");
}
else if (randNum == 9 && a9 < 2) {
a9++;
times_through++;
strcpy(card_image, "pink_circular.png");
}
else if (randNum == 10 && a10 < 2) {
a10++;
times_through++;
strcpy(card_image, "purple_circular.png");
}
else if (randNum == 11 && a11 < 2) {
a11++;
times_through++;
strcpy(card_image, "yellow_circular.png");
}
//determines where the card will be placed based on the times_through
switch (times_through) {
case 1:
strcpy(card_image12, card_image);
case 2:
strcpy(card_image16, card_image);
case 3:
strcpy(card_image1, card_image);
case 4:
strcpy(card_image13, card_image);
case 5:
strcpy(card_image21, card_image);
case 6:
strcpy(card_image15, card_image);
case 7:
strcpy(card_image6, card_image);
case 8:
strcpy(card_image18, card_image);
case 9:
strcpy(card_image9, card_image);
case 10:
strcpy(card_image22, card_image);
case 11:
strcpy(card_image11, card_image);
case 12:
strcpy(card_image4, card_image);
case 13:
strcpy(card_image7, card_image);
case 14:
strcpy(card_image17, card_image);
case 15:
strcpy(card_image3, card_image);
case 16:
strcpy(card_image23, card_image);
case 17:
strcpy(card_image8, card_image);
case 18:
strcpy(card_image10, card_image);
case 19:
strcpy(card_image5, card_image);
case 20:
strcpy(card_image20, card_image);
case 21:
strcpy(card_image24, card_image);
case 22:
strcpy(card_image2, card_image);
case 23:
strcpy(card_image19, card_image);
case 24:
strcpy(card_image14, card_image);
}
}
FEHImage card_back;
int i;
//uses for loops to create the backs of each of the cards
for (i = 0; i < 6; i++) {
card_back.Open("card_back.png");
card_back.Draw ((50*i + 10), 20);
}
for (i = 0; i < 6; i++) {
card_back.Open("card_back.png");
card_back.Draw ((50*i + 10), 75);
}
for (i = 0; i < 6; i++) {
card_back.Open("card_back.png");
card_back.Draw ((50*i + 10), 130);
}
for (i = 0; i < 6; i++) {
card_back.Open("card_back.png");
card_back.Draw ((50*i + 10), 185);
}
LCD.Update(); //Updates the screen
}
/*Avi Maloo and Malia Weatherbie ~ Creates the icons that allow the user to click
the cards.
It keeps track of the amount of moves made and the time taken to match all the
cards.
It only allows for two cards to be flipped at once, and it ensures double clicking
a card
does not count as a match. If the cards match, they remain face up. If the cards
dont match,
the reamin face up for 1.5 s then flip back over. Once 12 matches are made, the
timer ends and
a winning screen opens! Input an instance of a Card object to make sure certain
stats are
able to update*/
void Card::userFlip(Card Cards)
{
//declare variables and intialize so each time a new game is open they
start at 0.
char string1[30];
int x_pos, y_pos, counter = 0;
Cards.match = 0;
Cards.press_counter = 0;
Cards.elapsed_time = 0;
int startTime = time(NULL);
FEHImage myCard; //makes image for the cards that will be created when
flipped/reflipped.
//create the buttons for each of the cards
FEHIcon:: Icon A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T,
U, V, W, X, Y;
A.SetProperties(" ", 12, 22, 40, 45, WHITE, WHITE);
A.Draw();
B.SetProperties(" ", 62, 22, 40, 45, WHITE, WHITE);
B.Draw();
C.SetProperties(" ", 112, 22, 40, 45, WHITE, WHITE);
C.Draw();
D.SetProperties(" ", 162, 22, 40, 45, WHITE, WHITE);
D.Draw();
E.SetProperties(" ", 212, 22, 40, 45, WHITE, WHITE);
E.Draw();
F.SetProperties(" ", 262, 22, 40, 45, WHITE, WHITE);
F.Draw();
G.SetProperties(" ", 12, 77, 40, 45, WHITE, WHITE);
G.Draw();
H.SetProperties(" ", 62, 77, 40, 45, WHITE, WHITE);
H.Draw();
I.SetProperties(" ", 112, 77, 40, 45, WHITE, WHITE);
I.Draw();
J.SetProperties(" ", 162, 77, 40, 45, WHITE, WHITE);
J.Draw();
K.SetProperties(" ", 212, 77, 40, 45, WHITE, WHITE);
K.Draw();
L.SetProperties(" ", 262, 77, 40, 45, WHITE, WHITE);
L.Draw();
M.SetProperties(" ", 12, 132, 40, 45, WHITE, WHITE);
M.Draw();
N.SetProperties(" ", 62, 132, 40, 45, WHITE, WHITE);
N.Draw();
O.SetProperties(" ", 112, 132, 40, 45, WHITE, WHITE);
O.Draw();
P.SetProperties(" ", 162, 132, 40, 45, WHITE, WHITE);
P.Draw();
Q.SetProperties(" ", 212, 132, 40, 45, WHITE, WHITE);
Q.Draw();
R.SetProperties(" ", 262, 132, 40, 45, WHITE, WHITE);
R.Draw();
S.SetProperties(" ", 12, 187, 40, 45, WHITE, WHITE);
S.Draw();
T.SetProperties("", 62, 187, 40, 45, WHITE, WHITE);
T.Draw();
U.SetProperties(" ", 112,187, 40, 45, WHITE, WHITE);
U.Draw();
V.SetProperties(" ", 162, 187, 40, 45, WHITE, WHITE);
V.Draw();
W.SetProperties(" ", 212, 187, 40, 45, WHITE, WHITE);
W.Draw();
Y.SetProperties(" ", 262, 187, 40, 45, WHITE, WHITE);
Y.Draw();
//Return button creation
X.SetProperties("X", 302, 4, 17, 17, SIENNA, DIMGRAY);
X.Draw();
LCD.Update(); //update the screen
//Checks which cards is pressed.
float a, b;
while(true)
{
counter = 0; //reinitalizes counter to 0
while(counter < 2) { //ensures only 2 cards can be clicked at a time
while (!LCD.Touch(&a, &b)) {};
while (LCD.Touch(&a, &b)) {};
//check if first card is pressed
if (A.Pressed(a,b,0))
{
myCard.Open(card_image1); //Opens/Draws the image of the card pressed
myCard.Draw(10,20);
Cards.press_counter++; //Records overall how many times the cards are
touched
counter++; //records when a card is touched
//check for match after two cards have been selected
if (counter == 2) {
//ensures double clicking a card does not count as a match
if (strcmp(string1, card_image1) == 0 && (x_pos != 10 || y_pos != 20))
{
Cards.match++; //if match, adds one to match counter and card stays
face up
}
else {
Sleep(1.5); //if no match, card stays face up for 1.5 seconds
myCard.Open("card_back.png"); //then both cards are flipped back
over
myCard.Draw(10,20);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image1), x_pos = 10, y_pos = 20;
}
//check if 2nd card is pressed
if (B.Pressed(a,b,0)) {
myCard.Open(card_image2);
myCard.Draw(60,20);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image2) == 0 && (x_pos != 60 || y_pos != 20))
{
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(60,20);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image2), x_pos = 60, y_pos = 20;
}
//check if 3rd card is pressed
if (C.Pressed(a,b,0)) {
myCard.Open(card_image3);
myCard.Draw(110,20);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image3) == 0 && (x_pos != 110 || y_pos != 20))
{
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(110,20);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image3), x_pos = 110, y_pos = 20;
}
//check if 4th card is pressed
if (D.Pressed(a,b,0)) {
myCard.Open(card_image4);
myCard.Draw(160,20);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image4) == 0 && (x_pos != 160 || y_pos != 20))
{
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(160,20);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image4), x_pos = 160, y_pos = 20;
}
//check if 5th card is pressed
if (E.Pressed(a,b,0)) {
myCard.Open(card_image5);
myCard.Draw(210,20);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image5) == 0 && (x_pos != 210 || y_pos != 20))
{
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(210,20);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image5), x_pos = 210, y_pos = 20;
}
//check if 6th card is pressed
if (F.Pressed(a,b,0)) {
myCard.Open(card_image6);
myCard.Draw(260,20);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image6) == 0 && (x_pos != 260 || y_pos != 20))
{
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(260,20);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image6), x_pos = 260, y_pos = 20;
}
//check if 7th card is pressed
if (G.Pressed(a,b,0)) {
myCard.Open(card_image7);
myCard.Draw(10,75);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image7) == 0 && (x_pos != 10 || y_pos != 75))
{
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(10,75);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image7), x_pos = 10, y_pos = 75;
}
//check if 8th card is pressed
if (H.Pressed(a,b,0)) {
myCard.Open(card_image8);
myCard.Draw(60,75);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image8) == 0 && (x_pos != 60 || y_pos != 75))
{
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(60,75);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image8), x_pos = 60, y_pos = 75;
}
//check if 9th card is pressed
if (I.Pressed(a,b,0)) {
myCard.Open(card_image9);
myCard.Draw(110,75);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image9) == 0 && (x_pos != 110 || y_pos != 75))
{
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(110,75);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image9), x_pos = 110, y_pos = 75;
}
//check if 10th card is pressed
if (J.Pressed(a,b,0))
{
myCard.Open(card_image10);
myCard.Draw(160,75);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image10) == 0 && (x_pos != 160 || y_pos !=
75)) {
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(160,75);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image10), x_pos = 160, y_pos = 75;
}
//check if 11th card is pressed
if (K.Pressed(a,b,0)) {
myCard.Open(card_image11);
myCard.Draw(210,75);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image11) == 0 && (x_pos != 210 || y_pos !=
75)) {
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(210,75);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image11), x_pos = 210, y_pos = 75;
}
//check if 12th card is pressed
if (L.Pressed(a,b,0)) {
myCard.Open(card_image12);
myCard.Draw(260,75);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image12) == 0 && (x_pos != 260 || y_pos !=
75)) {
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(260,75);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image12), x_pos = 260, y_pos = 75;
}
//check if 13th card is pressed
if (M.Pressed(a,b,0)) {
myCard.Open(card_image13);
myCard.Draw(10,130);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image13) == 0 && (x_pos != 10 || y_pos !=
130)) {
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(10,130);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image13), x_pos = 10, y_pos = 130;
}
//check if 14th card is pressed
if (N.Pressed(a,b,0)) {
myCard.Open(card_image14);
myCard.Draw(60,130);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image14) == 0 && (x_pos != 60 || y_pos !=
130)) {
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(60,130);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image14), x_pos = 60, y_pos = 130;
}
//check if 15th card is pressed
if (O.Pressed(a,b,0)) {
myCard.Open(card_image15);
myCard.Draw(110,130);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image15) == 0 && (x_pos != 110 || y_pos !=
130)) {
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(110,130);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image15), x_pos = 110, y_pos = 130;
}
//check if 16th card is pressed
if (P.Pressed(a,b,0)) {
myCard.Open(card_image16);
myCard.Draw(160,130);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image16) == 0 && (x_pos != 160 || y_pos !=
130)) {
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(160,130);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image16), x_pos = 160, y_pos = 130;
}
//check if 17th card is pressed
if (Q.Pressed(a,b,0)) {
myCard.Open(card_image17);
myCard.Draw(210,130);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image17) == 0 && (x_pos != 210 || y_pos !=
130)) {
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(210,130);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image17), x_pos = 210, y_pos = 130;
}
//check if 18th card is pressed
if (R.Pressed(a,b,0)) {
myCard.Open(card_image18);
myCard.Draw(260,130);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image18) == 0 && (x_pos != 260 || y_pos !=
130)) {
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(260,130);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image18), x_pos = 260, y_pos = 130;
}
//check if 19th card is pressed
if (S.Pressed(a,b,0)) {
myCard.Open(card_image19);
myCard.Draw(10,185);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image19) == 0 && (x_pos != 10 || y_pos !=
185)) {
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(10,185);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image19), x_pos = 10, y_pos = 185;
}
//check if 20th card is pressed
if (T.Pressed(a,b,0)) {
myCard.Open(card_image20);
myCard.Draw(60,185);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image20) == 0 && (x_pos != 60 || y_pos !=
185)) {
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(60,185);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image20), x_pos = 60, y_pos = 185;
}
//check if 21st card is pressed
if (U.Pressed(a,b,0)) {
myCard.Open(card_image21);
myCard.Draw(110,185);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image21) == 0 && (x_pos != 110 || y_pos !=
185)) {
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(110,185);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image21), x_pos = 110, y_pos = 185;
}
//check if 22nd card is pressed
if (V.Pressed(a,b,0)) {
myCard.Open(card_image22);
myCard.Draw(160,185);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image22) == 0 && (x_pos != 160 || y_pos !=
185)) {
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(160,185);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image22), x_pos = 160, y_pos = 185;
}
//check if 23rd card is pressed
if (W.Pressed(a,b,0)) {
myCard.Open(card_image23);
myCard.Draw(210,185);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image23) == 0 && (x_pos != 210 || y_pos !=
185)) {
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(210,185);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image23), x_pos = 210, y_pos = 185;
}
//check if 24th card is pressed
if (Y.Pressed(a,b,0)) {
myCard.Open(card_image24);
myCard.Draw(260,185);
Cards.press_counter++;
counter++;
//check for match
if (counter == 2) {
if (strcmp(string1, card_image24) == 0 && (x_pos != 260 || y_pos !=
185)) {
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(260,185);
myCard.Open("card_back.png");
myCard.Draw(x_pos, y_pos);
}
}
//copy its variables for comparison
strcpy(string1, card_image24), x_pos = 260, y_pos = 185;
}
//check if return button is pushed
if (X.Pressed(a,b,0)) {
LCD.Clear();
Menu(Cards); //Return to Menu
LCD.Update();
}
if (Cards.match == 12) {
//find elapsed time
int endTime = time(NULL); //Time once all cards are matched
Cards.elapsed_time = endTime - startTime;
Sleep(1.5); //Keep all the matches open for 1.5s
//open images
FEHImage backgroundWin;
FEHImage sunWin;
FEHImage wormWin;
//the starting x and y values for the sun and worm
int xpos = 310;
int ypos = 10;
int xpos2 = 10;
int ypos2 = 150;
//updating x and y postions of sun and worm to make them look like
moving
while (xpos >= 70 && xpos2 <=250) {
xpos = xpos - 5;
xpos2 = xpos2 + 5;
backgroundWin.Open("backgroundWin.png");
backgroundWin.Draw(0,0);
sunWin.Open("sunWin.png"); //open sun at new x-y pos
sunWin.Draw(xpos,ypos);
wormWin.Open("wormWin.png"); //open worm at new x-y pos
wormWin.Draw(xpos2, ypos2);
Sleep(0.1);
LCD.Clear(); //clear the screen
}
LCD.Clear(); //clear the screen
backgroundWin.Open("backgroundWin.png");
backgroundWin.Draw(0,0);
LCD.SetFontColor(DARKGREEN);
LCD.WriteAt("You Matched", 100, 100);
LCD.WriteAt("Them All!", 110, 130);
//Return button creation
X.SetProperties("X", 302, 4, 17, 17, SIENNA, DIMGRAY);
X.Draw();
LCD.Update();
}
}
}
}
/*void Card::userFlip(Card Cards)
{
//Delcare variables
Cards.match = 0;
Cards.press_counter = 0;
Cards.elapsed_time = 0;
int startTime = time(NULL);
//create the buttons for each of the cards
A.SetProperties(" ", 12, 22, 40, 45, WHITE, WHITE);
A.Draw();
B.SetProperties(" ", 62, 22, 40, 45, WHITE, WHITE);
B.Draw();
C.SetProperties(" ", 112, 22, 40, 45, WHITE, WHITE);
C.Draw();
D.SetProperties(" ", 162, 22, 40, 45, WHITE, WHITE);
D.Draw();
E.SetProperties(" ", 212, 22, 40, 45, WHITE, WHITE);
E.Draw();
F.SetProperties(" ", 262, 22, 40, 45, WHITE, WHITE);
F.Draw();
G.SetProperties(" ", 12, 77, 40, 45, WHITE, WHITE);
G.Draw();
H.SetProperties(" ", 62, 77, 40, 45, WHITE, WHITE);
H.Draw();
I.SetProperties(" ", 112, 77, 40, 45, WHITE, WHITE);
I.Draw();
J.SetProperties(" ", 162, 77, 40, 45, WHITE, WHITE);
J.Draw();
K.SetProperties(" ", 212, 77, 40, 45, WHITE, WHITE);
K.Draw();
L.SetProperties(" ", 262, 77, 40, 45, WHITE, WHITE);
L.Draw();
M.SetProperties(" ", 12, 132, 40, 45, WHITE, WHITE);
M.Draw();
N.SetProperties(" ", 62, 132, 40, 45, WHITE, WHITE);
N.Draw();
O.SetProperties(" ", 112, 132, 40, 45, WHITE, WHITE);
O.Draw();
P.SetProperties(" ", 162, 132, 40, 45, WHITE, WHITE);
P.Draw();
Q.SetProperties(" ", 212, 132, 40, 45, WHITE, WHITE);
Q.Draw();
R.SetProperties(" ", 262, 132, 40, 45, WHITE, WHITE);
R.Draw();
S.SetProperties(" ", 12, 187, 40, 45, WHITE, WHITE);
S.Draw();
T.SetProperties("", 62, 187, 40, 45, WHITE, WHITE);
T.Draw();
U.SetProperties(" ", 112,187, 40, 45, WHITE, WHITE);
U.Draw();
V.SetProperties(" ", 162, 187, 40, 45, WHITE, WHITE);
V.Draw();
W.SetProperties(" ", 212, 187, 40, 45, WHITE, WHITE);
W.Draw();
Y.SetProperties(" ", 262, 187, 40, 45, WHITE, WHITE);
Y.Draw();
//Return button creation
X.SetProperties("X", 302, 4, 17, 17, SIENNA, DIMGRAY);
X.Draw();
LCD.Update();
float a, b;
while(true)
{
Cards.counter = 0;
while(Cards.counter < 2)
{
while (!LCD.Touch(&a, &b)) {};
while (LCD.Touch(&a, &b)) {};
//check if first card is pressed
if (A.Pressed(a,b,0))
{
myCard.Open(card_image1);
myCard.Draw(10,20);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image1, 10, 20);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image1);
Cards.x_pos = 10;
Cards.y_pos = 20;
}
//check if 2nd card is pressed
if (B.Pressed(a,b,0))
{
myCard.Open(card_image2);
myCard.Draw(60,20);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image2, 60, 20);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image2);
Cards.x_pos = 60;
Cards.y_pos = 20;
}
//check if 3rd card is pressed
if (C.Pressed(a,b,0))
{
myCard.Open(card_image3);
myCard.Draw(110,20);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image3, 110, 20);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image3);
Cards.x_pos = 110;
Cards.y_pos = 20;
}
//check if 4th card is pressed
if (D.Pressed(a,b,0))
{
myCard.Open(card_image4);
myCard.Draw(160,20);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image4, 160, 20);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image4);
Cards.x_pos = 160;
Cards.y_pos = 20;
}
//check if 5th card is pressed
if (E.Pressed(a,b,0))
{
myCard.Open(card_image5);
myCard.Draw(210,20);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image5, 210, 20);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image5);
Cards.x_pos = 210;
Cards.y_pos = 20;
}
//check if 6th card is pressed
if (F.Pressed(a,b,0))
{
myCard.Open(card_image6);
myCard.Draw(260,20);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image6, 260, 20);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image6);
Cards.x_pos = 260;
Cards.y_pos = 20;
}
//check if 7th card is pressed
if (G.Pressed(a,b,0))
{
myCard.Open(card_image7);
myCard.Draw(10,75);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image7, 10, 75);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image7);
Cards.x_pos = 10;
Cards.y_pos = 75;
}
//check if 8th card is pressed
if (H.Pressed(a,b,0))
{
myCard.Open(card_image8);
myCard.Draw(60,75);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image8, 60, 75);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image8);
Cards.x_pos = 60;
Cards.y_pos = 75;
}
//check if 9th card is pressed
if (I.Pressed(a,b,0))
{
myCard.Open(card_image9);
myCard.Draw(110,75);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image9, 110, 75);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image9);
Cards.x_pos = 110;
Cards.y_pos = 75;
}
//check if 10th card is pressed
if (J.Pressed(a,b,0))
{
myCard.Open(card_image10);
myCard.Draw(160,75);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image10, 160, 75);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image10);
Cards.x_pos = 160;
Cards.y_pos = 75;
}
//check if 11th card is pressed
if (K.Pressed(a,b,0))
{
myCard.Open(card_image11);
myCard.Draw(210,75);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image11, 210, 75);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image11);
Cards.x_pos = 210;
Cards.y_pos = 75;
}
//check if 12th card is pressed
if (L.Pressed(a,b,0))
{
myCard.Open(card_image12);
myCard.Draw(260,75);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image12, 260, 75);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image12);
Cards.x_pos = 260;
Cards.y_pos = 75;
}
//check if 13th card is pressed
if (M.Pressed(a,b,0))
{
myCard.Open(card_image13);
myCard.Draw(10,130);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image13, 10, 130);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image13);
Cards.x_pos = 10;
Cards.y_pos = 130;
}
//check if 14th card is pressed
if (N.Pressed(a,b,0))
{
myCard.Open(card_image14);
myCard.Draw(60,130);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image14, 60, 130);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image14);
Cards.x_pos = 60;
Cards.y_pos = 130;
}
//check if 15th card is pressed
if (O.Pressed(a,b,0))
{
myCard.Open(card_image15);
myCard.Draw(110,130);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image15, 110, 130);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image15);
Cards.x_pos = 110;
Cards.y_pos = 130;
}
//check if 16th card is pressed
if (P.Pressed(a,b,0))
{
myCard.Open(card_image16);
myCard.Draw(160,130);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image16, 160, 130);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image16);
Cards.x_pos = 160;
Cards.y_pos = 130;
}
//check if 17th card is pressed
if (Q.Pressed(a,b,0))
{
myCard.Open(card_image17);
myCard.Draw(210,130);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image17, 210, 130);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image17);
Cards.x_pos = 210;
Cards.y_pos = 130;
}
//check if 18th card is pressed
if (R.Pressed(a,b,0))
{
myCard.Open(card_image18);
myCard.Draw(260,130);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image18, 260, 130);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image18);
Cards.x_pos = 260;
Cards.y_pos = 130;
}
//check if 19th card is pressed
if (S.Pressed(a,b,0))
{
myCard.Open(card_image19);
myCard.Draw(10,185);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image19, 10, 185);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image19);
Cards.x_pos = 10;
Cards.y_pos = 185;
}
//check if 20th card is pressed
if (T.Pressed(a,b,0))
{
myCard.Open(card_image20);
myCard.Draw(60,185);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image20, 60, 185);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image20);
Cards.x_pos = 60;
Cards.y_pos = 185;
}
//check if 21st card is pressed
if (U.Pressed(a,b,0))
{
myCard.Open(card_image21);
myCard.Draw(110,185);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image21, 110, 185);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image21);
Cards.x_pos = 110;
Cards.y_pos = 185;
}
//check if 22nd card is pressed
if (V.Pressed(a,b,0))
{
myCard.Open(card_image22);
myCard.Draw(160,185);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image22, 160, 185);
//copy its variables into dummy variables for comparison
strcpy(Cards.string1, card_image22);
Cards.x_pos = 160;
Cards.y_pos = 185;
}
//check if 23rd card is pressed
if (W.Pressed(a,b,0))
{
myCard.Open(card_image23);
myCard.Draw(210,185);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image23, 210, 185);
//copy its variables for comparison
strcpy(Cards.string1, card_image23);
Cards.x_pos = 210;
Cards.y_pos = 185;
}
//check if 24th card is pressed
if (Y.Pressed(a,b,0)){
myCard.Open(card_image24);
myCard.Draw(260,185);
Cards.press_counter++;
Cards.counter++;
Cards.Match(Cards, card_image24, 260, 185);
//copy its variables for comparison
strcpy(Cards.string1, card_image24);
Cards.x_pos = 260;
Cards.y_pos = 185;
}
if (X.Pressed(a,b,0)) {
LCD.Clear();
LCD.Update();
Menu(Cards);
LCD.Update();
}
if (Cards.match == 12) {
//find elapsed time
int endTime = time(NULL);
Cards.elapsed_time = endTime - startTime;
FEHImage backgroundWin;
int xpos = 300;
int ypos = 10;
backgroundWin.Open("backgroundWin.png");
backgroundWin.Draw(0,0);
FEHImage sunWin;
sunWin.Open("sunWin.png");
sunWin.Draw(xpos, ypos);
FEHImage wormWin;
while (xpos >= 150) {
xpos = xpos - 10;
sunWin.Draw(xpos,ypos);
Sleep(0.1);
}
int xpos2 = 30;
int ypos2 = 100;
wormWin.Open("wormWin.png");
wormWin.Draw(xpos2, ypos2);
while (xpos2 <= 250) {
xpos2 = xpos2 + 10;
wormWin.Draw(xpos2, ypos2);
Sleep(0.1);
}
LCD.Clear();
backgroundWin.Open("backgroundWin.png");
backgroundWin.Draw(0,0);
LCD.SetFontColor(DARKGREEN);
LCD.WriteAt("You Matched", 85, 100);
LCD.WriteAt("Them All!", 85, 130);
//Return button creation
X.SetProperties("X", 302, 4, 17, 17, SIENNA, DIMGRAY);
X.Draw();
LCD.Update();
}
}
}
}
void Card::Match(Card Cards, char *str, int c, int d)
{
if (Cards.counter == 2)
{
if (strcmp(Cards.string1, str) == 0 && (Cards.x_pos != c || Cards.y_pos
!= d)) {
Cards.match++;
}
else {
Sleep(1.5);
myCard.Open("card_back.png");
myCard.Draw(c,d);
myCard.Open("card_back.png");
myCard.Draw(Cards.x_pos, Cards.y_pos);
}
}
}*/

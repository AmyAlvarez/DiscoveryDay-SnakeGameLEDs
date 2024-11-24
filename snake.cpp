// pin assignments
const int rows[] = {2, 3, 4, 5}; // row pins
const int cols[] = {6, 7, 8, 9}; // column pins
const int upButton = 10; // up button pin
const int rightButton = 11; // right button pin

int snake[16][2];  // for the snake body, max size 16, storing (row, col) 
int snakeLength = 3;// initial snake length
int direction = 1; // 0=up, 1=right (default to right initially)
int foodRow, foodCol; // food position
bool gameOver = false;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);
  }
  pinMode(upButton, INPUT_PULLUP);// up button with pull-up resistor
  pinMode(rightButton, INPUT_PULLUP);// right button with pull-up resistor
  initializeGame();
}

void loop() {
  if (gameOver) {
    displayGameOver();
    return;
  }

  readInput();
  moveSnake();
  if (checkCollision()) {
    gameOver = true;
    return;
  }
  if (snake[0][0] == foodRow && snake[0][1] == foodCol) {
    snakeLength++;
    spawnFood();
  }
  displayGrid();
  delay(200); //adjust snake speed
}

// start game
void initializeGame() {
  snake[0][0] = 1; snake[0][1] = 1; //start snake position
  snake[1][0] = 1; snake[1][1] = 0;
  spawnFood();
}

// read input for direction
void readInput() {
  if (!digitalRead(upButton) && direction != 1) direction = 0; // up
  if (!digitalRead(rightButton) && direction != 0) direction = 1; //right
}

// move snake
void moveSnake() {
  for (int i = snakeLength - 1; i > 0; i--) {
    snake[i][0] = snake[i - 1][0];
    snake[i][1] = snake[i - 1][1];
  }
  if (direction == 0) snake[0][0]--; // move up
  if (direction == 1) snake[0][1]++; // move right
}

// check for collisions
bool checkCollision() {
  if (snake[0][0] < 0 || snake[0][0] >= 4 || snake[0][1] < 0 || snake[0][1] >= 4) return true; // wall collision
  for (int i = 1; i < snakeLength; i++) {
    if (snake[0][0] == snake[i][0] && snake[0][1] == snake[i][1]) return true; // self-collision (if the snake bumps into itself)
  }
  return false;
}

// spawn food
void spawnFood(){
  foodRow = random(0, screenSize);
  foodCol = random(0, screenSize);
}

// display the grid
void displayGrid(){
  //toggle all LEDS off
  for(int i=0; i<screenSize; i++)
    for(int j=0; j<screenSize; j++){
      SCREEN[i][j] = false;
    }

  // pull and disp the snake loc
  for(int i=0; i<snakeLength; i++){
    int sX = snake[i][0];//pull the x cord
    int sY = snake[i][1];//pull the y cord
    SCREEN[sX][sY] = true;
  }

  // pull and disp the food loc
  SCREEN[foodRow][foodCol] = true;
}

// display game over
void displayGameOver(){
  //toggle all LEDS off
  for(int i=0; i<screenSize; i++)
    for(int j=0; j<screenSize; j++){
      SCREEN[i][j] = false;
    }

  bool gameOverScreenG[6][6] = {//contains a G
    {1, 1, 1, 1, 0, 0},
    {1, 0, 0, 0, 0, 0},
    {1, 0, 1, 1, 0, 0},
    {1, 0, 0, 1, 0, 0},
    {1, 0, 0, 1, 0, 0},
    {1, 1, 1, 1, 0, 0}
  };

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Cell
{
  int index;    // 0 is the center cell, the next cells spiral outwards
  int richness; // 0 if the cell is unusable, 1-3 for usable cells
  int neigh0;   // the index of the neighbouring cell for each direction
  int neigh1;
  int neigh2;
  int neigh3;
  int neigh4;
  int neigh5;
};

struct Tree
{
  int cellIndex;  // location of this tree
  int size;       // size of this tree: 0-3
  bool isMine;    // 1 if this is your tree
  bool isDormant; // 1 if this tree is dormant
};

struct State
{
  int numberOfCells;
  vector<Cell> cells;
  int day;
  int nutrients;
  int sun;
  int score;
  int oppSun;
  int oppScore;
  bool oppIsWaiting;
  int numberOfTrees;
  vector<Tree> trees;
  int numberOfPossibleActions;
  vector<string> actions;
  int sunDirection;
};

void ReadCells(State *state)
{
  cin >> state->numberOfCells;
  cin.ignore();

  for (int i = 0; i < state->numberOfCells; i++)
  {
    Cell cell;
    cin >> cell.index >> cell.richness >> cell.neigh0 >> cell.neigh1 >> cell.neigh2 >> cell.neigh3 >> cell.neigh4 >> cell.neigh5;
    state->cells.push_back(cell);
    cin.ignore();
  }
}

void UpdateState(State *state)
{
  cin >> state->day;
  cin.ignore();
  cin >> state->nutrients;
  cin.ignore();
  cin >> state->sun >> state->score;
  cin.ignore();
  cin >> state->oppSun >> state->oppScore >> state->oppIsWaiting;
  cin.ignore();
  cin >> state->numberOfTrees;
  cin.ignore();
  state->trees.clear();
  for (int i = 0; i < state->numberOfTrees; i++)
  {
    Tree tree;
    cin >> tree.cellIndex >> tree.size >> tree.isMine >> tree.isDormant;
    state->trees.push_back(tree);
    cin.ignore();
  }
  cin >> state->numberOfPossibleActions;
  cin.ignore();
  state->actions.clear();
  for (int i = 0; i < state->numberOfPossibleActions; i++)
  {
    string possibleAction;
    getline(cin, possibleAction); // try printing something from here to start with
    state->actions.push_back(possibleAction);
  }
  state->sunDirection = state->day % 6;
}

main()
{
  State state = State();
  ReadCells(&state);

  // game loop
  while (1)
  {
    UpdateState(&state);

    for (auto &&i : state.actions)
    {
      cerr << i << endl;
    }

    cout << state.actions[1] << endl;
  }
}
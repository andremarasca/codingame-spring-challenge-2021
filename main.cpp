#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <iterator>

#define DEBUG(MSG) ((cerr << MSG << endl))

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

enum COMMAND
{
  SEED,
  GROW,
  COMPLETE,
  WAIT,
};

map<COMMAND, string> CommandToString = {
    {SEED, "SEED"},
    {GROW, "GROW"},
    {COMPLETE, "COMPLETE"},
    {WAIT, "WAIT"},
};

map<string, COMMAND> StringToCommand = {
    {"SEED", SEED},
    {"GROW", GROW},
    {"COMPLETE", COMPLETE},
    {"WAIT", WAIT},
};

struct Action
{
  string action = "";
  string command = CommandToString.at(WAIT);
  int index1 = -1;
  int index2 = -1;
  float points = 0.0f;

  void print() const;
  void init(string);
};

void Action::print() const
{
  cout << this->command;

  if (this->index1 >= 0)
    cout << " " << this->index1;

  if (this->index2 >= 0)
    cout << " " << this->index2;

  cout << endl;
};

void Action::init(string possibleAction)
{
  istringstream iss(possibleAction);
  vector<string> results((istream_iterator<string>(iss)),
                         istream_iterator<string>());

  this->action = possibleAction;

  this->command = results[0];

  if (results.size() > 1)
  {
    stringstream ss;
    ss << results[1];
    ss >> this->index1;
  }
  if (results.size() > 2)
  {
    stringstream ss;
    ss << results[2];
    ss >> this->index2;
  }
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
  vector<Action> actions;
  int sunDirection;

  void sortActions();
};

void State::sortActions()
{
  sort(
      this->actions.begin(), this->actions.end(), [](Action &a1, Action &a2) -> bool
      { return a1.points > a2.points; });
}

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
    Action action;
    action.init(possibleAction);
    state->actions.push_back(action);
  }
  state->sunDirection = state->day % 6;
}

void EvaluateActions(State *state)
{
  for (Action &a : state->actions)
  {
    switch (StringToCommand.at(a.command))
    {
    case COMMAND::SEED:
      a.points += 10 + (state->numberOfCells - a.index2);
      break;
    case COMMAND::GROW:
      a.points += 10 + (state->numberOfCells - a.index2) + (3 - state->trees[a.index1].size);
      break;
    case COMMAND::COMPLETE:
      a.points += 30 + (20 - state->sun) + ((state->oppScore > state->score) ? 200 : 0);
      break;
    default:
      a.points += -10;
      break;
    }
  }
}

int main()
{
  State state = State();
  ReadCells(&state);

  while (1)
  {
    UpdateState(&state);

    EvaluateActions(&state);

    state.sortActions();

    // for (auto i : state.actions)
    // {
    //   DEBUG(i.command);
    //   // DEBUG(i.index1);
    //   // DEBUG(i.index2);
    //   DEBUG(i.points);
    // }

    state.actions[0].print();
  }
}
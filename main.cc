#include <iostream>
#include <stdexcept>

using ::std::cout;
using ::std::endl;
using ::std::domain_error;

// How many games are we simulating, potentially?
const int GAMES_IN_SERIES = 7;

// What is the probability of the favorite winning a single game?
const double P_FAVORITE_WINNING = 0.55f;

// Enumeration representing the team.
enum class Team : int { None, Favorite, Underdog };

// Node represents the state of a particular outcome in the decision tree.
class Node {
 public:
  Node* parent = nullptr;
  Node* favorite_win = nullptr;
  Node* underdog_win = nullptr;
  double outcome_probability = 1.0f;
  Team game_winner = Team::None;
  Team series_winner = Team::None;
  int favorite_victories = 0;
  int underdog_victories = 0;
};

// Build the edecision tree (recursive helper).
void BuildTree(Node* parent, int wins_needed, double p_fave) {
  // If there was a series winner, stop recursing.

  if (parent->favorite_victories == wins_needed) {
    parent->series_winner = Team::Favorite;
    return;
  }

  else if (parent->underdog_victories == wins_needed) {
    parent->series_winner = Team::Underdog;
    return;
  }

  // Favorite wins
  Node* fave = new Node();
  fave->parent = parent;
  fave->outcome_probability = parent->outcome_probability * p_fave;
  fave->game_winner = Team::Favorite;
  fave->favorite_victories = parent->favorite_victories + 1;
  fave->underdog_victories = parent->underdog_victories;
  parent->favorite_win = fave;
  BuildTree(fave, wins_needed, p_fave);

  // Underdog wins
  Node* under = new Node();
  under->parent = parent;
  under->outcome_probability = parent->outcome_probability * (1.0f - p_fave);
  under->game_winner = Team::Underdog;
  under->favorite_victories = parent->favorite_victories;
  under->underdog_victories = parent->underdog_victories + 1;
  parent->underdog_win = under;
  BuildTree(under, wins_needed, p_fave);
}

// Build the decision tree.
Node* BuildTree(int games_in_series, double p_of_favorite_victory) {
  Node* root = new Node();
  BuildTree(root, (games_in_series + 1) / 2, p_of_favorite_victory);
  return root;
}

// Run stats (recursive helper)
void RunStatsRecurse(Node* node, double* p_fave, double* p_under) {
  if (!node) {
    return;
  }

  switch (node->series_winner) {
    case Team::Favorite:
      (*p_fave) += node->outcome_probability;
      return;
    case Team::Underdog:
      (*p_under) += node->outcome_probability;
      return;
    default:
      // Intentionally empty.
      break;
  }

  RunStatsRecurse(node->favorite_win, p_fave, p_under);
  RunStatsRecurse(node->underdog_win, p_fave, p_under);
}

void RunStats(Node* root) {
  double p_fave = 0.0f;
  double p_under = 0.0f;
  RunStatsRecurse(root, &p_fave, &p_under);
  cout << "P(favorite): " << p_fave << endl;
  cout << "P(underdog): " << p_under << endl;
}

int main(int argc, char* argv[]) {
  Node* node = BuildTree(GAMES_IN_SERIES, P_FAVORITE_WINNING);
  RunStats(node);
  return 0;
}

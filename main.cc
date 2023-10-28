#include <iostream>

// How many games are we simulating, potentially?
const int GAMES_IN_SERIES = 7;

enum class Team : int { None, Favorite, Underdog };

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

Node* BuildTree(int games_in_series, double p_of_favorite_victory) {
  Node* root = new Node();
  BuildTree(root, (games_in_series + 1) / 2, p_of_favorite_victory);
  return root;
}

void Stats(Node* root) {}

int main(int argc, char* argv[]) {
  Node* node = BuildTree(GAMES_IN_SERIES, 0.60f);
  Stats(node);
  return 0;
}

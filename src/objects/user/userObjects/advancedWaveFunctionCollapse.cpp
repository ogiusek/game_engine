#include <iostream>

#include <vector>
#include <functional>
#include <algorithm>

#include <ctime>
#include <cstdlib>

using namespace std;

class AWFCTile
{
private:
  class AWFCTileNeighbour
  {
  public:
    int value, chance;
    bool operator==(const int &other) { return other == value; }
    void operator=(int _value) { value = _value; }
    AWFCTileNeighbour(int _value, int _chance = 1) : value(value), chance(chance){};
  };

public:
  int id;
  // vector<int> allowedNeighbours;
  vector<AWFCTileNeighbour> allowedNeighbours;

  int getChance(int value)
  {
    for (AWFCTileNeighbour neighbour : allowedNeighbours)
      if (neighbour == value)
        return neighbour.chance;
    return 0;
  }

  bool Allows(int _id)
  {
    for (AWFCTileNeighbour allowed : allowedNeighbours)
      if (allowed == _id)
        return true;
    return false;
  }

  AWFCTile(int _id, vector<AWFCTileNeighbour> _allowedNeighbours)
      : id(_id), allowedNeighbours(_allowedNeighbours){};
  AWFCTile() {}
};

class AdvancedWaveFunctionCollapse
{
private:
  class UnCollapsedTile
  {
  public:
    int x, y;
    bool collapsed = false;
    vector<AWFCTile> tiles;
    bool Allows(AWFCTile tile)
    {
      for (AWFCTile existingTile : tiles)
        if (existingTile.Allows(tile.id))
          return true;
      return false;
    }
    void remove(AWFCTile tile)
    {
      for (int i = 0; i < tiles.size(); i++)
        if (tile.id == tiles[i].id)
        {
          tiles.erase(tiles.begin() + i);
          // return remove(tile);
          break;
        }
    }

    void Collapse()
    {
      tiles = {tiles[rand() % tiles.size()]};
      collapsed = true;
    }
    UnCollapsedTile(int _x, int _y, vector<AWFCTile> _tiles)
        : x(_x), y(_y), tiles(_tiles){};
  };
  int w, h;
  vector<AWFCTile> availableTiles;

  vector<vector<UnCollapsedTile>> unCollapsed;
  vector<vector<AWFCTile>> collapsed;

  bool isCollapsed()
  {
    for (vector<UnCollapsedTile> column : unCollapsed)
      for (UnCollapsedTile tile : column)
        if (!tile.collapsed)
          return false;
    return true;
  }

  UnCollapsedTile *getLowestEntropy()
  {
    UnCollapsedTile *lowestEntropyTile = nullptr;
    for (vector<UnCollapsedTile> &column : unCollapsed)
      for (UnCollapsedTile &tile : column)
        if (!tile.collapsed && (lowestEntropyTile == nullptr || lowestEntropyTile->tiles.size() > tile.tiles.size()))
          lowestEntropyTile = &tile;
    return lowestEntropyTile;
  }

  void init()
  {
    for (int x = 0; x < w; x++)
    {
      unCollapsed.push_back({});
      collapsed.push_back({});
      for (int y = 0; y < h; y++)
      {
        collapsed[x].push_back({});
        unCollapsed[x].push_back({x, y, availableTiles});
      }
    }
  }

  vector<UnCollapsedTile *> getNeighbours(UnCollapsedTile *tile)
  {
    vector<UnCollapsedTile *> neighbours;
    if (tile->x - 1 >= 0)
      neighbours.push_back(&unCollapsed[tile->x - 1][tile->y]);
    if (tile->x + 1 < w)
      neighbours.push_back(&unCollapsed[tile->x + 1][tile->y]);
    if (tile->y - 1 >= 0)
      neighbours.push_back(&unCollapsed[tile->x][tile->y - 1]);
    if (tile->y + 1 < h)
      neighbours.push_back(&unCollapsed[tile->x][tile->y + 1]);
    return neighbours;
  }

  void CheckTile(UnCollapsedTile *unCollapsedTile)
  {
    int initSize = unCollapsedTile->tiles.size();
    vector<UnCollapsedTile *> neighbours = getNeighbours(unCollapsedTile);

    for (AWFCTile &tile : unCollapsedTile->tiles)
      for (UnCollapsedTile *neighbour : neighbours)
        if (!neighbour->Allows(tile))
        {
          unCollapsedTile->remove(tile);
          break;
        }

    if (initSize == unCollapsedTile->tiles.size()) // if do not removed eny value
      return;

    for (UnCollapsedTile *neighbour : neighbours)
      CheckTile(neighbour);
  }

  void CollapseTile(UnCollapsedTile *unCollapsedTile)
  {
    if (unCollapsedTile->tiles.size() == 0 || unCollapsedTile->collapsed)
    {
      for (vector<UnCollapsedTile> column : unCollapsed)
      {
        for (UnCollapsedTile tile : column)
          cout << tile.tiles.size() << " ";
        cout << endl;
      }
      throw runtime_error("Cannot collapse wave function collapse");
    }

    int initSize = unCollapsedTile->tiles.size();
    unCollapsedTile->Collapse();
    collapsed[unCollapsedTile->x][unCollapsedTile->y] = unCollapsedTile->tiles[0];

    if (initSize == 1)
      return;

    vector<UnCollapsedTile *> neighbours = getNeighbours(unCollapsedTile);
    for (UnCollapsedTile *neighbour : neighbours)
      CheckTile(neighbour);
  }

  void Collapse()
  {
    while (!isCollapsed())
    {
      UnCollapsedTile *lowestEntropyTile = getLowestEntropy();
      CollapseTile(lowestEntropyTile);
    }
    unCollapsed = {};
  }

public:
  vector<vector<AWFCTile>> get() { return collapsed; }

  AdvancedWaveFunctionCollapse(vector<AWFCTile> _availableTiles, int _width, int _height, int _seed = time(0))
      : availableTiles(_availableTiles), w(_width), h(_height)
  {
    srand(_seed);
    init();
    Collapse();
  };
};
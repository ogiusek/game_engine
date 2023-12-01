#include <iostream>

#include <vector>
#include <set>
#include <iterator>
#include <functional>
#include <algorithm>

#include <ctime>
#include <cstdlib>

using namespace std;

class WFCTile
{
public:
  class Tile
  {
  public:
    int id;
    int chance;
    Tile(int _id, int _chance = 1) : id(_id), chance(_chance){};
  };

  int id;
  int chance;
  vector<Tile> allowedNeighbours;

  bool Allows(int _id)
  {
    for (Tile allowed : allowedNeighbours)
      if (allowed.id == _id)
        return true;
    return false;
  }
  int getChance(int _id)
  {
    for (Tile t : allowedNeighbours)
      if (t.id == _id)
        return t.chance;
    return 0;
  }
  WFCTile(int _id, int _chance, vector<Tile> _allowedNeighbours)
      : id(_id), chance(_chance), allowedNeighbours(_allowedNeighbours){};
  WFCTile(Tile tile) : id(tile.id), chance(tile.chance) {}
  WFCTile() {}
};

class WaveFunctionCollapse
{
private:
  class UnCollapsedTile
  {
  public:
    int x, y;
    bool collapsed = false;
    vector<WFCTile> tiles;
    int tilesSize;

    bool Allows(WFCTile tile)
    {
      for (WFCTile existingTile : tiles)
        if (existingTile.Allows(tile.id))
          return true;
      return false;
    }
    void remove(WFCTile tile)
    {
      for (int i = 0; i < tilesSize; i++)
        if (tile.id == tiles[i].id)
        {
          tiles.erase(tiles.begin() + i);
          tilesSize -= 1;
          if (tilesSize == 1)
            Collapse(); // <-- can do this
          break;
        }
    }
    void Collapse(vector<WFCTile> neighbours = {})
    {
      vector<WFCTile> randomTiles = tiles;
      vector<WFCTile> tilesChances;
      for (WFCTile neighbour : neighbours)
        for (auto neighbourTile : neighbour.allowedNeighbours)
          tilesChances.push_back(neighbourTile);
      for (WFCTile &t1 : randomTiles)
        for (WFCTile &t2 : tilesChances)
          if (t1.id == t2.id)
            t1.chance *= t2.chance;

      // for (WFCTile &t : randomTiles)
      //   cout << t.id << "." << t.chance << endl;
      // for (WFCTile neighbour : neighbours)
      //   for (WFCTile &randomTile : randomTiles)
      //     if (neighbour.id == randomTile.id)
      //     {
      //       randomTile.chance *= neighbour.chance;
      //       cout << randomTile.id << "." << randomTile.chance << " " << neighbour.chance << endl;
      //       break;
      //     }
      collapsed = true;
      if (tilesSize == 1)
        return;
      // tiles = {tiles[rand() % tiles.size()]};
      // return;

      int totalChance = 0;
      for (int i = 0; i < tilesSize; i++)
        totalChance += randomTiles[i].chance;
      // cout << totalChance << endl;
      float randChoice = (float)rand() / (float)RAND_MAX;
      float cumulativeChance = 0;
      for (int i = 0; i < tilesSize; i++)
      {
        float normalizedChance = (float)randomTiles[i].chance / (float)totalChance;
        cumulativeChance += normalizedChance;
        if (cumulativeChance >= randChoice)
        {
          randomTiles = {randomTiles[i]};
          tilesSize = 1;
          break;
        }
      }
      tiles = randomTiles;
    }
    UnCollapsedTile(int _x, int _y, vector<WFCTile> _tiles)
        : x(_x), y(_y), tiles(_tiles), tilesSize(tiles.size()){};
  };
  int w, h, seed;
  double collapseDuration = 0, getDuration = 0,
         eraseDuration = 0, tileCollapseDuration = 0, tileCheckDuration = 0;
  vector<WFCTile> availableTiles;

  vector<vector<UnCollapsedTile>> unCollapsed;
  vector<vector<WFCTile>> collapsed;

  set<UnCollapsedTile *>
      notCollapsedTiles,
      interactiveTiles;

  bool isCollapsed() { return notCollapsedTiles.size() == 0; }

  UnCollapsedTile *getLowestEntropy()
  {
    UnCollapsedTile *lowestEntropyTile = nullptr;
    if (interactiveTiles.size() == 0)
      // return *next(notCollapsedTiles.begin(), int(rand() % notCollapsedTiles.size())); // <-- randomization
      return *notCollapsedTiles.begin(); // <-- performance
    lowestEntropyTile = *interactiveTiles.begin();
    for (UnCollapsedTile *e : interactiveTiles)
      if (!e->collapsed && lowestEntropyTile->tilesSize > e->tilesSize)
        lowestEntropyTile = e;
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
    for (int x = 0; x < w; x++)
      for (int y = 0; y < h; y++)
        notCollapsedTiles.insert(&(unCollapsed[x][y]));
  }

  vector<UnCollapsedTile *> getNeighbours(UnCollapsedTile *tile)
  {
    vector<UnCollapsedTile *> neighbours;
    if (tile->x != 0)
      neighbours.push_back(&unCollapsed[tile->x - 1][tile->y]);
    if (tile->x + 1 != w)
      neighbours.push_back(&unCollapsed[tile->x + 1][tile->y]);
    if (tile->y != 0)
      neighbours.push_back(&unCollapsed[tile->x][tile->y - 1]);
    if (tile->y + 1 != h)
      neighbours.push_back(&unCollapsed[tile->x][tile->y + 1]);
    return neighbours;
  }

  void CheckTile(UnCollapsedTile *unCollapsedTile)
  {
    int initSize = unCollapsedTile->tilesSize;
    vector<UnCollapsedTile *> neighbours = getNeighbours(unCollapsedTile);

    for (WFCTile &tile : unCollapsedTile->tiles)    // for each tile
      for (UnCollapsedTile *neighbour : neighbours) // check is allowed by neighbours
        if (!neighbour->Allows(tile))
        {
          unCollapsedTile->remove(tile);
          break;
        }

    if (initSize == unCollapsedTile->tilesSize) // if do not removed eny value
      return;

    interactiveTiles.insert(unCollapsedTile);
    for (UnCollapsedTile *neighbour : neighbours)
      CheckTile(neighbour);
  }

  void CollapseTile(UnCollapsedTile *unCollapsedTile)
  {
    if (unCollapsedTile->tilesSize == 0)
      throw runtime_error("Cannot collapse wave function collapse");
    if (unCollapsedTile->collapsed)
    {
      notCollapsedTiles.erase(unCollapsedTile);
      interactiveTiles.erase(unCollapsedTile);
      return;
    }

    clock_t start = clock();
    interactiveTiles.erase(unCollapsedTile);
    notCollapsedTiles.erase(unCollapsedTile);
    clock_t stop = clock();
    eraseDuration += (double)(stop - start) / CLOCKS_PER_SEC;

    start = clock();
    vector<UnCollapsedTile *> neighbours = getNeighbours(unCollapsedTile);
    int initSize = unCollapsedTile->tilesSize;
    // unCollapsedTile->Collapse(neighbours); // <-- convert this to vector<WFCTile>

    // vector<WFCTile> neighboursValues;
    // for (UnCollapsedTile *neighbour : neighbours)
    //   for (WFCTile value : neighbour->tiles)
    //     neighboursValues.push_back(value);

    // unCollapsedTile->Collapse(neighboursValues);
    unCollapsedTile->Collapse(availableTiles);
    // unCollapsedTile->Collapse();
    stop = clock();
    tileCollapseDuration += (double)(stop - start) / CLOCKS_PER_SEC;

    if (initSize == 1)
      return;

    start = clock();
    for (UnCollapsedTile *neighbour : neighbours)
      CheckTile(neighbour);
    stop = clock();
    tileCheckDuration += (double)(stop - start) / CLOCKS_PER_SEC;
  }

  void Collapse()
  {
    while (!isCollapsed())
    {
      clock_t start = clock();
      UnCollapsedTile *lowestEntropyTile = getLowestEntropy();
      clock_t stop = clock();
      getDuration += (double)(stop - start) / CLOCKS_PER_SEC;

      start = clock();
      CollapseTile(lowestEntropyTile);
      stop = clock();
      collapseDuration += (double)(stop - start) / CLOCKS_PER_SEC;
    }
    for (int x = 0; x < w; x++)
      for (int y = 0; y < h; y++)
        collapsed[x][y] = unCollapsed[x][y].tiles[0];

    // unCollapsed UnCollapsedTile
    // collapsed WFCTile
    // for (vector<UnCollapsedTile> column : unCollapsed)
    //   for (UnCollapsedTile tile : column)
    //     cout << tile.tiles[0].id << " ";
    // cout << "\n\n\n";

    // for (vector<WFCTile> column : collapsed)
    //   for (WFCTile tile : column)
    //     cout << tile.id << " ";
    // cout << "\n\n\n";

    unCollapsed = {};
  }

public:
  vector<vector<WFCTile>> get() { return collapsed; }

  WaveFunctionCollapse(vector<WFCTile> _availableTiles, int _width, int _height, int _seed = time(0), bool showPerformance = 0)
      : availableTiles(_availableTiles), w(_width), h(_height)
  {
    seed = _seed;
    srand(_seed);

    init();
    clock_t start = clock();
    Collapse();
    clock_t stop = clock();

    double duration = (double)(stop - start) / CLOCKS_PER_SEC;
    if (showPerformance)
      // tileCollapseDuration
      // tileCheckDuration
      cout << w << "x" << h << " map generated in " << duration << "s\n"
           << " get duration is " << getDuration << "s\n"
           << " collapse duration is " << collapseDuration << "s where\n erasing took " << eraseDuration << "s, tile collapsing took " << tileCollapseDuration << "s and tile checking took " << tileCheckDuration << "s\n";
  };
};